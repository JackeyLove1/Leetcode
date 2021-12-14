# ML 01 数据预处理
# 导入包
import numpy as np
import pandas as pd

# 导入数据
dataset = pd.read_csv("/datasets/Data.csv")

# 构造简单的特征
X = dataset.iloc[ : , :-1].values # 行，列
Y = dataset.iloc[ : , 3].values

# 数据预处理
from sklearn.impute import SimpleImputer
imputer = SimpleImputer(missing_values=np.nan, strategy='mean')
imputer = imputer.fit(X[ : , 1:3]) # 使用平均值填充
X[ : , 1:3] = imputer.transform(X[ : , 1:3])

# 对标签进行编码
from sklearn.preprocessing import LabelEncoder, OneHotEncoder
labelencoder_X = LabelEncoder()
X[ : , 0] = labelencoder_X.fit_transform(X[ : , 0])
labelencoder_X.fit_transform(X[ : , 1])

# 创建虚拟变量
onehotencoder = OneHotEncoder()
X = onehotencoder.fit_transform(X).toarray()
labelencoder_Y = LabelEncoder()
Y =  labelencoder_Y.fit_transform(Y)

# 划分数据集和测试集
from sklearn.model_selection import train_test_split
X_train, X_test, Y_train, Y_test = train_test_split( X , Y , test_size = 0.2, random_state = 0)

# 特征量化 数据归一化
from sklearn.preprocessing import StandardScaler
sc_X = StandardScaler()
X_train = sc_X.fit_transform(X_train)
X_test = sc_X.transform(X_test)