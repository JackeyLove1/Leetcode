import torch
import torch.nn as nn
import torchvision
import torchvision.models as models
import torchvision.transforms as transforms
import warnings

warnings.filterwarnings('ignore')

# torch加载mnist数据集
DOWNLOAD_PATH = './data'
input_size = 784  # 28 * 28
hidden_size = 500
num_classes = 10
out_features = 1000
num_epochs = 100
batch_size = 100
learning_rate = 0.00015
dropout = 0.1

device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
print("use device: ", device)
# load dataset
transform_mnist = torchvision.transforms.Compose([torchvision.transforms.ToTensor(),
                                                  torchvision.transforms.Normalize((0.1307,), (0.3081,))])

train_set = torchvision.datasets.MNIST(DOWNLOAD_PATH, train=True, download=True,
                                       transform=transform_mnist)
train_loader = torch.utils.data.DataLoader(train_set, batch_size=batch_size, shuffle=True)

test_set = torchvision.datasets.MNIST(DOWNLOAD_PATH, train=False, download=True,
                                      transform=transform_mnist)
test_loader = torch.utils.data.DataLoader(test_set, batch_size=batch_size, shuffle=True)


# model
# resnet18: in_features=512, out_features=1000
def get_model():
    model = nn.Sequential(
        models.mobilenet_v3_large(pretrained=True),
        nn.Linear(out_features, hidden_size),
        nn.ReLU(),
        nn.Dropout(dropout),
        nn.Linear(hidden_size, num_classes),
        nn.Sigmoid(),
    )
    return model.to(device)


# init
def weight_init(m):
    classname = m.__class__.__name__
    if classname.find('Conv2d') != -1:
        torch.nn.init.normal_(m.weight.data)
        torch.nn.init.constant_(m.bias.data, 0.0)
    elif classname.find('Linear') != -1:
        torch.nn.init.normal_(m.weight)
        torch.nn.init.constant_(m.bias, 0.0)
    elif classname.find('BatchNorm2d') != -1:
        torch.nn.init.normal_(m.weight.data, 1.0, 0.02)
        torch.nn.init.constant_(m.bias.data, 0.0)


def model_init(model):
    return model.apply(weight_init)


model = get_model()
# tools
optimizer = torch.optim.SGD(model.parameters(), lr=learning_rate)
criterion = nn.CrossEntropyLoss()


# test
def model_test():
    model.eval()
    with torch.no_grad():
        correct = 0
        total = 0
        for images, labels in test_loader:
            images = images.to(device)
            images = images.repeat(1, 3, 1, 1)
            labels = labels.to(device)
            outputs = model(images)
            _, predicted = torch.max(outputs.data, dim=1)
            total += labels.size()[0]
            correct += (labels == predicted).sum().item()
        print("Accuracy: {}".format(100 * correct / total))


# train
# X [100, 1, 28, 28], y [100]
def model_train():
    for epoch in range(num_epochs):
        model.train()
        for i, (X, y) in enumerate(train_loader):
            X, y = X.to(device), y.to(device)
            X = X.repeat(1, 3, 1, 1)
            y_hat = model(X)

            optimizer.zero_grad()
            loss = criterion(y_hat, y)
            loss.backward()
            optimizer.step()

            if (i + 1) % 100 == 0:
                print("epoch: {}, step: {}/{}, loss: {}".format(epoch + 1, i + 1, len(train_loader), loss.item()))
        model_test()


def model_save():
    torch.save(model.state_dict(), './model.ckpt')


if __name__ == '__main__':
    # print(model)
    model_train()
    # model_save()
