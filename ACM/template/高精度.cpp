// 推荐第二种方案bign
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int MAXN = 85, Mod = 10000; //高精四位压缩大法好 
int n, m;
int ar[MAXN];

struct HP {
	int p[505], len;
	HP() {
		memset(p, 0, sizeof p);
		len = 0;
	} //这是构造函数，用于直接创建一个高精度变量 
	void print() {
		printf("%d", p[len]);  
        for (int i = len - 1; i > 0; i--) {  
            if (p[i] == 0) {
				printf("0000"); 
				continue;
			}
            for (int k = 10; k * p[i] < Mod; k *= 10) 
				printf("0");
            printf("%d", p[i]);
        }
	} //四位压缩的输出 
} f[MAXN][MAXN], base[MAXN], ans;

HP operator + (const HP &a, const HP &b) {
	HP c; c.len = max(a.len, b.len); int x = 0;
	for (int i = 1; i <= c.len; i++) {
		c.p[i] = a.p[i] + b.p[i] + x;
		x = c.p[i] / Mod;
		c.p[i] %= Mod;
	}
	if (x > 0)
		c.p[++c.len] = x;
	return c;
} //高精+高精 

HP operator * (const HP &a, const int &b) {
	HP c; c.len = a.len; int x = 0;
	for (int i = 1; i <= c.len; i++) {
		c.p[i] = a.p[i] * b + x;
		x = c.p[i] / Mod;
		c.p[i] %= Mod;
	}
	while (x > 0)
		c.p[++c.len] = x % Mod, x /= Mod;
	return c;
} //高精*单精 

HP max(const HP &a, const HP &b) {
	if (a.len > b.len)
		return a;
	else if (a.len < b.len)
		return b;
	for (int i = a.len; i > 0; i--)
		if (a.p[i] > b.p[i])
			return a;
		else if (a.p[i] < b.p[i])
			return b;
	return a;
} //比较取最大值 

void BaseTwo() {
	base[0].p[1] = 1, base[0].len = 1;
	for (int i = 1; i <= m + 2; i++){ //这里是m! m! m! 我TM写成n调了n年... 
		base[i] = base[i - 1] * 2;
	}
} //预处理出2的幂 

int main(void) {
	scanf("%d%d", &n, &m);
	BaseTwo();
	while (n--) {
		memset(f, 0, sizeof f);
		for (int i = 1; i <= m; i++)
			scanf("%d", &ar[i]);
		for (int i = 1; i <= m; i++)
			for (int j = m; j >= i; j--) { //因为终值是小区间，DP自然就从大区间开始 
				f[i][j] = max(f[i][j], f[i - 1][j] + base[m - j + i - 1] * ar[i - 1]); 
				f[i][j] = max(f[i][j], f[i][j + 1] + base[m - j + i - 1] * ar[j + 1]);
			} //用结构体重载运算符写起来比较自然 
		HP Max;
		for (int i = 1; i <= m; i++)
			Max = max(Max, f[i][i] + base[m] * ar[i]);
		ans = ans + Max; //记录到总答案中 
	}
	ans.print(); //输出 
	return 0;
}


#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
using namespace std;
const int N = 1005;
struct bign
{
    int len,s[N];
    bign()  {  memset(s,0,sizeof(s));  len=1;  }
    bign(int num)  {  *this=num; }
    bign(char *num) { *this=num; }
    bign operator =(int num)
    {
        char c[N];
        sprintf(c,"%d",num);
        *this=c;
        return *this;
    }
    bign operator =(const char *num)
    {
        len=strlen(num);
        for (int i=0;i<len;i++) s[i]=num[len-1-i]-'0';
        return *this;
    }
    string str()
    {
        string res="";
        for (int i=0;i<len;i++) res=(char)(s[i]+'0')+res;
        return res;
    }
    void clean()
    {
        while (len>1&&!s[len-1]) len--;
    }
    bign operator +(const bign &b)
    {
        bign c;    
        c.len=0;
        for (int i=0,g=0;g||i<len||i<b.len;i++)
        {
            int x=g;
            if (i<len) x+=s[i];
            if (i<b.len) x+=b.s[i];
            c.s[c.len++]=x%10;
            g=x/10;
        }
        return c;
    }
    bign operator -(const bign &b)
    {
        bign c;
        c.len=0;
        int x;     
        for (int i=0,g=0;i<len;i++)
        {
            x=s[i]-g;
            if (i<b.len) x-=b.s[i];
            if (x>=0) g=0;
            else{          
                x+=10;
                g=1;
            };
            c.s[c.len++]=x;
        }
        c.clean();
        return c;
    }
    bign operator *(const bign &b)
    {
        bign c;
        c.len=len+b.len;
        for (int i=0;i<len;i++) for (int j=0;j<b.len;j++) c.s[i+j]+=s[i]*b.s[j];
        for (int i=0;i<c.len-1;i++) { c.s[i+1]+=c.s[i]/10; c.s[i]%=10; }
        c.clean();
        return c;  
    }
    bool operator <(const bign &b)
    {
        if (len!=b.len) return len<b.len;
        for (int i=len-1;i>=0;i--)
             if (s[i]!=b.s[i]) return s[i]<b.s[i];
        return false;
    }
    bign operator +=(const bign &b)
    {
        *this=*this+b;
        return *this;
    }
    bign operator -=(const bign &b)
    {
        *this=*this-b;
        return *this;
    }  
};
istream& operator >>(istream &in,bign &x)
{
  string s;
  in>>s;
  x=s.c_str();
  return in;
}
ostream& operator <<(ostream &out,bign &x)
{
    out<<x.str();
    return out;
}
int main(){
    bign a,b,c;
    ios::sync_with_stdio(false);
    cin>>a>>b;
//    cout<<a<<endl;
//    cout<<b<<endl;
    c=a+b;
    cout<<c<<endl;
    return 0;
}
