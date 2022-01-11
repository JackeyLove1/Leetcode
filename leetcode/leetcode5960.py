class Solution:
    def capitalizeTitle(self, title: str) -> str:
        words = title.split(" ")
        res = ""
        for word in words:
            if len(word) == 1 or len(word) == 2:
                res = res + word.lower() + " "
            else:
                res = res + word.capitalize() + " "
        return res[:len(res)-1]
