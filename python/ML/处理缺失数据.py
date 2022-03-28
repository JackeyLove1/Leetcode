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

# SimpleImputer类提供了插补缺失值的基本策略。
# 可以使用提供的常量或使用缺失值所在各列的统计量（平均值，中位数或众数）来估算缺失值。
# 此类还支持不同的缺失值编码
