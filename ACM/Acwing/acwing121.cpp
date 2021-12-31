#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int,int> PII;
int n,c;
PII points[1010];
vector<int> numbers;
int sum[1010][1010];
int get(int x){
    return lower_bound(numbers.begin(),numbers.end(),x) - numbers.begin();
}
bool check(int len){
    for (int x1 = 0,x2 = 1; x2 < numbers.size(); x2++){
        while(numbers[x2] - numbers[x1 + 1] + 1 > len)x1++;
        for (int y1 = 0, y2 = 1; y2 < numbers.size(); y2++){
            while(numbers[y2] - numbers[y1 + 1] + 1 > len)y1++;
            if (sum[x2][y2] - sum[x1][y2] - sum[x2][y1] + sum[x1][y1] >= c) return true;
        }
    }
    return false;
}
int main(){
    cin >> c >> n;
    numbers.push_back(0);
    for (int i = 0; i < n; i++){
        int x,y;
        cin >> x >> y;
        points[i] = {x,y};
        numbers.push_back(x);
        numbers.push_back(y);
    }
    sort(numbers.begin(),numbers.end());
    numbers.erase(unique(numbers.begin(),numbers.end()),numbers.end());
    for (int i = 0; i < n; i++){
       int x = get(points[i].first),y = get(points[i].second);
       sum[x][y]++;
    }
    for (int i = 1; i < numbers.size(); i++){
        for (int j = 1; j < numbers.size(); j++){
            sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }
    int l = 1,r = 10000;
    while (l < r){
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l;
    return 0;
}

