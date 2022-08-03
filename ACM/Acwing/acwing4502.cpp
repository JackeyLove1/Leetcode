#include<iostream>
using namespace std;
const int N=5e5+5;
int q,x,a[N],k,n;
double s;
int main(){
    scanf("%d",&q);
    while(q--){
        scanf("%d",&x);
        if(x==1)scanf("%d",&a[++n]);
        else{
            while(k+1<=n&&a[k+1]<(s+a[n])/(k+1))s+=a[++k];
            //尝试加入一个新的元素
            printf("%0.6f\n",a[n]-(a[n]+s)/(k+1));
        }
    }
    return 0;
}
