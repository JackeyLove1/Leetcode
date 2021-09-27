#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;
const int N = 200000 + 1, INF = 1e9;
int t,n;
struct node{
    int s,e,d;
}a[N];
int getSum(int x){ // O(n) 求[minn,x]的前缀和 
    int res = 0;
    for(int i = 1; i <= n; i++)
        if(a[i].s <= x)
            res += (min(a[i].e, x) - a[i].s)/a[i].d + 1;

    return res;
}
bool check(int l,int r){ // O(n) 查找[l,r]是否存在奇数位 
    return (getSum(r) - getSum(l - 1)) & 1;
}
int main(){
    cin >> t;
    while(t--){
        cin >> n;
        int maxn = -INF, minn = INF;
        for(int i = 1; i <= n; i++){
            cin >> a[i].s >> a[i].e >> a[i].d;
            minn = min(minn,a[i].s); 
            maxn = max(maxn,a[i].e);
        }

        if(!(getSum(maxn) & 1)){
            cout << "There's no weakness." << endl;
        }else{
            int l = minn, r = maxn;
            while(l <= r){
                int mid = (l + r) >> 1;
                if(check(l,mid))r = mid - 1;
                else l = mid + 1;
            }

            cout << l << " " << (getSum(l) - getSum(l - 1)) << endl;
        }
    }
    return 0;
}
