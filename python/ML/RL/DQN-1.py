import gym
import torch
import torch.nn as nn
import torch.nn.functional as F
import numpy as np
import random
import time
from collections import deque

# hyper parameter
gamma = 0.9  # discount factor
initial_epsilon = 0.5  # starting value of epsilon
final_epsilon = 0.01  # final value of epsilon
replay_size = 10000  # experience replay buffer size
explore = 10000
batch_size = 32  # size of minibatch
lr = 0.001
hidden_size1 = 100
hidden_size2 = 20

device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
print("using device: ", device)

np.random.seed(int(time.time()) % 1000)


class QNetWork(nn.Module):
    def __init__(self, state_dim, action_dim):
        super(QNetWork, self).__init__()
        self.fc1 = nn.Linear(state_dim, hidden_size1)
        self.relu = nn.ReLU()
        self.fc2 = nn.Linear(hidden_size1, hidden_size2)
        self.fc3 = nn.Linear(hidden_size2, action_dim)

    def forward(self, x):
        x = self.fc1(x)
        x = self.relu(x)
        x = self.fc2(x)
        x = self.relu(x)
        x = self.fc3(x)
        return x

    def initialize_weights(self):
        for m in self.modules():
            nn.init.normal_(m.weight.data, 0, 0.1)
            nn.init.constant_(m.bias.data, 0)


class DQN(object):
    def __init__(self, env):
        self.state_dim = env.observation_space.shape[0]
        self.action_dim = env.action_space.n

        # init experience replay
        self.replay_buffer = deque()

        # init network parameters
        self.network = QNetWork(state_dim=self.state_dim, action_dim=self.action_dim).to(device)
        self.optimizer = torch.optim.SGD(self.network.parameters(), lr=lr)
        self.criterion = nn.MSELoss()

        # init epsilon
        self.time_step = 0
        self.epsilon = initial_epsilon

    def perceive(self, state, action, reward, next_state, done):
        # state [4] action [2] reward[1] done [bool]
        one_hot_action = np.zeros(self.action_dim)
        one_hot_action[action] = 1
        # put the transition into pool
        self.replay_buffer.append((state, one_hot_action, reward, next_state, done))
        if len(self.replay_buffer) > replay_size:
            self.replay_buffer.popleft()
        if len(self.replay_buffer) > batch_size:
            self.train_Q_NetWork()

    def train_Q_NetWork(self):
        self.time_step += 1

        # step 1: obtain minibatch from replay_buffer
        minibatch = random.sample(self.replay_buffer, batch_size)  # [32]
        state_batch = torch.FloatTensor([data[0] for data in minibatch]).to(device)  # [32 * 4]
        action_batch = torch.FloatTensor([data[1] for data in minibatch]).to(device)  # [32 * 2]
        reward_batch = torch.FloatTensor([data[2] for data in minibatch]).to(device)  # [32]
        next_state_batch = torch.FloatTensor([data[3] for data in minibatch]).to(device)  # [32 * 4]
        done = torch.FloatTensor([data[4] for data in minibatch]).to(device)  # [32]

        done = done.unsqueeze(1)  # [32] -> [32 * 1]
        reward_batch = reward_batch.unsqueeze(1)  # [32] -> [32 * 1]
        # q_val = self.network.forward(state_batch) # [32 * 2]
        action_index = action_batch.argmax(dim=-1).unsqueeze(1)  # [32 * 2],选择的动作
        eval_q = self.network.forward(state_batch).gather(1, action_index)  # 根据动作选择q

        # calculate y
        Q_value_batch = self.network.forward(next_state_batch)  # [32 * 2] 只有两个动作空间，返回两个q
        next_action_batch = torch.unsqueeze(torch.max(Q_value_batch, dim=-1)[1], 1)
        next_q = self.network.forward(next_state_batch).gather(1, next_action_batch)

        # TD algorithm
        y_batch = reward_batch + gamma * next_q * (1 - done)
        loss = self.criterion(eval_q, y_batch)
        self.optimizer.zero_grad()
        loss.backward()
        self.optimizer.step()

    def egreedy_action(self, state):
        state = torch.unsqueeze(torch.FloatTensor(state).to(device), 0)
        Q_value = self.network.forward(state.to(device))
        # random select or greedy select
        if random.random() <= self.epsilon:
            self.epsilon -= (initial_epsilon - final_epsilon) / explore
            return random.randint(0, self.action_dim - 1)
        else:
            self.epsilon -= (initial_epsilon - final_epsilon) / explore
            return torch.max(Q_value, 1)[1].data.to('cpu').numpy()[0]

    def action(self, state):
        state = torch.unsqueeze(torch.FloatTensor(state).to(device), 0)
        Q_value = self.network.forward(state.to(device))
        return torch.max(Q_value, dim=1)[1].data.to('cpu').numpy()[0]


game = 'CartPole-v0'
episodes = 3000
steps = 300
test = 10


def train():
    env = gym.make(game)
    # env.unwrapped()  # open restricted operation
    agent = DQN(env)

    for episode in range(episodes):
        state = env.reset()
        for step in range(steps):
            action = agent.egreedy_action(state)
            next_state, reward, done, _ = env.step(action)
            reward = -1 if done else 0.1
            agent.perceive(state, action, reward, next_state, done)
            state = next_state
            if done:
                break
        if episode % 100 == 0:
            total_reward = 0
            for i in range(test):
                state = env.reset()
                for j in range(steps):
                    action = agent.action(state)
                    state, reward, done, _ = env.step(action)
                    total_reward += reward
                    if done:
                        break
            ave_reward = total_reward / test
            print(
                'Episode: {}, Evaluation Average Reward:{}, Total_reward:{}'.format(episode, ave_reward, total_reward))


if __name__ == "__main__":
    time_start = time.time()
    train()
    print("The total time: {}".format(time.time() - time_start))
