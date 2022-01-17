class Solution {
public:
    int minMoves(int target, int maxDoubles) {
        if (target == 1) return 0;
        int cnt = 0;
        while (target % 2 == 0 && maxDoubles > 0) {
            ++cnt;
            target = target / 2;
            --maxDoubles;
            return minMoves(target, maxDoubles) + cnt;
        }
        if(maxDoubles == 0){
            return target - 1;
        }
        return minMoves(target - 1, maxDoubles) + 1;
    }
};

int main() {
    Solution s;
    cout << s.minMoves(5, 0) << " res: 4" << endl;
    cout << s.minMoves(19, 2) << " res: 7" << endl;
    cout << s.minMoves(766972377, 92) << " res: 45" << endl;
    cout << s.minMoves(656101987, 1) << "res: ? " << endl;
}