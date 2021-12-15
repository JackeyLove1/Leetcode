import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

dataset = pd.read_csv("/Users/arexiusvan/Downloads/100-Days-Of-ML-Code-master/datasets/Social_Network_Ads.csv")

X = dataset.iloc[:, [2, 3]].values
y = dataset.iloc[:, 4].values

# 划分数据集和测试集
from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.25, random_state = 0)

# 数据缩放
from sklearn.preprocessing import StandardScaler
sc = StandardScaler()
X_train = sc.fit_transform(X_train)
X_test = sc.transform(X_test)

# 构建分类器
from sklearn.neighbors import KNeighborsClassifier
classifier = KNeighborsClassifier(n_neighbors = 5, metric = 'minkowski', p = 2)
classifier.fit(X_train, y_train)

# 预测
y_pred = classifier.predict(X_test)

# 构建混淆矩阵
from sklearn.metrics import confusion_matrix
cm = confusion_matrix(y_test, y_pred)