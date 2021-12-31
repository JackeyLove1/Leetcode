#include<bits/stdc++.h>
using namespace std;
int p,n,m,x;
int main()
{
    scanf("%d",&p);
    while(p--)
    {
        scanf("%d%d",&n,&m);
        priority_queue<int> l;
        priority_queue<int,vector<int>,greater<int> > r;
        int ans[m],co=0;
        for(int i=1;i<=m;i++)   //当i为奇数时输入的总个数也为奇数
        {
            scanf("%d",&x);
            if(r.empty() || r.top()<x)  r.push(x);
            else l.push(x);
            if(i%2)
            {
                while(r.size()<(i+1)/2)
                {
                    r.push(l.top());
                    l.pop();
                }
                while(r.size()>(i+1)/2)
                {
                    l.push(r.top());
                    r.pop();
                }
                ans[co++]=r.top();
            }
        }
        cout<<n<<" "<<co<<endl;
        for(int i=0;i<co;i++)
        {
            if(i && i%10==0) cout<<endl;
            cout<<ans[i]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
