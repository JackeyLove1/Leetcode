class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        dic = {}
        for num in nums:
            if num in dic:
                dic[num]  += 1
            else:
                dic[num] = 1
        l = list(dic.items())
        l.sort(key = lambda x : x[1], reverse = True)
        res = []
        for i in range(k):
            res.append(l[i][0])
        return res