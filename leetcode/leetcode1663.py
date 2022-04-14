class Solution:
    def getSmallestString(self, n: int, k: int) -> str:
        res = ""
        for i in reversed(range(n)):
            for j in reversed(range(27)):
                if k >= i + j:
                    res += chr(ord('a') + j - 1)
                    k -= j
                    break
        return res[::-1]


if __name__ == "__main__":
    s = Solution()
    print(s.getSmallestString(3, 27))
