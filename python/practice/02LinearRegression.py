# 使用LinearRegression 进行简单的线性回归

# 导入包
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# 导入数据
dataset = pd.read_csv("/Users/arexiusvan/Downloads/100-Days-Of-ML-Code-master/datasets/studentscores.csv")

# 提取数据构造特征
X = dataset.iloc[:, :1].values
Y = dataset.iloc[:, 1].values

# 分割训练集和测试集
from sklearn.model_selection import train_test_split
X_train, X_test, Y_train, Y_test = train_test_split( X, Y, test_size = 1/4, random_state = 0)

# 导入LinearRegression进行拟合
from sklearn.linear_model import LinearRegression
regressor = LinearRegression()
regressor = regressor.fit(X_train, Y_train)

# 预测结果
Y_pred = regressor.predict(X_test)

# 可视化
plt.scatter(X_train , Y_train, color = 'red')
plt.plot(X_train , regressor.predict(X_train), color ='blue')
plt.show()

# 测试集可视化
plt.scatter(X_test , Y_test, color = 'red')
plt.plot(X_test , regressor.predict(X_test), color ='blue')
plt.show()