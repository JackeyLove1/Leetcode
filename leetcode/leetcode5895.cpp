class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        int m = grid.size(), n = grid[0].size();
        vector<int> buff;
        for(vector<int> &line : grid)
            for(int &i : line)
                buff.push_back(i);
        sort(buff.begin(), buff.end());
        for(int &i : buff)
            if((i - buff[0]) % x)
                return -1;
        int mid = m * n / 2;
        int ans = 0;
        for(int &i : buff)
            ans += abs(i - buff[mid]) / x;
        return ans;
    }
};
