class Solution {
public:
    bool isRectangleOverlap(vector<int> &rec1, vector<int> &rec2) {
        bool x_overlap = !(rec1[2] <= rec2[0] || rec2[2] <= rec1[0]);
        bool y_overlap = !(rec1[3] <= rec2[1] || rec2[3] <= rec1[1]);
        return x_overlap && y_overlap;
    }
};