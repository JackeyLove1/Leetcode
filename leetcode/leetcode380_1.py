def sumr(seq):
    if len(seq) == 0:
        return 0
    return seq[0] + sumr(seq[1:])


def sumr2(val):
    """
    :param val: a value
    :return: sum of from 1 to value which val % 3 or val % 5
    """
    return sum(n for n in range(val) if n % 3 == 0 or n % 5 == 0)


def m(n: int) -> int:
    return 2 ** n - 1


from typing import Callable


class Mersennel:
    def __init__(self, algorithm: Callable[[int], int]) -> None:
        self.pow2 = algorithm

    def __call__(self, args: int, **kwargs) -> int:
        return self.pow2(args) - 1


def shifty(b: int) -> int:
    return 1 << b


m1s = Mersennel(shifty)

import numpy as np


class RandomizedSet:

    def __init__(self):
        self.dicts = {}

    def insert(self, val: int) -> bool:
        if self.dicts.get(val) is None:
            self.dicts[val] = 1
            return True
        return False

    def remove(self, val: int) -> bool:
        if self.dicts.get(val) is None:
            return False
        del self.dicts[val]
        return True

    def getRandom(self) -> int:
        return list(self.dicts.keys())[np.random.randint(0, max(1, len(self.dicts)))]


# Your RandomizedSet object will be instantiated and called as such:
# obj = RandomizedSet()
# param_1 = obj.insert(val)
# param_2 = obj.remove(val)
# param_3 = obj.getRandom()

if __name__ == "__main__":
    print(sumr([1, 2, 3, 4, 5]))
    print(sumr2(10))
    r = RandomizedSet()
    print(r.insert(1))
    print(r.remove(2))
    print(r.insert(2))
    print(r.getRandom())
