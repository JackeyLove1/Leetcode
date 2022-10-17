#include<iostream>
#include<cstring>
#include<map>

using namespace std;

const int N=210;

int res[N][N],g[N][N];
int k,n,m,S,E;
map<int,int> id;

void mul(int c[][N],int a[][N],int b[][N])
{
    static int temp[N][N];
    memset(temp,0x3f,sizeof temp);
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                temp[i][j]=min(temp[i][j],a[i][k]+b[k][j]);
    memcpy(c,temp,sizeof temp);
}

void qmi()
{
    memset(res,0x3f,sizeof res);
    for(int i=1;i<=n;i++) res[i][i]=0;//经过0条边
    while(k)//更新的过程
    {
        if(k&1) mul(res,res,g);//res=res*g;根据k决定是否用当前g的结果去更新res
        mul(g,g,g);//g=g*g;g的更新
        k>>=1;
    }
}

int main()
{
    cin>>k>>m>>S>>E;//虽然点数较多，但由于边数少，所以我们实际用到的点数也很少，可以使用map来离散化来赋予
    //他们唯一的编号
    memset(g,0x3f,sizeof g);
    //这里我们来解释一下为什么不去初始化g[i][i]=0呢？
    //我们都知道在类Floyd算法中有严格的边数限制，如果出现了i->j->i的情况其实在i->i中我们是有2条边的
    //要是我们初始化g[i][i]=0,那样就没边了，影响了类Floyd算法的边数限制！
    if(!id.count(S)) id[S]=++n;
    if(!id.count(E)) id[E]=++n;
    S=id[S],E=id[E];
    while(m--)
    {
        int a,b,c;
        scanf("%d%d%d",&c,&a,&b);
        if(!id.count(a)) id[a]=++n;
        if(!id.count(b)) id[b]=++n;
        a=id[a],b=id[b];
        g[a][b]=g[b][a]=min(g[a][b],c);
    }
    qmi();
    cout<< res[S][E] <<endl;
    return 0;
}