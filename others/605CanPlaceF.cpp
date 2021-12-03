#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

bool canPlaceFlowers(vector<int> &flowerbed, int n) {
    if (flowerbed.empty()) return false;
    int s = flowerbed.size();
    if (s == 1) {
        if (n == 0 || (n == 1 && flowerbed[0] == 0)) return true;
        else return false;
    }
    if (flowerbed[0] == 0 && flowerbed[1] == 0) {
        flowerbed[0] = 1;
        n--;
    }
    for (int i = 1; i < flowerbed.size() - 1; i++) {
        if (flowerbed[i - 1] == 0 && flowerbed[i + 1] == 0 && flowerbed[i] == 0) {
            flowerbed[i] = 1;
            n--;
        }
    }
    if (flowerbed[s - 1] == 0 && flowerbed[s - 2] == 0) {
        flowerbed[s - 1] == 0;
        n--;
    }
    if (n <= 0) return true;
    return false;
}

int main() {
    vector<int> nums = {0, 1, 0};
    cout << canPlaceFlowers(nums, 1) << endl;
    cout << canPlaceFlowers(nums, 0) << endl;
    vector<int> nums1 = {1, 0, 0, 0, 1};
    cout << canPlaceFlowers(nums1, 1) << endl;
    cout << canPlaceFlowers(nums1, 2) << endl;
    return 0;
}