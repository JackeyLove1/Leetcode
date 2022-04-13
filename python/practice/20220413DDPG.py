"""
DDPG用于连续动作的Double-DQN
"""

import gym
import torch
import torch.nn as nn
from torch.distributions import Normal
import numpy as np
import warnings
import time
from collections import deque
import math
import random

warnings.filterwarnings("ignore")
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print("using device; ", device)

num_episodes = 1000
lr = 0.001
gamma = 0.98
lmbda = 0.95
num_epochs = 3
num_steps = 300
eps_clip = 0.2
max_steps = 1000
num_tests = 3
num_update_iterations = 100
env_name = 'Pendulum-v0'
env = gym.make(env_name)
state_dim = env.observation_space.shape[0]
action_dim = env.action_space.shape[0]
max_memory = 10000
sample_batch = 100
actor_update = 100
critic_update = 100
explore = 0.99
explore_declay = 0.0001
explore_noise = 0.1


class Actor(nn.Module):
    """
    max_action expand the actions
    return a certain action
    """

    def __init__(self, state_dim, action_dim, max_action=2):
        super(Actor, self).__init__()
        self.fc1 = nn.Linear(state_dim, 100)
        self.fc2 = nn.Linear(100, 20)
        self.fc3 = nn.Linear(20, action_dim)
        self.max_action = max_action
        self.relu = nn.ReLU()

    def forward(self, x):
        x = self.relu(self.fc1(x))
        x = self.relu(self.fc2(x))
        x = self.max_action * torch.tanh(self.fc3(x))  # 将连续的动作缩放到[-1, 1]之间再扩展
        return x

    def init_weight(self):
        for m in self.modules():
            if isinstance(m, torch.nn.Linear):
                nn.init.xavier_normal_(m.weight.data)
                nn.init.constant_(m.bias.data, 0)


class Critic(nn.Module):
    """
    Input: state_batch, action_batch
    return: Q-val
    """

    def __init__(self, state_dim, action_dim):
        super(Critic, self).__init__()
        self.fc1 = nn.Linear(state_dim + action_dim, 100)
        self.fc2 = nn.Linear(100, 20)
        self.fc3 = nn.Linear(20, 1)
        self.relu = nn.ReLU()

    def forward(self, states, actions):
        x = torch.cat([states, actions], dim=1)
        x = self.relu(self.fc1(x))
        x = self.relu(self.fc2(x))
        x = self.fc3(x)
        return x

    def init_weight(self):
        for m in self.modules():
            if isinstance(m, torch.nn.Linear):
                nn.init.xavier_normal_(m.weight.data)
                nn.init.constant_(m.bias.data, 0)


class Replay_buffer():
    """
    repaly_buffer
    transaction: state, action, reward, next_s, done
    """

    def __init__(self, max_size=max_memory, batch_size=sample_batch):
        self.buffer = deque()
        self.max_size = max_size
        self.batch_size = batch_size

    def push(self, transaction):
        if len(self.buffer) > self.max_size:
            self.buffer.popleft()
        self.buffer.append(transaction)

    def sample(self):
        return random.sample(self.buffer, self.batch_size)


class DDPG(object):
    def __init__(self, state_dim, action_dim, max_action=2):
        self.explore = explore
        self.actor = Actor(state_dim, action_dim, max_action).to(device)
        self.actor.init_weight()
        self.actor_target = Actor(state_dim, action_dim, max_action).to(device)
        self.actor_target.load_state_dict(self.actor.state_dict())
        self.actor_optimizer = torch.optim.Adam(self.actor.parameters(), lr=lr)

        self.critic = Critic(state_dim, action_dim).to(device)
        self.critic.init_weight()
        self.critic_target = Critic(state_dim, action_dim).to(device)
        self.critic_target.load_state_dict(self.critic.state_dict())
        self.critic_optimizer = torch.optim.Adam(self.actor.parameters(), lr=lr)

        self.criterion = torch.nn.MSELoss()
        self.num_actor_learn_iteration = 0
        self.num_critic_learn_iteration = 0
        self.num_trainings = 0

        self.repaly_buffer = Replay_buffer()

    def choose_action(self, state, is_train=True):
        if is_train and np.random.random() < self.explore:
            self.explore = max(self.explore - explore_declay, explore_declay)
            return np.random.normal(0, explore_noise, size=env.action_space.shape[0])

        state = torch.FloatTensor(state).to(device)  # state [1, state_dim]
        action = self.actor(state)
        return action.detach().numpy()

    def store(self, state, action, reward, next_state, done):
        self.repaly_buffer.push((state, action, reward, next_state, done))

    def update(self):
        for i in range(num_update_iterations):
            data_batch = self.repaly_buffer.sample()
            state_batch = torch.FloatTensor([data[0] for data in data_batch]).to(device)
            action_batch = torch.FloatTensor([data[1] for data in data_batch]).to(device)
            reward_batch = torch.FloatTensor([[data[2]] for data in data_batch]).to(device)
            next_state_batch = torch.FloatTensor([data[3] for data in data_batch]).to(device)
            done_batch = torch.FloatTensor([[data[4]] for data in data_batch]).to(device)

            # critic loss
            target_q = self.critic_target(next_state_batch, self.actor_target(next_state_batch))
            target_q = (reward_batch + (1 - done_batch) * gamma * target_q).detach()

            current_q = self.critic(state_batch, action_batch)

            critic_loss = self.criterion(target_q, current_q)
            self.critic_optimizer.zero_grad()
            critic_loss.backward()
            self.critic_optimizer.step()
            # print("critic_loss: ", critic_loss.item())

            # actor loss
            actor_loss = -self.critic(state_batch, self.actor(state_batch)).sum()
            self.actor_optimizer.zero_grad()
            actor_loss.backward()
            self.actor_optimizer.step()
            # print("actor_loss: ", actor_loss.item())

            # update
            self.num_actor_learn_iteration += 1
            if self.num_actor_learn_iteration % actor_update == 0:
                self.actor_target.load_state_dict(self.actor.state_dict())

            self.num_critic_learn_iteration += 1
            if self.num_critic_learn_iteration % critic_update == 0:
                self.critic_target.load_state_dict(self.critic.state_dict())


def main():
    agent = DDPG(state_dim, action_dim)
    for episode in range(num_episodes):
        state = env.reset()
        for step in range(num_steps):
            action = agent.choose_action(state, is_train=True)
            next_state, reward, done, _ = env.step(action)
            agent.store(state, action, reward, next_state, done)
            state = next_state
            if done:
                break
        agent.update()
        if episode % 100 == 0:
            total_reward = 0
            for j in range(num_tests):
                state = env.reset()
                for step in range(num_steps):
                    action = agent.choose_action(state, is_train=False)
                    next_state, reward, done, _ = env.step(action)
                    total_reward += reward
                    agent.store(state, action, reward, next_state, done)
                    state = next_state
                    if done:
                        break
            print("Episode: {}, Total_reward:{}".format(episode, total_reward))


if __name__ == "__main__":
    main()
