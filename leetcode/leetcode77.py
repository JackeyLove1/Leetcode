import itertools

class Solution:
    def combine(self, n: int, k: int) -> List[List[int]]:
        target = [ i for i in range(1, n+1)]
        res = []
        for p in itertools.combinations(target, k):
            res.append(p)
        return res