#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>
#include <cstring>


using namespace std;

class Solution{
public:
    using PII = pair<int, int>;

    static constexpr int N = 6100, INF = 0x3f3f3f3f;

    int e[N], ne[N], h[N], w[N], dist[N], idx;
    bool st[N];

    inline void init(){
        idx = 0;
        memset(dist, 0x3f, sizeof dist);
        memset(h, -1, sizeof h);
        memset(st, 0, sizeof st);
    }

    inline void add(int a, int b, int c){
        e[idx] = b, w[idx] = c,ne[idx] = h[a],  h[a] = idx++;
    }

    inline int dijkstra(int k, int n){
        // cout << "running ... " << endl;
        dist[k] = 0;
        priority_queue<PII, vector<PII>, greater<>> heap;
        heap.push({0, k}); // distance, point
        while (!heap.empty()){
            auto t = heap.top();
            heap.pop();

            auto[distance, ver] = t;
            if(st[ver]) continue;
            st[ver] = true;
            for(int i = h[ver]; i != -1; i = ne[i]){
                // cout <<"i: " << i << endl;
                int j = e[i];
                // cout << "j: " << j << " w[i]: " << w[i] << endl;
                // cout << "dist[j]: " << dist[j] << endl;
                if(dist[j] > distance + w[i]){
                    dist[j] = distance + w[i];
                    heap.push({dist[j], j});
                }
            }
        }
        int res = 0;
        for(int i = 1; i <= n; i++){
            if(dist[i] >= INF / 2) return -1;
            else res = max(res, dist[i]);
        }
        return res;
    }

    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        init();
        for(auto&nums : times ){
            add(nums[0], nums[1], nums[2]);
        }
        return dijkstra(k, n);
    }
};

int main(){
    auto s = new Solution();
    vector<vector<int>> nums = {{2,1,1}, {2,3,1},{3,4,1}};
    int n = 4, k = 2;
    cout << s->networkDelayTime(nums, n, k) << endl;
}