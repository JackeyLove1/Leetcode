
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, w[19], f[20][1<<19], W;
int main(){
    memset(f, 0x3f, sizeof f);
    scanf("%d%d", &n, &W);
    for(int i=1; i<=n; i++)
        scanf("%d", &w[i]),
        f[1][1<<(i-1)]=w[i];//第1辆车只装第i只猫时
    f[1][0]=0;//第1辆车不装猫时
    for(int i=1; i<=n; i++){ //枚举车
        for(int j=0; j<(1<<n); j++){ //枚举状态 （j的第k位为0表示第k只猫不选，为1表示要选）
            if(f[i][j]!=0x3f3f3f3f)//如果这辆车被更新过 才能用来更新其他的
                for(int k=1; k<=n; k++){//枚举猫
                    if( W-f[i][j]>=w[k] && (j&(1<<(k-1)))==0 )//如果能装下 并且这只猫没有用过
                        f[i][j|(1<<(k-1))]=min(f[i][j|(1<<(k-1))],f[i][j]+w[k]);
                        //在 f[i][j]+w[k] 中找最小，赋值给 f[i][j|(1<<(k-1))]
                    else f[i+1][j|(1<<(k-1))]=min(f[i+1][j|(1<<(k-1))],w[k]);
                }
        }
        if( f[i][(1<<n)-1] !=0x3f3f3f3f ){ //所有猫都用过时 由于i从前往后循环 第一次被更新则为最小
            printf("%d\n",i);
            return 0;
        }
    }
    return 0;
}
