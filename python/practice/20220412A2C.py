import gym
import torch
import torch.nn as nn
import torch.nn.functional as F
import numpy as np
import random
import time
from collections import deque
from torch.distributions import Categorical
import warnings

warnings.filterwarnings("ignore")
np.random.seed(1)
torch.manual_seed(1)

# Hyper Parameters for PG Network
GAMMA = 0.95  # discount factor
LR = 0.01  # learning rate
ENV_NAME = 'CartPole-v0'
EPISODE = 3000  # Episode limitation
STEP = 3000  # Step limitation in an episode
TEST = 10  # The number of experiment test every 100 episode
EPSILON = 0.01  # final value of epsilon
REPLAY_SIZE = 10000  # experience replay buffer size
BATCH_SIZE = 32  # size of minibatch
REPLACE_TARGET_FREQ = 10  # frequency to update target Q network

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print("using device: ", device)


class Network(nn.Module):
    def __init__(self, input_size, output_size):
        super(Network, self).__init__()
        self.fc1 = nn.Linear(input_size, 20)
        self.fc2 = nn.Linear(20, output_size)

    def forward(self, x):
        out = F.relu(self.fc1(x))
        out = self.fc2(out)
        return out

    def initialize_weights(self):
        for m in self.modules():
            if isinstance(m, torch.nn.Linear):
                nn.init.normal_(m.weight.data, 0, 0.1)
                nn.init.constant_(m.bias.data, 0.01)


# PG
class Actor(object):
    def __init__(self, env):
        self.state_dim = env.observation_space.shape[0]
        self.action_dim = env.action_space.n

        self.actor = Network(self.state_dim, self.action_dim).to(device)
        self.actor.initialize_weights()

        self.optimizer = torch.optim.SGD(self.actor.parameters(), lr=LR)

    def action(self, state):
        state = torch.FloatTensor(state).unsqueeze(0).to(device)  # [batch, state_dim]
        prob = torch.softmax(self.actor(state), dim=1)
        m = Categorical(prob)
        return m.sample().item()

    def learn(self, state, action, td_error):
        state = torch.FloatTensor(state).unsqueeze(0).to(device)  # [batch, state_dim]
        action = torch.LongTensor([action]).to(device)
        softmax_state = self.actor.forward(state)
        neg_log_prob = F.cross_entropy(input=softmax_state, target=action, reduction='none')
        loss = -neg_log_prob * td_error
        self.optimizer.zero_grad()
        loss.backward()
        self.optimizer.step()


# QL
class Critic(object):
    def __init__(self, env):
        # 状态空间和动作空间的维度
        self.state_dim = env.observation_space.shape[0]
        self.action_dim = env.action_space.n
        self.critic = Network(self.state_dim, 1).to(device)
        self.critic.initialize_weights()

        self.optimizer = torch.optim.SGD(self.critic.parameters(), lr=LR)
        self.criterion = torch.nn.MSELoss()

    def learn(self, state, reward, next_state):
        state = torch.FloatTensor(state).unsqueeze(0).to(device)
        next_state = torch.FloatTensor(next_state).unsqueeze(0).to(device)

        q = self.critic(state)
        next_q = self.critic(next_state)

        loss = self.criterion(reward + GAMMA * next_q, q)
        self.optimizer.zero_grad()
        loss.backward()
        self.optimizer.step()

        with torch.no_grad():
            td_error = reward + GAMMA * next_q - q

        return td_error


def train():
    # initialize OpenAI Gym env and dqn agent
    env = gym.make(ENV_NAME)
    actor = Actor(env)
    critic = Critic(env)

    for episode in range(EPISODE):
        # initialize task
        state = env.reset()
        # Train
        for step in range(STEP):
            action = actor.action(state)  # SoftMax概率选择action
            next_state, reward, done, _ = env.step(action)
            td_error = critic.learn(state, reward, next_state)  # gradient = grad[r + gamma * V(s_) - V(s)]
            actor.learn(state, action, td_error)  # true_gradient = grad[logPi(s,a) * td_error]
            state = next_state
            if done:
                break

        # Test every 100 episodes
        if episode % 100 == 0:
            total_reward = 0
            for i in range(TEST):
                state = env.reset()
                for j in range(STEP):
                    # env.render()
                    action = actor.action(state)  # direct action for test
                    state, reward, done, _ = env.step(action)
                    total_reward += reward
                    if done:
                        break
            ave_reward = total_reward / TEST
            print('episode: ', episode, 'Evaluation Average Reward:', ave_reward)


if __name__ == '__main__':
    time_start = time.time()
    train()
    time_end = time.time()
    print('Total time is ', time_end - time_start, 's')
