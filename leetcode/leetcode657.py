class Solution:
    def judgeCircle(self, moves: str) -> bool:
        l = [0, 0]
        for c in moves:
            if c == 'U':
                l[0] += 1
            elif c == 'D':
                l[0] -= 1
            elif c == 'L':
                l[1] += 1
            else:
                l[1] -= 1
        if l == [0, 0]:
            return True
        return False