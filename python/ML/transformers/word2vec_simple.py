from d2l import torch as d2l
import torch
import torch.nn as nn
import torch.functional as F

# 导入数据集
batch_size, max_window_size, num_noise_words = 512, 5, 5
data_iter, vocab = d2l.load_data_ptb(batch_size, max_window_size, num_noise_words)
    
# 构造embedding
embed = nn.Embedding(num_embeddings=20, embedding_dim=4)


# 使用skip_gram跳元法训练
def skip_gram(center, contexts_and_negatives, embed_v, embed_u):
    """
    :param center: [batch_size, 1] 中心词
    :param contexts_and_negatives: [batch_size, max_len] 采样大小（包括上下文和噪声单词并填充）
    :param embed_v:
    :param embed_u:
    :return:
    """
    v = embed_v(center)  # [batch_size, 1, embedding_v]
    u = embed_u(contexts_and_negatives)  # [batch_size, max_len, embedding_u]
    pred = torch.bmm(v, u.transpose(-1, -2))  # embedding_v == embedding_u
    return pred


# 带掩码的二元交叉损失函数
class SigmoidBCELoss(nn.Module):
    def __init__(self):
        super(SigmoidBCELoss, self).__init__()

    def forward(self, inputs, target, mask=None):
        out = nn.functional.binary_cross_entropy_with_logits(inputs, target, weight=mask, reduction='None')
        return out.mean(dim=1)


loss = SigmoidBCELoss()

embed_size = 100

net = nn.Sequential(
    nn.Embedding(len(vocab), embed_size),
    nn.Embedding(len(vocab), embed_size)
)


def train(net, data_iter, lr, num_epochs, device=d2l.try_gpu()):
    def init_weight(m):
        if type(m) == nn.Embedding:
            nn.init.xavier_uniform_(m.weight)

    net.apply(init_weight)
    net = net.to(device)
    optimizer = torch.optim.Adam(net.parameters(), lr=lr)
    for epoch in range(num_epochs):
        num_batches = len(data_iter)
        losses = 0
        for batch in data_iter:
            optimizer.zero_grad()
            center, context_negative, mask, label = [data.to(device) for data in batch]
            pred = skip_gram(center, context_negative, net[0], net[1])
            l = (loss(pred.reshape(label.shape).float(), label.float(), mask) / mask.sum(axis=1) * mask.shape[1])
            losses += l.sum()
            l.sum().backward()
            optimizer.step()
        print("Epoch %d, Losses: %d\n", epoch, losses)

lr, num_epochs = 0.002, 5

if __name__ == "__main__":
    train(net, data_iter, lr, num_epochs)