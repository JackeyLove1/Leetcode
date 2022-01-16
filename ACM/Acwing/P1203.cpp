#include <iostream>
#include <algorithm>
using namespace std;
string a;
int f(int x)
{
    int s=0;
    char a1=a[x];
    char b2=a[x+1];
    for(int i=x;;i--)//往前看和往后看
    {
        if(a[i]==a1)s++;
        else if(a[i]=='w')
            s++;
        else
            break;
    }
    for(int i=x+1;;i++)
    {
        if(a[i]==b2)s++;
        else if(a[i]=='w')
            s++;
        else
            break;
    }
    return s;
}
int main()
{
    int ans,n;
    ans=-1;
    cin>>n;cin>>a;
    a=a+a+a;
    for(int i=n;i<2*n;i++)//三段 从中间那一段开始处理
    {
        if(a[i]==a[i+1])
            continue;
        if(a[i]=='w')//这TMD硬是看的到第三个点 要不然真不会
        {
            a[i]='r';
            ans=max(ans,f(i));
            a[i]='b';
            ans=max(ans,f(i));
            a[i]='w';
        }
        ans=max(ans,f(i));
    }
    ans=min(ans,n);//最长也不能比总长长
    if(ans==-1)ans=n;//出现这种情况必定是一路continue过来的
    cout<<ans<<endl;
    return 0;
}