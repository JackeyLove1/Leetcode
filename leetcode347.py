from typing import List
import collections


def topKFrequent(nums: List[int], k: int) -> List[int]:
    w = dict(collections.Counter(nums))
    l = list(w.items())
    l.sort(key=lambda x:x[1], reverse=True)
    res = [l[i][0] for i in range(k)]
    return res

if __name__ == "__main__":
    print(topKFrequent([1, 1, 1, 2, 2, 3], 2))
