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
# cifa10
import torchvision.transforms as transforms
transform = transforms.Compose(
    [transforms.ToTensor(),
     transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))])

trainset = torchvision.datasets.CIFAR10(root='./data', train=True,
                                        download=True, transform=transform)
trainloader = torch.utils.data.DataLoader(trainset, batch_size=4,
                                          shuffle=True, num_workers=2)

testset = torchvision.datasets.CIFAR10(root='./data', train=False,
                                       download=True, transform=transform)
testloader = torch.utils.data.DataLoader(testset, batch_size=4,
                                         shuffle=False, num_workers=2)

classes = ('plane', 'car', 'bird', 'cat',
           'deer', 'dog', 'frog', 'horse', 'ship', 'truck')

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
X, y = datasets.load_iris(return_X_y=True)

# 加载boston房价数据集
from sklearn.datasets import load_boston
X, y = load_boston(return_X_y=True)

# 加载糖尿病数据集
sklearn.datasets.load_diabetes(*, return_X_y=False, as_frame=False)

# 加载数字数据集
sklearn.datasets.load_digits(*, n_class=10, return_X_y=False, as_frame=False)

# 加载乳腺癌数据集
sklearn.datasets.load_breast_cancer(*, return_X_y=False, as_frame=False)

# load_array, data_iter即为迭代器
true_w = torch.tensor([2, -3.4])
true_b = 4.2
features, labels = d2l.synthetic_data(true_w, true_b, 1000)
def load_array(data_arrays, batch_size, is_train=True):  #@save
    """构造一个PyTorch数据迭代器"""
    dataset = data.TensorDataset(*data_arrays)
    return data.DataLoader(dataset, batch_size, shuffle=is_train)
batch_size = 10
data_iter = load_array((features, labels), batch_size)

# MNIST数据集
from torchvision import datasets

data_root = './output/mnist'
num_workers = 4
batch_size = 64

dataset = datasets.MNIST(root=data_root, download=True, transform=None)
dataloader = DataLoader(dataset, batch_size=batch_size, shuffle=True, num_workers=num_workers)

# Fashion MNIST数据集
data_root = './fasionmnist'
dataset = datasets.FashionMNIST(root=data_root, download=True, transform=None)
dataloader = DataLoader(dataset, batch_size=batch_size, shuffle=True, num_workers=num_workers)

# ImageNet
data_root = './imagenet'
dataset = datasets.ImageNet(root=data_root, split='train', download=True, transform=None)
dataloader = DataLoader(dataset, batch_size=batch_size, shuffle=True, num_workers=num_workers)

# cifa10      
data_root = './cifar10'
dataset = datasets.CIFAR10(root=data_root, download=True, transform=None)
dataloader = DataLoader(dataset, batch_size=batch_size, shuffle=True, num_workers=num_workers)

# cifa10
#超参数定义
EPOCH = 100
BATCH_SIZE = 64
LR = 0.001
#数据集加载
transform_train = transforms.Compose([
    transforms.RandomHorizontalFlip(),
    transforms.RandomGrayscale(),
    transforms.ToTensor(),
    transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))])
transform_test = transforms.Compose([     
    transforms.ToTensor(),
    transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))])
#将数据加载进来，本地已经下载好， root=os.getcwd()为自动获取与源码文件同级目录下的数据集路径   
train_data = datasets.CIFAR10(root=os.getcwd(), train=True,transform=transform_train,download=False)
test_data =datasets.CIFAR10(root=os.getcwd(),train=False,transform=transform_test,download=False)
#数据分批
from torch.utils.data import DataLoader
train_loader = DataLoader(dataset=train_data,batch_size=BATCH_SIZE,shuffle=True,num_workers=2)
test_loader = DataLoader(dataset=test_data,batch_size=BATCH_SIZE,shuffle=True,num_workers=2)

