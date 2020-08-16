from typing import List


class Solution:
    def judge(self, nums: List[int]):
        for i in range(len(nums) - 1):
            if nums[i] > nums[i + 1]:
                return False
        return True

    def checkPossibility(self, nums: List[int]) -> bool:
        for i in range(len(nums)):
            // get deep copy
            l = nums.copy()
            l.pop(i)
            if (self.judge(l)):
                return True
        return False
