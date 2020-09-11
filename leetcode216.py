from typing import List
import itertools


def combinationSum3(k: int, n: int) -> List[List[int]]:
    res = []
    for p in itertools.combinations(range(1, 10), k):
        if (sum(p) == n):
            res.append(list(p))
    return res


if __name__ == "__main__":
    print(combinationSum3(3, 7))
    print(combinationSum3(3, 9))
