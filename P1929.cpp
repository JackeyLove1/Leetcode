#include<cstdio>
#include<cstring>
#define Min(x,y) (x<y?x:y)
const int N=206;
int a[N],n,f[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    memset(f,0x3f,sizeof(f));
    int oo=f[0];
    f[1]=0;
    for(int i=2;i<=n;i++)
    {
        if(a[i]<=a[i-1]+1) f[i]=f[i-1]+1;
        for(int j=i-1;j>0;j--)
            for(int k=j-1;k>0;k--)
                if((1<<(j-k))+a[k]>=a[i]) f[i]=Min(f[i],f[j]+j-k+1);
    }
    printf("%d\n",f[n]>=oo?-1:f[n]);
}