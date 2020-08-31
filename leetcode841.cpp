#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <deque>

using namespace std;

bool canVisitAllRooms(vector<vector<int>>& rooms) {
    // 本质上是一个图的遍历问题
    // 给你一个邻接矩阵，看图是否能被遍历
    int n = rooms.size();
    vector<bool> visited(n, false);
    deque<int> bfs;
    bfs.push_back(0);
    while (!bfs.empty()){
        int node = bfs.front();
        visited[node] = true;
        bfs.pop_front();
        for(auto num : rooms[node]){
            if(!visited[num])
                bfs.push_back(num);
        }
    }
    for(auto flag : visited){
        if(!flag)
            return false;
    }
    return true;
}