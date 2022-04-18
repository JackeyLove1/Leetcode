class Solution:
    def countEven(self, num: int) -> int:
        cnt = 0
        for number in range(1, num+1):
            if sum([int(c) for c in str(number)]) % 2 == 0:
                cnt += 1
        return cnt