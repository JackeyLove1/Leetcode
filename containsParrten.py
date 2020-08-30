from typing import List


def containsPattern(arr: List[int], m: int, k: int) -> bool:
    if m * k > len(arr):
        return False
    arrL = ''.join([str(x) for x in arr])
    for i in range(len(arr)-m):
        tmp = str(arrL[i:m + i] * k)
        print(tmp)
        print(arrL.find(tmp))
        if arrL.find(tmp) >= 0:
            return True
    return False


if __name__ == "__main__":
    # arr = [1, 2, 4, 4, 4, 4]
    # m = 1
    # k = 3
    # print(containsPattern(arr, m, k))
    arr = [2, 3, 4, 4, 6, 2, 6, 6, 5, 3, 5, 1, 4, 3, 3, 5, 2, 5, 1, 2, 3, 3, 5, 4, 6, 1, 2, 6, 4, 2, 4, 4, 3, 2, 6, 4, 4, 2,
       6, 1, 5, 6, 2, 1, 6, 6, 5, 2, 5, 1, 4, 3, 6, 5, 6, 6, 4, 4, 5, 1, 4, 2, 2, 4, 5, 3, 5, 3, 5, 3, 5, 3, 6, 2, 3, 5,
       1, 6, 1, 6, 2, 3, 5, 3, 3, 2, 2, 6, 1, 6, 3, 3, 2, 5, 1]
    m = 4
    k = 2
    print(containsPattern(arr, m, k))
