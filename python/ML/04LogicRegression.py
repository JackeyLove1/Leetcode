# 使用LinearRegression 进行简单的线性回归

# 导入包
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# 导入数据
dataset = pd.read_csv("/Users/arexiusvan/Downloads/100-Days-Of-ML-Code-master/datasets/Social_Network_Ads.csv")

# 构造数据
X = dataset.iloc[:, [2,3]].values
Y = dataset.iloc[:, -1].values

# 转化标签
# 填充空白数据

# 划分数据集和测试集合
from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, Y, test_size = 0.25, random_state = 0)

# 数据归一化
from sklearn.preprocessing import StandardScaler
sc = StandardScaler()
X_train = sc.fit_transform(X_train)
X_test = sc.transform(X_test)

from sklearn.linear_model import LogisticRegression
classifier = LogisticRegression()
classifier.fit(X_train, y_train)

# predict
y_pred = classifier.predict(X_test)
