#include <cstdio>
#include <cstdlib>
#include <iostream>

#define ll long long
using namespace std;
ll a[100000 + 5],ans[100000 + 5];
int n,m;
int main()
{
//	printf("%d\n",2^3);
	cin>>n;
	for(int i = 1; i<=n; i++) {
		scanf("%lld",&a[i]);
		ans[i] = ans[i-1] ^ a[i];
	}
//	for(int i = 1; i<=n; i++) {
//		printf("%d ",ans[i]);
//	}
//	printf("\n");
	cin>>m;
	int l,r;
	while(m--) {
		scanf("%d%d",&l,&r);
		printf("%lld\n",ans[r] ^ ans[l - 1]);
	}
	return 0;
 } 
