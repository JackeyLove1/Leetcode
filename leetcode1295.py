class Solution:
    def findNumbers(self, nums: List[int]) -> int:
        l = [len(str(i))%2==0 for i in nums]
        return l.count(True)
