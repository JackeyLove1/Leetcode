from typing import List


def judgeLetters(s: str, maxLetters: int):
    s = set(s)
    return len(s) <= maxLetters


def findSub(s: str, maxLetters: int, minSize: int, maxSize: int):
    l = []
    for i in range(len(s)):
        for j in range(minSize, maxSize + 1):
            strs = s[i:i + j]
            if (judgeLetters(strs, maxLetters) and len(strs) >= minSize):
                l.append(strs)
    # print(l)
    return l

def count(s: str, substr: str):
    l = len(substr)
    cnt = 0
    for i in range(len(s)):
        if s[i:i+l] == substr:
            cnt += 1
    return cnt

def maxFreq(s: str, maxLetters: int, minSize: int, maxSize: int) -> int:
    l = findSub(s, maxLetters, minSize, maxSize)
    res = 0
    for i in range(len(l)):
        res = max(res, count(s, l[i]))
    return res


if __name__ == "__main__":
    print(maxFreq("aababcaab", 2, 3, 4))
    print(maxFreq("aaaa", 1, 3, 3))
    print(maxFreq("aabcabcab", 2, 2, 3))
    print(maxFreq("abcde", 2, 3, 3))
