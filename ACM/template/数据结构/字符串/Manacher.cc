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
