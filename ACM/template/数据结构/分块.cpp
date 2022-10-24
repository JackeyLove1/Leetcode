#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cmath>

// 一个简单的整数问题2
/*
给定一个长度为 N 的数列 A，以及 M 条指令，每条指令可能是以下两种之一：
C l r d，表示把 A[l],A[l+1],…,A[r] 都加上 d。
Q l r，表示询问数列中第 l∼r 个数的和。
对于每个询问，输出一个整数表示答案。
*/

using namespace std;

typedef long long LL;
const int N = 100010, M = 350;

int n, m, len;
LL add[M], sum[M];
int w[N];

int get(int i) // 获取在那个分块
{
    return i / len;
}

void change(int l, int r, int d)
{
    if (get(l) == get(r))  // 段内直接暴力
    {
        for (int i = l; i <= r; i ++ ) w[i] += d, sum[get(i)] += d;
    }
    else
    {
        int i = l, j = r;
        while (get(i) == get(l)) w[i] += d, sum[get(i)] += d, i ++ ;
        while (get(j) == get(r)) w[j] += d, sum[get(j)] += d, j -- ;
        for (int k = get(i); k <= get(j); k ++ ) sum[k] += len * d, add[k] += d;
    }
}

LL query(int l, int r)
{
    LL res = 0;
    if (get(l) == get(r))  // 段内直接暴力
    {
        for (int i = l; i <= r; i ++ ) res += w[i] + add[get(i)];
    }
    else
    {
        int i = l, j = r;
        while (get(i) == get(l)) res += w[i] + add[get(i)], i ++ ;
        while (get(j) == get(r)) res += w[j] + add[get(j)], j -- ;
        for (int k = get(i); k <= get(j); k ++ ) res += sum[k];
    }
    return res;
}

int main()
{
    scanf("%d%d", &n, &m);
    len = sqrt(n);
    for (int i = 1; i <= n; i ++ )
    {
        scanf("%d", &w[i]);
        sum[get(i)] += w[i];
    }

    char op[2];
    int l, r, d;
    while (m -- )
    {
        scanf("%s%d%d", op, &l, &r);
        if (*op == 'C')
        {
            scanf("%d", &d);
            change(l, r, d);
        }
        else printf("%lld\n", query(l, r));
    }

    return 0;
}

/*
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
#pragma GCC optimize(3)
using namespace std;
const int maxn=1000010;
const int _maxn=1010;
int n,q,block,cnt;
int belong[maxn],val[maxn],mark[_maxn];//数组在上文已提及，不多赘述 
vector<int> kuai[_maxn];
void start()//初始化kuai数组，让每个块内都有从小到大的顺序 （当然你也可以从大到小qwq） 
{
	for(int i=1;i<=cnt;++i)
		sort(kuai[i].begin(),kuai[i].end());
}
void update(int pos)//更新kuai数组
{
	kuai[pos].clear();//清空数组 
	for(int i=(pos-1)*block+1;i<=pos*block;++i)
		kuai[pos].push_back(val[i]);//因为块内元素已修改，所以重新放入元素 
	sort(kuai[pos].begin(),kuai[pos].end());//保证块内的有序性 
} 
void add(int l,int r,int x)//区间修改 
{
	for(int i=l;i<=min(r,belong[l]*block);++i)
		val[i]+=x;//左边零散的块暴力修改 
	update(belong[l]);//更新左边零散块的kuai数组 
	if(belong[l]!=belong[r])
	{
		for(int i=belong[l]+1;i<belong[r];++i)
			mark[i]+=x;//中间的块直接打标记 
		for(int i=(belong[r]-1)*block+1;i<=r;++i)
			val[i]+=x;//右边零散的块暴力修改		
		update(belong[r]);// 更新右边零散块的kuai数组 
	}
}
int search(int l,int r,int x)
{
	int num=0;//计数器 
	for(int i=l;i<=min(r,belong[l]*block);++i)
		if(val[i]+mark[belong[i]]>=x)//左边零散的块暴力查询，记住要加mark值 
			++num;
	if(belong[l]!=belong[r])
	{
		for(int i=belong[l]+1;i<belong[r];++i)
		{
			int L=0,R=block-1,mid;
			while(L<=R)//中间块二分查询，不然会T ，应该也可以用lower_bound这些类似的函数，别看我。。我不会。。 
			{
				mid=L+((R-L)>>1);
				if(kuai[i][mid]+mark[i]<x)
					L=mid+1;
				else
					R=mid-1;
			}
			num+=block-L;
		}
		for(int i=(belong[r]-1)*block+1;i<=r;++i)
			if(val[i]+mark[belong[i]]>=x)//右边零散的块暴力查询 
				++num;
	}
	return num;//返回值。。。 
}
int main()
{
	scanf("%d%d",&n,&q);
	block=sqrt(n);//块的大小 
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&val[i]);
		if(i%block==1)//到了新的一个块 
			cnt++;
		belong[i]=cnt;
		kuai[cnt].push_back(val[i]);
	}
	start();
	for(int i=1;i<=q;++i)
	{
		char in1;
		int in2,in3,in4;
		scanf(" %c%d%d%d",&in1,&in2,&in3,&in4);
		switch(in1)
		{
			case 'M':				
				add(in2,in3,in4);			
			break;
			case 'A':
				printf("%d\n",search(in2,in3,in4));
			break;
		}
	}
	return 0;
}
*/