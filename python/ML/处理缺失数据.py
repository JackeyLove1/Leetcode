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

# 使用平均值补充缺失数据
from sklearn.impute import SimpleImputer
imp = SimpleImputer(missing_values=np.nan, strategy='mean')
imp.fit([[1, 2], [np.nan, 3], [7, 6]])
X = [[np.nan, 2], [6, np.nan], [7, 6]]
print(imp.transform(X))

# 当strategy参数设置为'most_frequent'或 'constant'时，SimpleImputer类还支持以字符串或者pandas表示的分类数据。
df = pd.DataFrame([["a", "x"],
                    [np.nan, "y"],
                    ["a", np.nan],
                    ["b", "y"]], dtype="category")
imp = SimpleImputer(strategy="most_frequent")
print(imp.fit_transform(df))

# pandas 重新命名
item_df = item_df.rename(columns={'article_id': 'click_article_id'})  #重命名，方便后续match

