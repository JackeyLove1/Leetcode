class Solution:
    def frequencySort(self, s: str) -> str:
        dic = {}
        for num in s:
            if num in dic:
                dic[num]  += 1
            else:
                dic[num] = 1
        l = list(dic.items())
        l.sort(key = lambda x : x[1], reverse = True)
        res = ""
        for strs, nums in l:
            for i in range(nums):
                res += strs
        return res