import random

class RandomizedSet:

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.l = []
        self.dic = {}

    def insert(self, val: int) -> bool:
        """
        Inserts a value to the set. Returns true if the set did not already contain the specified element.
        """
        if val in self.dic:
            return False
        # 插入list的最后一个位置
        self.dic[val] = len(self.l)
        self.l.append(val)
        return True

    def remove(self, val: int) -> bool:
        """
        Removes a value from the set. Returns true if the set contained the specified element.
        """
        if val in self.dic:
            # move the last element to the place idx of the element to delete
            last_element, idx = self.l[-1], self.dic[val]
            self.l[idx], self.dic[last_element] = last_element, idx
            # delete the last element
            self.l.pop()
            del self.dic[val]
            return True
        return False

    def getRandom(self) -> int:
        """
        Get a random element from the set.
        """
        return random.choice(self.l)

# Your RandomizedSet object will be instantiated and called as such:
# obj = RandomizedSet()
# param_1 = obj.insert(val)
# param_2 = obj.remove(val)
# param_3 = obj.getRandom()
