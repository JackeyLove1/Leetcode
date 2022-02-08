# 使用插值的方法处理缺失的数据
# iloc : index location 
inputs, outputs = data.iloc[:, 0:2], data.iloc[:, 2]
inputs = inputs.fillna(inputs.mean()) # 使用平均值插值
print(inputs)

# 将NaN视为一个类别，建为一个全新的类
inputs = pd.get_dummies(inputs, dummy_na=True)
print(inputs)

# 将处理好的数据转化为tensor
import torch
X, y = torch.tensor(inputs.values), torch.tensor(outputs.values)
X, y
