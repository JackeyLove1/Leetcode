#include<stdio.h>
#include<string.h>
#define N 1100
int c[N][N],n,arr[N][N];
int lowbit(int x)
{
    return x&(-x);
}
void update(int x,int y,int num)
{
    int i,j;
    for(i=x;i<=n;i+=lowbit(i))
        for(j=y;j<=n;j+=lowbit(j))
            c[i][j]+=num;
}
int sum(int x,int y)
{
    int i,j,s=0;
    for(i=x;i>0;i-=lowbit(i))
        for(j=y;j>0;j-=lowbit(j))
            s+=c[i][j];
    return s;
}
int getsum(int x1,int y1,int x2,int y2)
{
    return sum(x2,y2)-sum(x1-1,y2)-sum(x2,y1-1)+sum(x1-1,y1-1);
}
int main()
{
    int op,x,y,l,b,r,t,a;
    while(scanf("%d",&op)!=EOF)
    {
        if(op==0)
        {
            scanf("%d",&n);
            memset(c,0,sizeof(c));
        }
        else if(op==1)
        {
            scanf("%d%d%d",&x,&y,&a);
            update(x+1,y+1,a);
        }
        else if(op==2)
        {
            scanf("%d%d%d%d",&l,&b,&r,&t);
            int ans=getsum(l+1,b+1,r+1,t+1);
            printf("%d\n",ans);
        }
    }
    return 0;
}