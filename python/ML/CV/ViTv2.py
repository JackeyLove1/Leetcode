import torch
import torchvision
import time
import torch.nn as nn
import torch.nn.functional as F
import numpy as np
from einops import rearrange, repeat
from einops.layers.torch import Rearrange

device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")


class PreNorm(nn.Module):
    def __init__(self, dim, fc):
        super(PreNorm, self).__init__()
        self.fc = fc
        self.norm = nn.LayerNorm(dim)

    def forward(self, x):
        return self.fc(self.norm(x))


class Attention(nn.Module):
    def __init__(self, dim, heads, dim_head, dropout=0.):
        super(Attention, self).__init__()
        self.inner_dim = heads * dim_head
        self.heads = heads
        self.scale = np.sqrt(dim_head)
        self.to_qkv = nn.Linear(dim, self.inner_dim * 3, bias=False)
        self.atten = nn.Softmax(dim=-1)
        self.out = nn.Sequential(
            nn.Linear(self.inner_dim, dim),
            nn.Dropout(dropout),
        )

    def forward(self, x):
        """
        :param x: [batch_size, n, dim]
        :return: [batch_size, n, dim]
        """
        # [batch_size, n, dim] -> [bs, n, heads * dim_heads] -> [bs, heads, n, dim_heads]
        qkv = self.to_qkv(x).chunk(3, dim=-1)  # [batch_size, n, dim] -> [bs, n, inner_dim] -> [bs, n, dim_head]
        # [bs, n, dim_head] -> [bs, heads, n, dim_heads] -> [bs, n, inner_dim]
        q, k, v = map(lambda t: rearrange(t, "b n (h d) -> b h n d", h=self.heads), qkv)  # [bs, heads, n, dim_head]
        qk = torch.einsum("b n i d, b n j d -> b n i j", q, k) / self.scale  # [bs, heads, n, n]
        softmax_qk = self.atten(qk)  # [bs, heads, n, n]
        attn_qkv = torch.einsum('b h n n, b h n d -> b h n d', softmax_qk, v)
        attn_qkv = rearrange(attn_qkv, "b h n d -> b n (h d)")  # [bs, n, inner_dim]
        return self.out(attn_qkv)


class FeedForward(nn.Module):
    def __init__(self, input_dim, hidden_dim, dropout):
        super(FeedForward, self).__init__()
        self.mlp = nn.Sequential(
            nn.Linear(input_dim, hidden_dim),
            nn.ELU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim, input_dim)
        )

    def forward(self, x):
        """
        :param x: [batch_size, n, dim]
        :return: [batch_size, n, dim]
        """
        return self.mlp(x)


class Transformer(nn.Module):
    def __init__(self, dim, depth, heads, dim_head, mlp_dim, dropout=0.):
        super(Transformer, self).__init__()
        self.layers = nn.ModuleList([])
        for _ in range(depth):
            self.layers.append(nn.ModuleList([
                PreNorm(dim, Attention(dim=dim, heads=heads, dim_head=dim_head, dropout=dropout)),
                PreNorm(dim, FeedForward(input_dim=dim, hidden_dim=mlp_dim, dropout=dropout)),
            ]))

    def forward(self, x):
        for atten, mlp in self.layers:
            x = atten(x) + x  # residual
            x = mlp(x) + x
        return x


class ViT(nn.Module):
    def __init__(self, *, image_size, patch_size, num_classes,
                 dim, depth, heads, mlp_dim, channels=3,
                 dim_head=64, dropout=0.1, emb_dropout=0.1):
        """
        :param image_size: 默认图片3通道，h == w
        :param patch_size: 划分的子图像大小
        :param num_classes: 图片需要的分类
        :param dim: embedding维度
        :param depth: Transformer 个数
        :param heads: 多头注意力的个数
        :param mlp_dim:
        :param channels: 图片的通道数
        cls: 默认'cls，选取CLS token作为输出，可选'mean'，在patch维度做平均池化
        """
        super(ViT, self).__init__()
        assert image_size % patch_size == 0, 'image dimensions must be divisible by the patch size'
        num_patches = (image_size // patch_size) ** 2  # 分块的数目
        self.patch_size = patch_size  # 图片分块的大小
        # [bs, c, h, w] -> [bs, (h / p， w / p) , (c p p)] -> [bs, n, dim]
        # h * w = num_patches c * p1 * p2 = patch_dim
        self.patch_dim = patch_size * patch_size * channels
        self.to_patch_embedding = nn.Sequential(
            Rearrange("b c (h p1) (w p2) -> b (h w) (c p1 p2)", p1=patch_size, p2=patch_size),
            nn.Linear(self.patch_dim, dim),
            nn.Dropout(emb_dropout)
        )
        self.Position = nn.Parameter(torch.randn(1, num_patches + 1, dim))  # 可学习的位置参数[1,num_patches+1,dim],1为cls位置
        self.cls = nn.Parameter(torch.randn((1, 1, dim)))  # cls 为一个可学习的参数
        self.transformer = Transformer(dim, depth, heads, dim_head, mlp_dim, dropout)
        self.mlp = nn.Sequential(
            nn.LayerNorm(dim),
            nn.Linear(dim, num_classes),
            nn.Dropout(dropout)
        )

    def forward(self, x, mask=None):
        """
        :param x: [batch_size, c, h, w]
        :param mask:
        :return:
        """
        batch_size = x.size()[0]
        x = self.to_patch_embedding(x)  # x: [bs, patch_dim, dim]
        cls = self.cls.repeat(batch_size, 1, 1)
        x = torch.cat((cls, x), dim=1)  # 在patch_dim维度上拼接，将cls放在第0个位置 [bs, num_patches + 1, dim]
        x = x + self.Position.repeat(batch_size, 1, 1)  # position_encoding,  [bs, num_patches + 1, dim]
        x = self.transformer(x)  # [bs, num_patches + 1, dim]
        x = x[:, 0]  # 从x中提取出cls
        x = self.mlp(x)  # [bs, 1, dim] -> [bs, 1, num_classes]
        return x


torch.manual_seed(42)

DOWNLOAD_PATH = '../data/mnist'
BATCH_SIZE_TRAIN = 100
BATCH_SIZE_TEST = 1000

transform_mnist = torchvision.transforms.Compose([torchvision.transforms.ToTensor(),
                                                  torchvision.transforms.Normalize((0.1307,), (0.3081,))])

train_set = torchvision.datasets.MNIST(DOWNLOAD_PATH, train=True, download=False,
                                       transform=transform_mnist)
train_loader = torch.utils.data.DataLoader(train_set, batch_size=BATCH_SIZE_TRAIN, shuffle=True)

test_set = torchvision.datasets.MNIST(DOWNLOAD_PATH, train=False, download=False,
                                      transform=transform_mnist)
test_loader = torch.utils.data.DataLoader(test_set, batch_size=BATCH_SIZE_TEST, shuffle=True)


def train_epoch(model, optimizer, data_loader, loss_history):
    total_samples = len(data_loader.dataset)
    model.train()

    for i, (data, target) in enumerate(data_loader):
        data, target = data.to(device), target.to(device)
        optimizer.zero_grad()
        output = F.log_softmax(model(data), dim=1).to(device)
        loss = F.nll_loss(output, target)
        loss.backward()
        optimizer.step()

        if i % 100 == 0:
            print('[' + '{:5}'.format(i * len(data)) + '/' + '{:5}'.format(total_samples) +
                  ' (' + '{:3.0f}'.format(100 * i / len(data_loader)) + '%)]  Loss: ' +
                  '{:6.4f}'.format(loss.item()))
            loss_history.append(loss.item())


def evaluate(model, data_loader, loss_history):
    model.eval()

    total_samples = len(data_loader.dataset)
    correct_samples = 0
    total_loss = 0

    with torch.no_grad():
        for data, target in data_loader:
            data, target = data.to(device), target.to(device)
            output = F.log_softmax(model(data), dim=1)
            loss = F.nll_loss(output, target, reduction='sum')
            _, pred = torch.max(output, dim=1)

            total_loss += loss.item()
            correct_samples += pred.eq(target).sum()

    avg_loss = total_loss / total_samples
    loss_history.append(avg_loss)
    print('\nAverage test loss: ' + '{:.4f}'.format(avg_loss) +
          '  Accuracy:' + '{:5}'.format(correct_samples) + '/' +
          '{:5}'.format(total_samples) + ' (' +
          '{:4.2f}'.format(100.0 * correct_samples / total_samples) + '%)\n')


start_time = time.time()
'''
patch大小为 7x7（对于 28x28 图像，这意味着每个图像 4 x 4 = 16 个patch）、10 个可能的目标类别（0 到 9）和 1 个颜色通道（因为图像是灰度）。
在网络参数方面，使用了 64 个单元的维度，6 个 Transformer 块的深度，8 个 Transformer 头，MLP 使用 128 维度。'''
model = ViT(image_size=28, patch_size=7, num_classes=10, channels=1,
            dim=64, depth=6, heads=8, mlp_dim=128).to(device)

'''
def __init__(self, *, image_size, patch_size, num_classes,
                 dim, depth, heads, mlp_dim, channels=3,
                 dim_head=64, dropout=0.1, emb_dropout=0.1):
'''
optimizer = torch.optim.Adam(model.parameters(), lr=0.0001)

N_EPOCHS = 1

if __name__ == "__main__":
    train_loss_history, test_loss_history = [], []
    for epoch in range(1, N_EPOCHS + 1):
        print('Epoch:', epoch)
        train_epoch(model, optimizer, train_loader, train_loss_history)
        evaluate(model, test_loader, test_loss_history)
        print('Execution time:', '{:5.2f}'.format(time.time() - start_time), 'seconds')
