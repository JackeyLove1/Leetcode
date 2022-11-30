#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;
#define mset(name,val) memset(name,val,sizeof name)
#define filein(str) freopen(str".in","r",stdin)
#define fileout(str) freopen(str".out","w",stdout) 
const int P=20020,SIZE=1000080;
int p,Head[P],cnt;
struct node
{
    int next,val,s;
};
struct state
{
    int a,b,f,s;
    inline void fcost(void)
    {
        this->f = 0;
        int Max = max( this->a , this->b );
        while ( Max<p ) Max<<=1 , (this->f)++ ;
    }
    bool operator < (const state t)const
    {
        return this->s+this->f == t.s+t.f ? this->f < t.f : this->s+this->f < t.s+t.f ;
    }
    bool operator > (const state t)const
    {
        return this->s+this->f == t.s+t.f ? this->f > t.f : this->s+this->f > t.s+t.f ;
    }
};
priority_queue < state,vector<state>,greater<state> > Heap;
state Begin;
node List[SIZE];
inline void input(void)
{
    scanf("%d",&p);
    Begin=(state){1,0,0,0};
}
inline int Hash(int x,int y)
{
    return (int)(((long long)x*2023%SIZE+(long long)y*1926%SIZE)%SIZE);
}
inline bool retrieval(int val,int s)
{
    int index=val%P;
    for (int i=Head[index];i;i=List[i].next)
    {
        if (List[i].val==val)
        {
            if (List[i].s<=s)return true;
            List[i].s=s;return false;
        }
    }
    List[++cnt]=(node){Head[index],val,s};
    Head[index]=cnt;
    return false;
}
inline int gcd(int a,int b)
{
    return b==0 ? a : gcd( b , a%b );
}
inline bool check(int x,int y)
{
    return x==y || ( x>p && y==0 ) || p % gcd(x,y) || x>2*p ;
}
inline void transfer(int x,int y,int t)
{
    if (x<y) swap(x,y);
    if (check(x,y))return;
    if (retrieval(Hash(x,y),t+1))return;
    state next=(state){x,y,0,t+1};
    next.fcost();
    Heap.push(next);
}
inline int Astar(void)
{
    Heap.push(Begin);
    while (!Heap.empty())
    {
        state t=Heap.top();
        Heap.pop();
        if (t.a==p||t.b==p)return t.s;
        int temp[2]={t.a,t.b};
        for (int i=0;i<2;i++)
        {
            for (int j=i;j<2;j++)
            {
                for (int k=0;k<2;k++)
                {
                    if (!k)
                        transfer(temp[i]+temp[j],temp[1],t.s);
                    if (k)
                        transfer(temp[0],temp[i]+temp[j],t.s);
                }
            }
        }
        transfer(temp[0],temp[0]-temp[1],t.s);
        transfer(temp[0]-temp[1],temp[1],t.s);
    }
}
int main(void)
{
    filein("power");
    fileout("power");
    input();
    printf("%d\n",Astar());
    return 0;
}