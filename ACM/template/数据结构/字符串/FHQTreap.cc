#include <iostream>
using namespace std;

const int N=100005;
struct node{
  int l,r; //左右儿子
  int val; //树的权值 
  int rnd; //堆的随机值
  int size; //子树大小
}tr[N];
int root,idx;

void newnode(int &x,int v){
  x = ++idx;
  tr[x].val=v;
  tr[x].rnd=rand();
  tr[x].size=1;
}
void pushup(int p){ 
  tr[p].size=tr[tr[p].l].size+tr[tr[p].r].size+1;
}
void split(int p,int v,int &x,int &y){
  if(!p) {x=y=0; return;}
  if(tr[p].val<=v){
    x = p;
    split(tr[x].r,v,tr[x].r,y);
    pushup(x);
  }
  else{
    y = p;
    split(tr[y].l,v,x,tr[y].l);
    pushup(y);
  }
}
int merge(int x,int y){
  if(!x||!y) return x+y;
  if(tr[x].rnd<tr[y].rnd){
    tr[x].r=merge(tr[x].r,y);
    pushup(x); return x;
  }
  else{
    tr[y].l=merge(x,tr[y].l);
    pushup(y); return y;    
  }
}
void insert(int v){
  int x,y,z;
  split(root,v,x,y);
  newnode(z,v);
  root=merge(merge(x,z),y);
}
void del(int v){
  int x,y,z;
  split(root,v,x,z);
  split(x,v-1,x,y);
  y=merge(tr[y].l,tr[y].r);
  root=merge(merge(x,y),z);
}
int getrank(int v){
  int x,y;
  split(root,v-1,x,y);
  int ans=tr[x].size+1;
  root=merge(x,y);
  return ans;
}
int getval(int root,int v){
  if(v==tr[tr[root].l].size+1)
    return tr[root].val;
  else if(v<=tr[tr[root].l].size)
    return getval(tr[root].l,v);
  else 
    return getval(tr[root].r,v-tr[tr[root].l].size-1);
}
int getpre(int v){
  int x,y,s,ans;
  split(root,v-1,x,y);
  s=tr[x].size;
  ans=getval(x,s);
  root=merge(x,y);
  return ans;
}
int getnxt(int v){
  int x,y,ans;
  split(root,v,x,y);
  ans=getval(y,1);
  root=merge(x,y);
  return ans;
}
int main(){
  int n,op,v;
  scanf("%d",&n);
  for(int i=1;i<=n;++i){
    scanf("%d%d",&op,&v);
    if(op==1)insert(v);
    else if(op==2)del(v);
    else if(op==3)printf("%d\n",getrank(v));
    else if(op==4)printf("%d\n",getval(root,v));
    else if(op==5)printf("%d\n",getpre(v));
    else printf("%d\n",getnxt(v));
  }
  return 0;
}