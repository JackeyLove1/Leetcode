from collections import Counter
from typing import List


class Solution:
    def mostCommonWord(self, paragraph: str, banned: List[str]) -> str:
        replaceList = [",", "!", "?", ":", ".", "'"]
        for ch in replaceList:
            paragraph = paragraph.replace(ch, " ")
        print(paragraph)
        wordCounter = Counter(paragraph.lower().split(" "))
        print(wordCounter)
        keys = sorted(wordCounter.keys(), key=lambda k: wordCounter[k], reverse=True)
        print(keys)
        for k in keys:
            if k not in banned and k != '' and k != ' ':
                return k
        return ""


if __name__ == "__main__":
    paragraph = "Bob hit a ball, the hit BALL flew far after it was hit."
    banned = ["hit"]
    s = Solution()
    # print("res: ", s.mostCommonWord(paragraph, banned))
    print('res: ', s.mostCommonWord("Bob. hIt, baLl", ["bob", "hit"]))
