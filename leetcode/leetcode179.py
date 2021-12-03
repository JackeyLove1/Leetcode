from typing import List
from collections import deque
import functools


def compare(str1, str2):
    if str1 + str2 > str2 + str1:
        return 1
    return -1


def largestNumber(nums: List[int]) -> str:
    strs = [str(num) for num in nums]
    strs.sort(reverse=True, key=functools.cmp_to_key(compare))
    res = ""
    for s in strs:
        res += s
    return res


if __name__ == "__main__":
    numbers = [3, 30, 34, 5, 9]
    print(largestNumber(numbers))
    # print( "4"+"4">"4"+"3")
    numbers2 = [10,2]
    print(largestNumber(numbers2))