from typing import List


def kSmallestPairs(nums1: List[int], nums2: List[int], k: int) -> List[List[int]]:
    l = []
    if k <= 0 or len(nums1) == 0 or len(nums2) == 0:
        return l
    for i in range(len(nums1)):
        for j in range(len(nums2)):
            l.append([nums1[i], nums2[j]])
    l.sort(key=lambda x: (x[0] + x[1]))
    return l[:k]


if __name__ == "__main__":
    nums1 = [1, 7, 11]
    nums2 = [2, 4, 6]
    print(kSmallestPairs(nums1, nums2, 3))
