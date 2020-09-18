from typing import List


class Solution:
    def judge(self, s1: str, s2: str):
        s1 = set(s1)
        for s in s2:
            if s in s1:
                return False
        return True

    def maxProduct(self, words: List[str]) -> int:
        res = 0
        for i in range(len(words)):
            for j in range(i, len(words)):
                if self.judge(words[i], words[j]):
                    res = max(res, len(words[i]) * len(words[j]))
        return res
x