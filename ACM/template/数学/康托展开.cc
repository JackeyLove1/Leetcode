static constexpr int FAC[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};	// 阶乘
int cantor(int *a, int n)
{
	int x = 0;
	for (int i = 0; i < n; ++i) {
		int smaller = 0;  // 在当前位之后小于其的个数
		for (int j = i + 1; j < n; ++j) {
			if (a[j] < a[i])
				smaller++;
		}
		x += FAC[n - i - 1] * smaller; // 康托展开累加
	}
	return x;  // 康托展开值
}

/*
这里主要为了讲解康托展开的思路，实现的算法复杂度为O(n^2)，
实际当n很大时，内层循环计算在当前位之后小于当前位的个数可以用线段树来处理计算，
而不用每次都遍历，这样复杂度可以降为O(nlogn)
*/

/*例如
#include<cstdio>  
const int fac[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};///阶乘  
int KT(int s[], int n)  
{  
    int i, j, cnt, sum;  
    sum = 0;  
    for (i = 0; i < n; ++i)  
    {  
        cnt = 0;  
        for (j = i + 1; j < n; ++j)  
            if (s[j] < s[i]) ++cnt;  
        sum += cnt * fac[n - i - 1];  
    }  
    return sum;  
}  
int main()  
{  
    int a[] = {3, 5, 7, 4, 1, 2, 9, 6, 8};  
    printf("%d\n", 1 + KT(a, sizeof(a) / sizeof(*a))); ///1+98884=98885 
}  
*/

// 逆康托展开

//康托展开逆运算
void decantor(int x, int n)
{
    vector<int> rest;  // 存放当前可选数，保证有序
    for(int i=1;i<=n;i++)
        v.push_back(i);
        
    vector<int> ans;  // 所求排列组合
    for(int i=n;i>=1;i--)
    {
        int r = x % FAC[i-1];
        int t = x / FAC[i-1];
        x = r;
        a.push_back(v[t]);      // 剩余数里第t+1个数为当前位
        v.erase(v.begin()+t);   // 移除选做当前位的数
    }
}

