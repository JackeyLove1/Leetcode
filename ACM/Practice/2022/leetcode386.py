from typing import List


class Solution:
    def lexicalOrder(self, n: int) -> List[int]:
        return list(map(int, sorted([str(x) for x in range(1, n + 1)])))
