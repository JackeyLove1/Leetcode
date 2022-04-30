import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import load_iris
from collections import Counter
import time

# load datasets
X, y = load_iris(return_X_y=True)

# split train_data and test_data
from sklearn.model_selection import train_test_split

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.4, random_state=0)


class Basic(object):
    def __init__(self):
        pass

    def fit(self, X, y):
        pass

    def predict(self, X):
        pass

    def score(self, X_test, y_test):
        pass


class SklearnKNN(object):
    def __init__(self):
        pass

    def fit(self, X, y):
        pass

    def predict(self, X):
        pass

    def score(self, X_test, y_test):
        pass


# 将每个点对训练集中所有的点求L2距离，然后排序求最近N个点的投票
class KNN(Basic):
    def __init__(self, n_neighbors=10, l=2, mode="classify"):
        super(KNN, self).__init__()
        self.X = None
        self.y = None
        self.N = 0
        self.n_neighbors = n_neighbors
        self.L = l
        self.mode = mode

    def fit(self, X, y):
        self.N = len(X)
        self.X = X
        self.y = y

    def perdict_one(self, x):
        dist = None
        if self.L == 1:
            dist = self.l1_norm(x)
        else:
            dist = self.l2_norm(x)
        sorted_idx = np.argsort(dist)
        k_neighbors = self.y[sorted_idx[:self.n_neighbors]]
        if (self.mode == "classify"):
            return Counter(k_neighbors).most_common(1)[0][0]
        else:
            return np.mean(k_neighbors)

    def predict(self, X):
        y_pred = []
        for i in range(len(X)):
            y_pred.append(self.perdict_one(X[i]))
        return np.array(y_pred)

    def score(self, X_test, y_test):
        y_pred = self.predict(X_test)
        correct = 0
        for i in range(len(y_pred)):
            if y_pred[i] == y_test[i]:
                correct += 1
        return float(correct) / float(len(y_test))

    def l1_norm(self, X):
        # using broadcast mechanism
        return np.sum(np.abs(X - self.X), axis=1)

    def l2_norm(self, X):
        return np.sum(np.square(X - self.X), axis=1)


def main():
    start = time.time()
    model = KNN()
    model.fit(X_train, y_train)
    accuracy = model.score(X_test, y_test)
    print("Test Accuracy is: ", accuracy)
    print("Cost time: ", time.time() - start)


if __name__ == "__main__":
    main()
