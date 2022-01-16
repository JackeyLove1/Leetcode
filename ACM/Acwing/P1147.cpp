#include<bits/stdc++.h>
using namespace std;
int m;
int main(){
    cin>>m;
    for(int k1=sqrt(2*m);k1>1;k1--)//枚举k1(注意是k1>1而不是k1>=1)
        if(2*m%k1==0 && (k1+2*m/k1)%2){//如果K2是整数而且与K1一奇一偶
            int k2=2*m/k1;
            cout<<(k2-k1+1)/2<<" "<<(k1+k2-1)/2<<endl;//输出答案
        }
    return 0;
}
