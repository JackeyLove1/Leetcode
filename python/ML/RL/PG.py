import torch
import torch.nn as nn
import torch.nn.functional as F
import gym
import time
from collections import deque
import numpy as np

gamma = 0.5
lr = 0.001
hidden_state = 20
game = 'CartPole-v0'
episodes = 2000
steps = 300
tests = 10
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')


class PGNetwork(nn.Module):
    def __init__(self, state_dim, action_dim):
        super(PGNetwork, self).__init__()
        self.fc1 = nn.Linear(state_dim, hidden_state)
        self.relu = nn.ReLU()
        self.fc2 = nn.Linear(hidden_state, action_dim)

    def forward(self, x):
        x = self.fc1(x)
        x = self.relu(x)
        x = self.fc2(x)
        return x

    def initialize_weight(self):
        for m in self.modules():
            nn.init.normal_(m.weight.data, 0, 0.1)
            nn.init.constant_(m.bias.data, 0.01)


class PG(object):
    def __init__(self, env):
        self.state_dim = env.observation_space.shape[0]
        self.action_dim = env.action_space.n

        # init N Monte Carlo transictions in one game
        self.ep_obs, self.ep_as, self.ep_rs = [], [], []

        # init network parameters
        self.network = PGNetwork(state_dim=self.state_dim, action_dim=self.action_dim)
        self.optimizer = torch.optim.SGD(self.network.parameters(), lr=lr)

        self.time_step = 0

    def choose_action(self, observation):
        observation = torch.FloatTensor(observation).to(device)
        # print("network.shape: ", observation.size())
        network_output = self.network.forward(observation)
        with torch.no_grad():
            prob_weight = F.softmax(network_output, dim=0).data.cpu().numpy()
        action = np.random.choice(range(prob_weight.shape[0]), p=prob_weight)
        return action

    def store_transition(self, s, a, r):
        self.ep_obs.append(s)
        self.ep_as.append(a)
        self.ep_rs.append(r)

    def learn(self):
        self.time_step += 1

        # calculate the value of every step
        discount_ep_rs = np.zeros_like(self.ep_rs)
        running_add = 0
        # from back to front calculate
        for t in reversed(range(0, len(self.ep_rs))):
            running_add = running_add * gamma + self.ep_rs[t]
            discount_ep_rs[t] = running_add
        discount_ep_rs -= np.mean(discount_ep_rs)
        discount_ep_rs /= np.std(discount_ep_rs)
        discount_ep_rs = torch.FloatTensor(discount_ep_rs).to(device)

        # forward
        softmax_input = self.network.forward(torch.FloatTensor(self.ep_obs).to(device))
        # all_act_prob
        neg_log_prob = F.cross_entropy(input=softmax_input, target=torch.LongTensor(self.ep_as).to(device))

        # backward
        loss = torch.mean(neg_log_prob * discount_ep_rs)
        self.optimizer.zero_grad()
        loss.backward()
        self.optimizer.step()

        # clear
        self.ep_obs, self.ep_as, self.ep_rs = [], [], []


def train():
    env = gym.make(game)
    agent = PG(env)
    for episode in range(episodes):
        state = env.reset()
        for step in range(steps):
            action = agent.choose_action(state)
            next_state, reward, done, _ = env.step(action)
            agent.store_transition(state, action, reward)
            state = next_state
            if done:
                agent.learn()
                break
        if episode % 100 == 0:
            total_reward = 0
            for i in range(tests):
                state = env.reset()
                for j in range(steps):
                    action = agent.choose_action(state)
                    state, reward, done, _ = env.step(action)
                    total_reward += reward
                    if done:
                        break
            avg_reward = total_reward / tests
            print("Episode:{}, Average Reward: {}".format(episode, avg_reward))


if __name__ == "__main__":
    train()
