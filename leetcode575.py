class Solution:
    def distributeCandies(self, candies: List[int]) -> int:
        l = len(candies)
        half_l = l // 2
        s = len(set(candies))
        if s < half_l:
            return s 
        else:
            return half_l 