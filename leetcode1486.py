class Solution:
    def xorOperation(self, n: int, start: int) -> int:
        l = [2*i + start for i in range(n)]
        res = l[0]
        for i in range(1, len(l)):
            res ^= l[i]
        return res