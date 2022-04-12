import numpy as np
import pandas as pd
from tensorflow.keras.layers import *
import tensorflow.keras.backend as K
import matplotlib.pyplot as plt
import tensorflow as tf
from tensorflow.keras.models import Model
from tensorflow.keras.utils import plot_model

# 加载数据
data = pd.read_csv('criteo_sampled_data.csv')
data.shape
cols = data.columns.values

# 数据预处理
dense_feats = [f for f in cols if f[0] == "I"] # 数值型特征
sparse_feats = [f for f in cols if f[0] == "C"] # 离散型特征
# 处理Dense特征
def process_dense_feats(data, feats):
    d = data.copy()
    d = d[feats].fillna(0.0)
    for f in feats:
        d[f] = d[f].apply(lambda x: np.log(x+1) if x > -1 else -1)
    
    return d
data_dense = process_dense_feats(data, dense_feats)

# 处理离散型特征
from sklearn.preprocessing import LabelEncoder
def process_sparse_feats(data, feats):
    d = data.copy()
    d = d[feats].fillna("-1")
    for f in feats:
        label_encoder = LabelEncoder()
        d[f] = label_encoder.fit_transform(d[f])
        
    return d
data_sparse = process_sparse_feats(data, sparse_feats)
# 合并数据集
total_data = pd.concat([data_dense, data_sparse], axis=1)
total_data['label'] = data['label']

# 一阶特征
# 构造 dense 特征的输入
dense_inputs = []
for f in dense_feats:
    _input = Input([1], name=f)
    dense_inputs.append(_input)
# 将输入拼接到一起，方便连接 Dense 层
concat_dense_inputs = Concatenate(axis=1)(dense_inputs)  # ?, 13
# 然后连上输出为1个单元的全连接层，表示对 dense 变量的加权求和
fst_order_dense_layer = Dense(1)(concat_dense_inputs)  # ?, 1

# 构造Sparse特征输入
# 这里单独对每一个 sparse 特征构造输入，
# 目的是方便后面构造二阶组合特征
sparse_inputs = []
for f in sparse_feats:
    _input = Input([1], name=f)
    sparse_inputs.append(_input)
    
sparse_1d_embed = []
for i, _input in enumerate(sparse_inputs):
    f = sparse_feats[i]
    voc_size = total_data[f].nunique()
    # 使用 l2 正则化防止过拟合
    reg = tf.keras.regularizers.l2(0.5)
    _embed = Embedding(voc_size, 1, embeddings_regularizer=reg)(_input)
    # 由于 Embedding 的结果是二维的，
    # 因此如果需要在 Embedding 之后加入 Dense 层，则需要先连接上 Flatten 层
    _embed = Flatten()(_embed)
    sparse_1d_embed.append(_embed)
# 对每个 embedding lookup 的结果 wi 求和
fst_order_sparse_layer = Add()(sparse_1d_embed)

# Linear特征合并
linear_part = Add()([fst_order_dense_layer, fst_order_sparse_layer])

# 二阶特征
# embedding size
k = 8

# 只考虑sparse的二阶交叉
sparse_kd_embed = []
for i, _input in enumerate(sparse_inputs):
    f = sparse_feats[i]
    voc_size = total_data[f].nunique()
    reg = tf.keras.regularizers.l2(0.7)
    _embed = Embedding(voc_size, k, embeddings_regularizer=reg)(_input)
    sparse_kd_embed.append(_embed)

# 1.将所有sparse的embedding拼接起来，得到 (n, k)的矩阵，其中n为特征数，k为embedding大小
concat_sparse_kd_embed = Concatenate(axis=1)(sparse_kd_embed)  # ?, n, k

# 2.先求和再平方
sum_kd_embed = Lambda(lambda x: K.sum(x, axis=1))(concat_sparse_kd_embed)  # ?, k
square_sum_kd_embed = Multiply()([sum_kd_embed, sum_kd_embed])  # ?, k

# 3.先平方再求和
square_kd_embed = Multiply()([concat_sparse_kd_embed, concat_sparse_kd_embed]) # ?, n, k
sum_square_kd_embed = Lambda(lambda x: K.sum(x, axis=1))(square_kd_embed)  # ?, k

# 4.相减除以2
sub = Subtract()([square_sum_kd_embed, sum_square_kd_embed])  # ?, k
sub = Lambda(lambda x: x*0.5)(sub)  # ?, k
snd_order_sparse_layer = Lambda(lambda x: K.sum(x, axis=1, keepdims=True))(sub)  # ?, 1

# DNN部分
flatten_sparse_embed = Flatten()(concat_sparse_kd_embed)  # ?, n*k

fc_layer = Dropout(0.5)(Dense(256, activation='relu')(flatten_sparse_embed))  # ?, 256
fc_layer = Dropout(0.3)(Dense(256, activation='relu')(fc_layer))  # ?, 256
fc_layer = Dropout(0.1)(Dense(256, activation='relu')(fc_layer))  # ?, 256

fc_layer_output = Dense(1)(fc_layer)  # ?, 1

output_layer = Add()([linear_part, snd_order_sparse_layer, fc_layer_output])
output_layer = Activation("sigmoid")(output_layer)

# 模型编译
model = Model(dense_inputs+sparse_inputs, output_layer)
model.summary()
model.compile(optimizer="adam", 
              loss="binary_crossentropy", 
              metrics=["binary_crossentropy", tf.keras.metrics.AUC(name='auc')])

# 训练
train_data = total_data.loc[:500000-1]
valid_data = total_data.loc[500000:]

train_dense_x = [train_data[f].values for f in dense_feats]
train_sparse_x = [train_data[f].values for f in sparse_feats]

train_label = [train_data['label'].values]

val_dense_x = [valid_data[f].values for f in dense_feats]
val_sparse_x = [valid_data[f].values for f in sparse_feats]

val_label = [valid_data['label'].values]

model.fit(train_dense_x+train_sparse_x, 
          train_label, epochs=5, batch_size=256,
          validation_data=(val_dense_x+val_sparse_x, val_label),
         )
         
