#include<iostream>
using namespace std;
#define int long long
const int N=1e5+10,mod=51061;
struct splay{
	int add,mul,rev;
	int fa,son[2];
	int val,sum;
	int size;
};
splay spl[N];
inline bool check_root(int pos){
	return spl[spl[pos].fa].son[0]!=pos&&spl[spl[pos].fa].son[1]!=pos;
}
inline void connect(int pos,int fa,int son){
	spl[fa].son[son]=pos;
	spl[pos].fa=fa;
}
inline int relation(int pos,int fa){
	return spl[fa].son[1]==pos;
}
inline void pushup(int pos){
	int lson=spl[pos].son[0],rson=spl[pos].son[1];
	spl[pos].size=spl[lson].size+spl[rson].size+1;
	spl[pos].sum=(spl[lson].sum+spl[rson].sum+spl[pos].val)%mod;
}
inline void pushdown(int pos){
	if(spl[pos].rev){
		swap(spl[pos].son[0],spl[pos].son[1]);
		spl[spl[pos].son[0]].rev^=1;
		spl[spl[pos].son[1]].rev^=1;
		spl[pos].rev=0;
	}
	int lson=spl[pos].son[0],rson=spl[pos].son[1];
	int lsize=spl[lson].size,rsize=spl[rson].size;
	spl[lson].sum=(spl[lson].sum*spl[pos].mul%mod+spl[pos].add*lsize%mod)%mod;
	spl[rson].sum=(spl[rson].sum*spl[pos].mul%mod+spl[pos].add*rsize%mod)%mod;
	spl[lson].val=(spl[lson].val*spl[pos].mul%mod+spl[pos].add%mod)%mod;
	spl[rson].val=(spl[rson].val*spl[pos].mul%mod+spl[pos].add%mod)%mod;
	spl[lson].add=(spl[lson].add*spl[pos].mul%mod+spl[pos].add%mod)%mod;
	spl[rson].add=(spl[rson].add*spl[pos].mul%mod+spl[pos].add%mod)%mod;
	spl[lson].mul=spl[lson].mul*spl[pos].mul%mod;
	spl[rson].mul=spl[rson].mul*spl[pos].mul%mod;
	spl[pos].mul=1;
	spl[pos].add=0;
}//可以参考线段树2
inline void pushall(int pos){
	if(!check_root(pos))
		pushall(spl[pos].fa);
	pushdown(pos);
}
void rotate(int pos){
	int fa=spl[pos].fa,gf=spl[fa].fa;
	int t1=relation(pos,fa),t2=relation(fa,gf);
	connect(spl[pos].son[t1^1],fa,t1);
	connect(fa,pos,t1^1);
	if(spl[gf].son[t2]==fa)
		connect(pos,gf,t2);
	else
		spl[pos].fa=gf;
	pushup(fa);
	pushup(pos);
}
void splaying(int pos){
	pushall(pos);
	while(!check_root(pos)){
		int fa=spl[pos].fa,gf=spl[fa].fa;
		if(!check_root(fa))
			relation(pos,fa)^relation(fa,gf)?rotate(pos):rotate(fa);
		rotate(pos);
	}
}
void access(int pos){
	int son=0;
	while(pos){
		splaying(pos);
		spl[pos].son[1]=son;
		pushup(pos);
		son=pos;
		pos=spl[pos].fa;
	}
}
void make_root(int pos){
	access(pos);
	splaying(pos);
	spl[pos].rev^=1;
}
int find_root(int pos){
	access(pos);
	splaying(pos);
	while(spl[pos].son[0]){
		pos=spl[pos].son[0];
		pushdown(pos);
	}
	splaying(pos);
	return pos;
}
void link(int x,int y){
	make_root(x);
	access(y);
	splaying(y);
	spl[x].fa=y;
}
void cut(int x,int y){
	make_root(x);
	access(y);
	splaying(y);
	spl[y].son[0]=0;
	spl[x].fa=0;
}
void split(int x,int y){
	make_root(x);
	access(y);
	splaying(y);
}
signed main(){
	int n,m;
	cin>>n>>m;
	int x,y;
	for(int i=1;i<=n;i++)
		spl[i].mul=spl[i].val=spl[i].sum=1;
	for(int i=1;i<=n-1;i++){
		cin>>x>>y;
		link(x,y);
	}
	char opt;
	int u,v,val;
	for(int i=1;i<=m;i++){
		cin>>opt;
		switch(opt){
			case '+':
				cin>>x>>y>>val;
				split(x,y);
				spl[y].add=(spl[y].add%mod+val%mod)%mod;
				spl[y].val=(spl[y].val%mod+val%mod)%mod;
				spl[y].sum=(spl[y].sum%mod+val*spl[y].size%mod)%mod;
				break;
			case '-':
				cin>>x>>y>>u>>v;
				cut(x,y);
				link(u,v);
				break;
			case '*':
				cin>>x>>y>>val;
				split(x,y);
				spl[y].val=spl[y].val*val%mod;
				spl[y].mul=spl[y].mul*val%mod;
				spl[y].add=spl[y].add*val%mod;
				spl[y].sum=spl[y].sum*val%mod;
				//同样可以参考线段树2
				break;
			case '/':
				cin>>x>>y;
				split(x,y);
				cout<<spl[y].sum<<'\n';
				break;
		}
	}
}