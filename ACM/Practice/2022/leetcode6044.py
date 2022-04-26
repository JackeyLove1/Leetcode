from typing import List
import bisect


class Solution:
    def fullBloomFlowers(self, flowers: List[List[int]], persons: List[int]) -> List[int]:
        start = sorted([s for s, _ in flowers])
        end = sorted([e for _, e in flowers])
        return [bisect.bisect_right(start, p) - bisect.bisect_left(end, p) for p in persons]
