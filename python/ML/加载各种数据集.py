# 导入必要的包
import torch 
import torchvision 

# torch加载mnist数据集
DOWNLOAD_PATH = './data'
BATCH_SIZE_TRAIN = 100
BATCH_SIZE_TEST = 1000

transform_mnist = torchvision.transforms.Compose([torchvision.transforms.ToTensor(),
                                                  torchvision.transforms.Normalize((0.1307,), (0.3081,))])

train_set = torchvision.datasets.MNIST(DOWNLOAD_PATH, train=True, download=True,
                                       transform=transform_mnist)
train_loader = torch.utils.data.DataLoader(train_set, batch_size=BATCH_SIZE_TRAIN, shuffle=True)

test_set = torchvision.datasets.MNIST(DOWNLOAD_PATH, train=False, download=True,
                                      transform=transform_mnist)
test_loader = torch.utils.data.DataLoader(test_set, batch_size=BATCH_SIZE_TEST, shuffle=True)

# C10
# 准备数据集
train_data = torchvision.datasets.CIFAR10(root="./data", train=True,
                                          transform=torchvision.transforms.ToTensor(),
                                          download=True)

test_data = torchvision.datasets.CIFAR10(root="./data", train=False,
                                         transform=torchvision.transforms.ToTensor(),
                                         download=True)

# 查看数据集的长度
train_data_size = len(train_data)
test_data_size = len(test_data)

# 查看训练集的长度
print("训练数据集的长度为{}".format(train_data_size))
print('**' * 20)
print("测试数据集的长度为{}".format(test_data_size))

# 加载数据集
train_dataloader = DataLoader(train_data, batch_size=64)
test_dataloader = DataLoader(test_data, batch_size=64)

# 加载iris数据集
sklearn.datasets.load_iris(*, return_X_y=False, as_frame=False


# 加载boston房价数据集
from sklearn.datasets import load_boston
X, y = load_boston(return_X_y=True)

# 加载糖尿病数据集
sklearn.datasets.load_diabetes(*, return_X_y=False, as_frame=False)

# 加载数字数据集
sklearn.datasets.load_digits(*, n_class=10, return_X_y=False, as_frame=False)

# 加载乳腺癌数据集
sklearn.datasets.load_breast_cancer(*, return_X_y=False, as_frame=False)

