import torch
from torch.utils.data import Dataset, DataLoader
import numpy as np


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

# 继承Dataset Class
# 实现DataLoader