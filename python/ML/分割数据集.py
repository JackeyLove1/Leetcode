# sklearn分割数据集
import sklearn.model_selection as ms
train_x, test_x, train_y, test_y = ms.train_test_split(x, y, test_size=0.25, random_state=7)
