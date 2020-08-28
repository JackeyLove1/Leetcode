from typing import List
from collections import deque

class Solution:
    def findItinerary(self, tickets: List[List[str]]) -> List[str]:
        dic = {}
        visited = {}
        for i in range(len(tickets)):
            if not visited.get(tickets[i][0]):
                visited[tickets[i][0]] = {}
            visited[tickets[i][0]][tickets[i][1]] = False
            if not dic.get(tickets[i][0]):
                dic[tickets[i][0]] = []
            # print(dic[tickets[i][0]])
            dic[tickets[i][0]].append(tickets[i][1])
        for k in dic.keys():
            dic[k] = sorted(dic[k])
        # print(dic)
        # print(visited)
        res = []
        d = deque()
        res.append("JFK")
        d.append("JFK")
        while d:
            tmp = d.popleft()
            if not dic.get(tmp):
                break
            for i in dic[tmp]:
                if not visited[tmp][i]:
                    # print(i)
                    d.append(i)
                    res.append(i)
                    visited[tmp][i] = True
                    break
        return res
