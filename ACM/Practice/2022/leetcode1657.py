from collections import Counter


class Solution:
    def closeStrings(self, word1: str, word2: str) -> bool:
        c1, c2 = Counter(word1), Counter(word2)
        f1 = sorted(c1.keys()) == sorted(c2.keys())
        f2 = sorted(c1.values()) == sorted(c2.values())
        return f1 and f2
