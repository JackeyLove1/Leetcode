import torch
from torch.utils.data import Dataset, DataLoader
import numpy as np

# 自定义dataset
# 继承Dataset Class
# 实现DataLoader
class subDataset(Dataset):
    def __init__(self, Data, Label):
        self.Data = Data
        self.Label = Label

    def __len__(self):
        return len(self.Label)

    def __getitem__(self, item):
        X = torch.tensor(self.Data[item])
        y = torch.tensor(self.Label[item])
        if torch.cuda.is_available():
            X = X.cuda()
            y = y.cuda()
        return X, y


Data = np.array([[1, 2], [3, 4], [5, 6], [7, 8]])
Label = np.array([1, 2, 3, 4])

if __name__ == "__main__":
    dataset = subDataset(Data=Data, Label=Label)
    print(dataset)
    print(dataset.__len__())

    dataloader = DataLoader(dataset=dataset, batch_size=2, shuffle=False, num_workers=4)
    for i, item in enumerate(dataloader):
        print("i: ", i)
        data, label = item
        print("data: ", data)
        print("label: ", label)
        for index in range(len(label)):
            print(data[index])
            print(label[index])

# numpy构建数据集
torch_dataset = Data.TensorDataset(x, y)

loader = Data.DataLoader(
    dataset = torch_dataset,
    batch_size = BATCH_SIZE,
    shuffle = True,# true表示数据每次epoch是是打乱顺序抽样的
    num_workers = 2, # 每次训练有两个线程进行的？？？？？ 改成 1 和 2 暂时没看出区别
)
