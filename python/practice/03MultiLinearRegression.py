# 使用LinearRegression 进行简单的线性回归

# 导入包
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# 导入数据
dataset = pd.read_csv("/Users/arexiusvan/Downloads/100-Days-Of-ML-Code-master/datasets/studentscores.csv")

# 提取数据构造特征
X = dataset.iloc[:, :-1].values
Y = dataset.iloc[:, 4].values

# 由于X的第三列中有非数字元素，需要转化为数字
from sklearn.preprocessing import LabelEncoder, OneHotEncoder
labelencoder = LabelEncoder()
X[:, -1] = labelencoder.fit_transform(X[:, -1])

# 躲避虚拟变量陷阱
X = X[: , 1:]

# 划分训练集和测试集
from sklearn.model_selection import train_test_split
X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size = 0.2, random_state = 0)

# 训练
from sklearn.linear_model import LinearRegression
regressor = LinearRegression()
regressor.fit(X_train, Y_train)

# 预测
y_pred = regressor.predict(X_test)