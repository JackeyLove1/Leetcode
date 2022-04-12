import gym
import torch
import torch.nn as nn
import torch.nn.functional as F
import numpy as np
import random
import time
from collections import deque
from torch.distributions import Categorical

np.random.seed(1)
torch.manual_seed(1)

# Hyper Parameters for PG Network
GAMMA = 0.95  # discount factor
LR = 0.01  # learning rate

# Use GPU
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print("using device: ", device)


# torch.backends.cudnn.enabled = False  # 非确定性算法


class PGNetwork(nn.Module):
    def __init__(self, state_dim, action_dim):
        super(PGNetwork, self).__init__()
        self.fc1 = nn.Linear(state_dim, 20)
        self.fc2 = nn.Linear(20, action_dim)
        self.softmax = nn.Softmax(dim=1)  # [batch, action_dim]

    def forward(self, x):
        out = F.relu(self.fc1(x))
        out = self.fc2(out)
        return self.softmax(out)

    def initialize_weights(self):
        for m in self.modules():
            if isinstance(m, torch.nn.Linear):
                nn.init.normal_(m.weight.data, 0, 0.1)
                nn.init.constant_(m.bias.data, 0.01)


class PG(object):
    # dqn Agent
    def __init__(self, env):  # 初始化
        # 状态空间和动作空间的维度
        self.state_dim = env.observation_space.shape[0]
        self.action_dim = env.action_space.n

        # init N Monte Carlo transitions in one game
        self.rewards, self.log_prob = [], []

        # init network parameters
        self.network = PGNetwork(state_dim=self.state_dim, action_dim=self.action_dim).to(device)
        self.network.initialize_weights()

        self.optimizer = torch.optim.Adam(self.network.parameters(), lr=LR)
        self.criterion = nn.MSELoss()
        # init some parameters
        self.time_step = 0

    def action(self, state, train=True):
        state = torch.FloatTensor(state).unsqueeze(0).to(device)  # [batch, state_dim]
        prob = self.network.forward(state)
        m = Categorical(prob)
        action = m.sample()
        if train:
            self.log_prob.append(m.log_prob(action))
        return action.item()

    # 将状态，动作，奖励这一个transition保存到三个列表中
    def store_transition(self, s, a, reward):
        self.rewards.append(reward)

    def learn(self):
        self.time_step += 1

        discounted_rewards = []
        discount_reward = 0

        for r in reversed(self.rewards):
            discount_reward = discount_reward * GAMMA + r
            discounted_rewards.append(discount_reward)
        discounted_rewards = torch.FloatTensor(discounted_rewards).to(device)
        discounted_rewards = (discounted_rewards - discounted_rewards.mean()) / discounted_rewards.std()
        self.log_prob = torch.cat(self.log_prob)

        assert self.log_prob.size() == discounted_rewards.size(), "self.log_prob.size() != discounted_rewards.size()"
        loss = (discounted_rewards * self.log_prob).mean()
        # backward
        self.optimizer.zero_grad()
        loss.backward()
        self.optimizer.step()

        # clear
        self.rewards, self.log_prob = [], []


# ---------------------------------------------------------
# Hyper Parameters
ENV_NAME = 'CartPole-v0'
EPISODE = 1000  # Episode limitation
STEP = 300  # Step limitation in an episode
TEST = 10  # The number of experiment test every 100 episode


def main():
    # initialize OpenAI Gym env and dqn agent
    env = gym.make(ENV_NAME)
    agent = PG(env)

    for episode in range(EPISODE):
        # initialize task
        state = env.reset()
        # Train
        for step in range(STEP):
            action = agent.action(state)
            next_state, reward, done, _ = env.step(action)
            agent.store_transition(state, action, reward)
            state = next_state
            if done:
                agent.learn()  # 更新策略网络
                break

        # Test every 100 episodes
        if episode % 100 == 0:
            total_reward = 0
            for i in range(TEST):
                state = env.reset()
                for j in range(STEP):
                    # env.render()
                    action = agent.action(state, False)
                    state, reward, done, _ = env.step(action)
                    total_reward += reward
                    if done:
                        break
            ave_reward = total_reward / TEST
            print('episode: ', episode, 'Evaluation Average Reward:', ave_reward)


if __name__ == '__main__':
    time_start = time.time()
    main()
    time_end = time.time()
    print('The total time is ', time_end - time_start)
