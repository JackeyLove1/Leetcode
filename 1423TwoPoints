#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;

int maxScore(vector<int> &cardPoints, int k) {
    size_t size = cardPoints.size();
    int sum = 0;
    for (int i = 0; i < k; i++) {
        sum += cardPoints[i];
    }
    int res = sum;
    for(int i = 0;i<k;i++){
        sum = sum + cardPoints[size - i - 1] - cardPoints[k-i-1];
        res = max(res, sum);
    }
    return res;
}

int main(){
    vector<int> v = {1,79,80,1,1,1,200,1};
    cout<<maxScore(v,3)<<endl;
    vector<int> v1 = {1,2,3,4,5,6,1};
    cout<<maxScore(v1,3)<<endl;
    vector<int> v2 = {2,2,2};
    cout<<maxScore(v2,2)<<endl;
    vector<int> v3 = {9,7,7,9,7,7,9};
    cout<<maxScore(v3,7)<<endl;
    return 0;
}