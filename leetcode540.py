class Solution:
    def singleNonDuplicate(self, nums: List[int]) -> int:
        return sum(set(nums))*2 - sum(nums)