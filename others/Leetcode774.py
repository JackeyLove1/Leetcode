from typing import List


class Solution:
    def nextGreatestLetter(letters: List[str], target: str) -> str:
        seen = set(letters)
        for i in range(1, 27):
            cand = chr((ord(target) - ord('a') + i) % 26 + ord('a'))
            if cand in seen:
                return cand


def main():
    print(Solution.nextGreatestLetter(['c', 'f', 'j'], 'a'))


if __name__ == '__main__':
    main()
