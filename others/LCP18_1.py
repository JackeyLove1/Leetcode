import itertools
from typing import List
class Solution:
    def breakfastNumber(self, staple: List[int], drinks: List[int], x: int) -> int:
        res = 0
        for item in itertools.product(staple, drinks):
            if item[0] + item[1] <= x:
                res = (res + 1) % 1000000007
        return res
