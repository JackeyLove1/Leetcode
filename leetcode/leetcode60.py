import itertools


def getPermutation(n: int, k: int) -> str:
    l = list(range(1, n + 1))
    res = list(list(itertools.permutations(l))[k - 1])
    strs = ""
    for i in range(len(res)):
        strs += str(res[i])
    return strs


if __name__ == "__main__":
    print(getPermutation(3, 3))
    print(getPermutation(4, 9))