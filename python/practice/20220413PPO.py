import gym
import torch.nn as nn
import torch
import torch.nn.functional as F
from torch.distributions import Categorical
import warnings
import time
import numpy as np
warnings.filterwarnings("ignore")
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print("using device; ", device)

num_episodes = 1000
lr = 0.001
gamma = 0.98
lmbda = 0.95
num_epochs = 3
eps_clip = 0.2
max_steps = 1000
num_tests = 10


class PPO(nn.Module):
    def __init__(self):
        super(PPO, self).__init__()
        self.data = []
        self.fc1 = nn.Linear(4, 256)
        self.fc2 = nn.Linear(256, 100)
        self.actor_network = nn.Linear(100, 2)
        self.critic_network = nn.Linear(100, 1)
        self.relu = nn.ReLU()
        self.optimizer = torch.optim.SGD(self.parameters(), lr=lr)
        self.criterion = torch.nn.MSELoss()

    def actor(self, x, softmax_dim=1):
        x = self.relu(self.fc1(x))
        x = self.relu(self.fc2(x))
        x = self.actor_network(x)
        prob = F.softmax(x, dim=softmax_dim)
        return prob

    def critic(self, x):
        x = self.relu(self.fc1(x))
        x = self.relu(self.fc2(x))
        x = self.critic_network(x)
        return x

    def put_data(self, transition):
        # transition: state, action, reward, next_state, prob_action, done
        self.data.append(transition)

    def make_batch(self):
        state_batch, action_batch = [], []
        reward_batch, next_state_batch = [], []
        prob_action_batch, done_batch = [], []

        for t in self.data:
            states, actions, rewards, next_states, prob_actions, dones = t
            state_batch.append(states)
            action_batch.append([actions])
            reward_batch.append([rewards])
            next_state_batch.append(next_states)
            prob_action_batch.append(prob_actions)
            done_batch.append([dones])
        state_batch = torch.FloatTensor(state_batch).to(device)
        action_batch = torch.FloatTensor(action_batch).to(device)
        reward_batch = torch.FloatTensor(reward_batch).to(device)
        next_state_batch = torch.FloatTensor(next_state_batch).to(device)
        prob_action_batch = torch.FloatTensor(prob_action_batch).to(device)
        done_batch = torch.FloatTensor(done_batch).to(device)

        self.data = []
        return state_batch, action_batch, reward_batch, next_state_batch, prob_action_batch, done_batch

    def train_net(self):
        s, a, r, next_s, prob_a, done_mask = self.make_batch()
        for i in range(num_epochs):
            td_target = r + gamma * (1 - done_mask) * self.critic(next_s)
            td_error = td_target - self.critic(s)
            td_error = td_error.detach().numpy()

            # Advantage Evaluate
            discount_td_errors = []
            discount_error = 0
            for err in reversed(td_error):
                discount_error = gamma * lmbda * discount_error + err[0]
                discount_td_errors.append(discount_error)
            discount_td_errors.reverse()
            discount_td_errors = torch.FloatTensor(discount_td_errors)

            # a / b = log(a) - log(b)
            prob_eval = self.actor(s)
            prob_action = prob_eval.gather(1, a.long())
            ratio = torch.exp(torch.log(prob_action) - torch.log(prob_a))

            surr1 = ratio * discount_td_errors
            surr2 = torch.clamp(surr1, 1 - eps_clip, 1 + eps_clip) * discount_td_errors
            loss = -torch.min(surr1, surr2) + self.criterion(td_target.detach(), self.critic(s))
            # actor_loss + critic_loss

            self.optimizer.zero_grad()
            loss.mean().backward()
            self.optimizer.step()


def main():
    env = gym.make('CartPole-v1')
    model = PPO()

    for episode in range(num_episodes):
        state = env.reset()
        while True:
            prob = model.actor(torch.FloatTensor(state).unsqueeze(0))
            m = Categorical(prob)
            action = m.sample().item()
            next_state, reward, done, _ = env.step(action)
            model.put_data((state, action, reward / 100, next_state, prob.squeeze(0)[action].item(), done))
            state = next_state
            if done:
                break
        model.train_net()
        if episode % 100 == 0:
            total_reward = 0
            for i in range(num_tests):
                state = env.reset()
                while True:
                    prob = model.actor(torch.FloatTensor(state).unsqueeze(0))
                    m = Categorical(prob)
                    action = m.sample().item()
                    next_state, reward, done, _ = env.step(action)
                    total_reward += reward
                    state = next_state
                    if done:
                        break
            print("Episode:{}, Total_reward:{}".format(episode, total_reward / num_tests))


if __name__ == "__main__":
    start = time.time()
    main()
    print("Cost:{}".format(time.time() - start))
