from typing import List


def kthSmallest(matrix: List[List[int]], k: int) -> int:
    l = []
    for i in range(len(matrix)):
        l.extend(matrix[i])
    l.sort()
    return l[k-1]

if __name__ == "__main__":
    matrix = [
        [1, 5, 9],
        [10, 11, 13],
        [12, 13, 15]
    ]
    k = 8
    print(kthSmallest(matrix, k))
