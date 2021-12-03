import collections
from typing import List


class Solution:
    def checkIfExist(self, arr: List[int]) -> bool:
        m = collections.Counter(arr)
        for n in arr:
            if n == 0 and m[n] >= 2:
                return True
            if n != 0 and m[n * 2] >= 1:
                return True
        return False
