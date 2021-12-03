from typing import List
import itertools

def subsets(nums: List[int]) -> List[List[int]]:
    res = []
    for i in range(len(nums)+1):
        for p in itertools.combinations(nums, i):
            res.append(list(p))
    return res

if __name__ == "__main__":
    nums = [1,2,3]
    print(subsets(nums))