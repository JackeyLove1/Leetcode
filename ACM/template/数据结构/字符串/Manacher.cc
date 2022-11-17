/*
// Luogu P3805 【模板】manacher 算法
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N=3e7;
char a[N],s[N];
int d[N]; //回文半径函数 

void get_d(char*s,int n){
  d[1]=1;
    for(int i=2,l,r=1;i<=n;i++){
        if(i<=r)d[i]=min(d[r-i+l],r-i+1);
        while(s[i-d[i]]==s[i+d[i]])d[i]++;
        if(i+d[i]-1>r)l=i-d[i]+1,r=i+d[i]-1;
        // printf("i=%d d=%d [%d %d]\n",i,d[i],l,r);
    }  
}
int main(){
  //改造串
  scanf("%s",a+1);
  int n=strlen(a+1),k=0;
  s[0]='$',s[++k]='#';        
  for(int i=1;i<=n;i++) 
    s[++k]=a[i],s[++k]='#';
  n=k;
  
  get_d(s,n);//计算d函数
  int ans=0;
  for(int i=1;i<=n;i++)
    ans=max(ans,d[i]);
  printf("%d\n",ans-1);
  return 0;
}
*/
// C++ Version
vector<int> d1(n);
for (int i = 0, l = 0, r = -1; i < n; i++) {
  int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
  while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
    k++;
  }
  d1[i] = k--;
  if (i + k > r) {
    l = i - k;
    r = i + k;
  }
}

// C++ Version
vector<int> d2(n);
for (int i = 0, l = 0, r = -1; i < n; i++) {
  int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
  while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
    k++;
  }
  d2[i] = k--;
  if (i + k > r) {
    l = i - k - 1;
    r = i + k;
  }
}

// example
#include<bits/stdc++.h>
using namespace std;
char str[2000020],s[2000020];
int p[2000020];
int len,id,mx;
void pre() //对字符串进行预处理
{
    len=strlen(s);
    str[0]='$';
    str[1]='#';
    for(int i=0;i<len;i++)
    {
        str[i*2+2]=s[i];
        str[i*2+3]='#';
    }
    len=len*2+2;
    str[len]=0;
}
void Manacher() //算法核心
{
    mx=0;
    for(int i=1;i<len;i++)
    {
        if(mx>i)
            p[i]=min(p[2*id-i],mx-i);
        else
            p[i]=1;
        while(str[i+p[i]]==str[i-p[i]])
            p[i]++;
        if(p[i]+i>mx)
        {
            mx=p[i]+i;
            id=i;
        }
    }
}
int main()
{
    int N;
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
    {
        scanf("%s",s);
        pre();
        Manacher();
        printf("%d\n",p[max_element(p,p+len)-p]-1);
    }
    return 0;
}
