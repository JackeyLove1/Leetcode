import gym
import random
import torch
import torch.nn as nn
import numpy as np
import torch.nn.functional as F
from collections import deque
from tqdm import tqdm

env_name = 'CartPole-v0'
random_seed = 0

np.random.seed(random_seed)
torch.manual_seed(random_seed)
random.seed(0)

hidden_state1 = 100
hidden_state2 = 20


class Game(object):
    def __init__(self, game=env_name, seed=random_seed):
        self.game = gym.make(game)
        self.game.seed(seed)

    def reset(self):
        return self.game.reset()

    def step(self, action):
        return self.game.step(action)

    def state_dim(self):
        return self.game.observation_space.shape[0]

    def action_dim(self):
        return self.game.action_space.n


class ReplayBuffer:
    """Experience Replay Buffer"""

    def __init__(self, capacity):
        self.buffer = deque(maxlen=capacity)

    def add(self, state, action, reward, next_state, done):
        self.buffer.append((state, action, reward, next_state, done))

    def sample(self, batch_size):
        return random.sample(self.buffer, batch_size)

    def size(self):
        return len(self.buffer)


class QNet(nn.Module):
    def __init__(self, state_dim, action_dim):
        super(QNet, self).__init__()
        self.fc1 = nn.Linear(state_dim, hidden_state1)
        nn.init.normal_(self.fc1.weight, 0, 0.1)
        nn.init.constant_(self.fc1.bias, 0)
        self.fc2 = nn.Linear(hidden_state1, hidden_state2)
        nn.init.normal_(self.fc2.weight, 0, 0.1)
        nn.init.constant_(self.fc2.bias, 0)
        self.fc3 = nn.Linear(hidden_state2, action_dim)
        nn.init.normal_(self.fc3.weight, 0, 0.1)
        nn.init.constant_(self.fc3.bias, 0)

    def forward(self, x):
        x = F.gelu(self.fc1(x))
        x = F.gelu(self.fc2(x))
        x = self.fc3(x)
        return x


device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
learning_rate = 0.0025
num_episodes = 500
gamma = 0.98
eplison = 0.01
target_update = 10
buffer_size = 10000
minimal_size = 500
batch_size = 64
num_tests = 10


class DQN(object):
    """
    state: [1, state_dim]
    reward: [1]
    action: [1]
    done: [1]
    """

    def __init__(self, state_dim, action_dim,
                 learning_rate, gamma, epsilon, target_update):
        self.state_dim = state_dim
        self.action_dim = action_dim
        self.learning_rate = learning_rate
        self.gamma = gamma
        self.epsilon = eplison
        self.target_update = target_update

        self.qnet = QNet(self.state_dim, self.action_dim).to(device)
        self.target_qnet = QNet(self.state_dim, self.action_dim).to(device)

        self.optimizer = torch.optim.Adam(self.qnet.parameters(), lr=learning_rate)
        self.criterion = torch.nn.MSELoss()

        self.gamma = gamma
        self.epsilon = eplison
        self.count = 0

    def take_action(self, state):
        if np.random.random() < self.epsilon:
            action = np.random.randint(0, self.action_dim)
        else:
            state = torch.FloatTensor(state).unsqueeze(0).to(device)
            action = self.qnet(state).argmax(dim=-1).item()
        return action

    def update(self, data_batch):
        """
        :param data_batch: state, action, reward, next_state, done
        :return:
        """
        states_batch = torch.FloatTensor([data[0] for data in data_batch]).to(device)
        actions_batch = torch.FloatTensor([[data[1]] for data in data_batch]).to(device)
        rewards_batch = torch.FloatTensor([[data[2]] for data in data_batch]).to(device)
        next_states_batch = torch.FloatTensor([data[3] for data in data_batch]).to(device)
        dones_batch = torch.FloatTensor([[data[4]] for data in data_batch]).to(device)

        q_values = self.qnet(states_batch).gather(1, actions_batch.long())

        next_q_values = torch.max(self.target_qnet(next_states_batch), dim=1)[0].unsqueeze(1)
        # td-error
        q_target = rewards_batch + self.gamma * next_q_values * (1 - dones_batch)

        self.optimizer.zero_grad()
        # loss = self.criterion(q_values, q_target)
        loss = self.criterion(q_values, q_target).mean()
        # print(loss)
        loss.backward()
        self.optimizer.step()

        self.count += 1
        if self.count % self.target_update == 0:
            self.target_qnet.load_state_dict(self.qnet.state_dict())


def main():
    game = Game()
    agent = DQN(game.state_dim(), game.action_dim(), learning_rate, gamma, eplison, target_update)
    replay_buffer = ReplayBuffer(buffer_size)
    for i in range(100):
        for step in range(int(num_episodes / 10)):
            agent.qnet.train()
            for i_episode in range(int(num_episodes / 10)):
                total_reward = 0
                state = game.reset()
                done = False
                while not done:
                    action = agent.take_action(state)
                    next_state, reward, done, _ = game.step(action)
                    replay_buffer.add(state, action, reward, next_state, done)
                    state = next_state
                    total_reward += reward
                    if replay_buffer.size() > minimal_size:
                        data_batch = replay_buffer.sample(batch_size)
                        agent.update(data_batch)
            # test
            test_reward = 0
            agent.qnet.eval()
            for i_test in range(num_tests):
                state = game.reset()
                done = False
                while not done:
                    action = agent.take_action(state)
                    next_state, reward, done, _ = game.step(action)
                    test_reward += reward
                    state = next_state
            print("Episode: {}, Test_Average_Reward: {}".format(i * 100 + step, test_reward / 10))


if __name__ == "__main__":
    main()
