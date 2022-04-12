import torch
import torch.nn as nn
import torchvision
import warnings

warnings.filterwarnings("ignore")

# torch加载mnist数据集
DOWNLOAD_PATH = './data'
input_size = 784  # 28 * 28
hidden_size = 500
num_classes = 10
output_size = 10
num_epochs = 10
batch_size = 100
learning_rate = 0.001

device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')

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
LinearNet = nn.Sequential(
    nn.Linear(input_size, hidden_size),
    nn.ReLU(),
    nn.Linear(hidden_size, output_size),
    nn.Sigmoid(),
)


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


model = LinearNet.to(device)
model.apply(weight_init)

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
            images = images.reshape(-1, input_size).to(device)
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
            y_hat = model(X.view(-1, input_size))

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
    model_train()
    model_save()
