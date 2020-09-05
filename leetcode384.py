from typing import List
import random
import copy

class Solution:

    def __init__(self, nums: List[int]):
        self.l1 = nums
        self.l2 = copy.deepcopy(nums)

    def reset(self) -> List[int]:
        """
        Resets the array to its original configuration and return it.
        """
        return self.l2

    def shuffle(self) -> List[int]:
        """
        Returns a random shuffling of the array.
        """
        random.shuffle(self.l1)
        return self.l1

# Your Solution object will be instantiated and called as such:
# obj = Solution(nums)
# param_1 = obj.reset()
# param_2 = obj.shuffle()
