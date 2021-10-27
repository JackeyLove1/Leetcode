#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100010;
int a[N], d1[N], d2[N], n;
int main() {
	while (cin >> a[++n]); n--;		//输入
	int len1 = 1, len2 = 1;		//初始长度为1
	d1[1] = a[1];		//用于求不上升序列长度
	d2[1] = a[1];		//用于求上升序列长度
	for (int i=2; i<=n; i++) {		//从a[2]开始枚举每个数(a[1]已经加进去了)
		if (d1[len1] >= a[i]) d1[++len1] = a[i];		//如果满足要求(不上升)就加入d1
		else {		//否则用a[i]替换d1中的一个数
			int p1 = upper_bound(d1 + 1, d1 + 1 + len1, a[i], greater<int>()) - d1;
			d1[p1] = a[i]; 
		}
		if (d2[len2] < a[i]) d2[++len2] = a[i];		//同上
		else {
			int p2 = lower_bound(d2 + 1, d2 + 1 + len2, a[i]) - d2;
			d2[p2] = a[i];
		}
	}
	cout << len1 << endl << len2;		//输出
	return 0;		//结束
}
        