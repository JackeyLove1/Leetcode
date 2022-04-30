import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import load_iris

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


# Perceptron
# y = w.T * x + b
# loss = (w.T * x + b - y) ** 2
import sklearn.linear_model 


class SkLearnModel(Basic):
    def __init__(self):
        super(SkLearnModel, self).__init__()
        self.model = sklearn.linear_model.Perceptron()

    def fit(self, X, y):
        self.model.fit(X, y)

    def predict(self, X):
        return self.model.predict(X)


class Perceptron(Basic):
    def __init__(self):
        super(Perceptron, self).__init__()
        self.w = np.array([])
        self.b = np.array([0])
        self.num_iterations = 10
        self.learning_rate = 0.01
        self.N = 0

    def sign(self, x, w, b):
        y = np.dot(x, w) + b
        return y

    def fit(self, X, y):
        np.random.seed(1)
        self.N = len(X[0])
        self.w = np.random.normal(0, 0.1, size=self.N)
        self.b = np.zeros(shape=1)
        for iter in range(self.num_iterations):
            for i in range(self.N):
                if y[i] * self.sign(X[i], self.w, self.b) <= 0:
                    self.w = self.w + self.learning_rate * np.dot(y[i], X[i])
                    self.b = self.b + self.learning_rate * y[i]

    def predict(self, X):
        pass


def PerceptronModel():
    model = Perceptron()
    model.fit(X_train, y_train)
    


if __name__ == "__main__":
    PerceptronModel()

