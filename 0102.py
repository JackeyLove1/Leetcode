class Solution:
    def CheckPermutation(self, s1: str, s2: str) -> bool:
        s1 = sorted(s1)
        s2 = sorted(s2)
        return s1 == s2