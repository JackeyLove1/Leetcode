import itertools
import collections
class Solution:
    def checkInclusion(self, s1: str, s2: str) -> bool:
        d1 = dict(collections.Counter(s1))
        d2 = dict(collections.Counter(s2))
        for k in d1.keys():
            if k not in d2 or d1[k] > d2[k]:
                return False
        for p in itertools.permutations(s1):
            p = "".join(p)
            if s2.find(p) >= 0:
                return True
        return False