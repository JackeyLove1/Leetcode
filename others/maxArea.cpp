#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <cmath>

using namespace std;

int maxArea(vector<int> &height) {
    int maxArea = 0;
    int left = 0, right = height.size() - 1;
    while (left < right) {
        maxArea = max(maxArea, min(height[left], height[right]) * (right - left));
        if (height[left] > height[right])
            right--;
        else
            left++;
    }
    return maxArea;
}

int main() {
    vector<int> nums = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << maxArea(nums) << endl;
    return 0;
}