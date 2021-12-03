from typing import List
import collections

def findLucky(arr: List[int]) -> int:
    l = list(collections.Counter(arr).items())
    l.sort(key=lambda x:x[1], reverse=True)
    for i in range(len(l)):
        if l[i][0] == l[i][1]:
            return l[i][0]
    return -1

if __name__ == "__main__":
    print(findLucky([2,2,3,4]))