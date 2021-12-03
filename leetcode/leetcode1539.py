from typing import List
class Solution:
    def findKthPositive(self, arr: List[int], k: int) -> int:
        n = max(arr)
        l = list(range(1, n + 1 + k))
        for num in arr:
            l.remove(num)
        return l[k - 1]