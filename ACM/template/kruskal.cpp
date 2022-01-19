#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

const int N=200010,M=100010;         

int p[M];
int n,m;

struct Edge
{
    int a,b,w;

     bool operator< (const Edge &W)const
    {
        return w < W.w;
    }
}edges[N];

int find(int x)
{
    if(p[x]!=x) p[x]=find(p[x]);
    else return x;
} 

int Kruskal()
{
    int res=0,cnt=0;//res记录最小生成树的树边权重之和,cnt记录的是全部加入到树的集合中边的数量(可能有多个集合)
    for(int i=0;i<m;i++)
    {
        int a=edges[i].a,b=edges[i].b,w=edges[i].w;
        if(find(a)!=find(b))
        /*
        具体可以参考连通块中点的数量,如果a和b已经在一个集合当中了,说明这两个点已经被一种方式连接起来了,
        如果加入a-b这条边,会导致集合中有环的生成,而树中不允许有环生成,所以一个连通块中的点的数量假设
        为x,那么里面x个节点应该是被串联起来的,有x-1条边,所以只有当a,b所属的集合不同时,才能将a-b这条
        边加入到总集合当中去
        */
        {
            p[find(a)]=p[find(b)];//将a,b所在的两个集合连接起来
            cnt++;//因为加入的是a-b的这一条边,将a,b所在的两个集合连接之后,全部集合中的边数加1
            res+=w;//加入到集合中的边的权重之和
        }
    }

    if(cnt==n-1) return res;//可以生成最小生成树
    else return 0x3f3f3f3f;//树中有n个节点便有n-1条边,如果cnt不等于n-1的话,说明无法生成有n个节点的树
}

int main()
{
    cin>>n>>m;

    for(int i=0;i<n;i++) p[i]=i;//初始化并查集

    for(int i=0;i<m;i++)
    {
        int a,b,w;
        scanf("%d%d%d",&a,&b,&w);
        edges[i]={a,b,w};
    }

    sort(edges,edges+m);//将边的权重按照大小一一排序

    int t=Kruskal();

    if(t==0x3f3f3f3f) printf("impossible\n");
    else printf("%d\n",t);

    return 0;
}