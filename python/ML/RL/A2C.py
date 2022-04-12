# A2C
import torch
import torch.nn as nn
import torch.nn.functional as F
import numpy as np
import time
import gym

gamma = 0.95
lr = 0.001
hidden_state = 20

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print("using device: ", device)


def weight_init(m):
    classname = m.__class__.__name__
    if classname.find('Conv2d') != -1:
        torch.nn.init.normal_(m.weight.data, 0, 0.1)
        torch.nn.init.constant_(m.bias.data, 0.0)
    elif classname.find('Linear') != -1:
        torch.nn.init.normal_(m.weight)
        torch.nn.init.constant_(m.bias, 0.0)
    elif classname.find('BatchNorm2d') != -1:
        torch.nn.init.normal_(m.weight.data, 1.0, 0.02)
        torch.nn.init.constant_(m.bias.data, 0.0)


class MLP(nn.Module):
    def __init__(self, state_dim, action_state):
        super(MLP, self).__init__()
        self.fc1 = nn.Linear(state_dim, hidden_state)
        self.fc2 = nn.Linear(hidden_state, action_state)
        self.relu = nn.ReLU()

    def forward(self, x):
        x = self.fc1(x)
        x = self.relu(x)
        x = self.fc2(x)
        return x


class Actor(object):
    def __init__(self, env):
        self.state_dim = env.observation_space.shape[0]
        self.action_dim = env.action_space.n

        self.network = MLP(self.state_dim, self.action_dim)
        self.optimizer = torch.optim.SGD(self.network.parameters(), lr=lr)

        self.time_step = 0

    def choose_action(self, observation):
        observation = torch.FloatTensor(observation).to(device)
        network_output = self.network.forward(observation)  # [action_dim, ]
        with torch.no_grad():
            prob_weights = F.softmax(network_output, dim=0).data.cpu().numpy()
        action = np.random.choice(range(prob_weights.shape[0]), p=prob_weights)
        return action

    def learn(self, state, action, td_error):
        self.time_step += 1
        # forward
        softmax_input = self.network.forward(torch.FloatTensor(state).to(device)).unsqueeze(0)
        action = torch.LongTensor([action]).to(device)
        neg_log_prob = F.cross_entropy(input=softmax_input, target=action, reduction="none")
        # backward
        loss = -neg_log_prob * td_error
        self.optimizer.zero_grad()
        loss.backward()
        self.optimizer.step()


Eplison = 0.01
Episode = 1000
Steps = 300
Replay_szie = 10000
Tests = 10
Batch_size = 32
Replay_target_freq = 10  # frequency to update target Q network
game = 'CartPole-v0'


class Critic(nn.Module):
    def __init__(self, env):
        super(Critic, self).__init__()
        self.state_dim = env.observation_space.shape[0]
        self.action_dim = 1

        self.network = MLP(self.state_dim, self.action_dim).to(device)
        self.optimizer = torch.optim.SGD(self.network.parameters(), lr=lr)
        self.criterion = nn.MSELoss()

        self.time_step = 0
        self.epsilon = Eplison

    def train_Q_network(self, state, reward, next_state):
        s, s_ = torch.FloatTensor(state).to(device), torch.FloatTensor(next_state).to(device)

        # forward
        v = self.network.forward(s)
        v_ = self.network.forward(s_)

        # backward
        loss = self.criterion(reward + gamma * v_, v)
        self.optimizer.zero_grad()
        loss.backward()
        self.optimizer.step()

        with torch.no_grad():
            td_error = reward + gamma * v_ - v
        return td_error


def train():
    env = gym.make(game)
    actor = Actor(env)
    critic = Critic(env)

    for episode in range(Episode):
        state = env.reset()
        for step in range(Steps):
            action = actor.choose_action(state)
            next_state, reward, done, _ = env.step(action)
            td_error = critic.train_Q_network(state, reward, next_state)
            actor.learn(state, action, td_error)
            state = next_state
            if done:
                break

        if episode % 100 == 0:
            total_reward = 0
            for i in range(Tests):
                state = env.reset()
                for j in range(Steps):
                    action = actor.choose_action(state)
                    state, reward, done, _ = env.step(action)
                    total_reward += reward
                    if done:
                        break
            avg_reward = total_reward / Tests
            print("Episode:{}, Average Reward:{}".format(episode, avg_reward))


if __name__ == "__main__":
    train()
