#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

char awa[105];
char waw[105];
char aaw[105];
int qwq[105][105][105];
string wqw[105][105][105];

inline int max (int a, int b) {
	return a > b ? a : b;
}

int main () {
	scanf ("%s %s %s", awa, waw, aaw);
	int n, m, k;
	n = strlen (awa);
	m = strlen (waw);
	k = strlen (aaw);
	for (register int i(1); i <= n; ++i)
		for (register int j(1); j <= m; ++j)
			for (register int l(1); l <= k; ++l) {
				if (awa[i - 1] == waw[j - 1] && awa[i - 1]== aaw[l - 1]) { //转移方程
					if (qwq[i][j][l] < qwq[i - 1][j - 1][l - 1] +1) {
						qwq[i][j][l] = qwq[i - 1][j - 1][l - 1] +1;
						wqw[i][j][l] = wqw[i - 1][j - 1][l - 1] + awa[i - 1];  //更新答案
					} 
				}
				else { //考虑继承
					if (qwq[i][j][l] < qwq[i - 1][j][l]) {
						qwq[i][j][l] = qwq[i - 1][j][l];
						wqw[i][j][l] = wqw[i - 1][j][l]; //更新答案
					}
					if (qwq[i][j][l] < qwq[i][j - 1][l]) {
						qwq[i][j][l] = qwq[i][j - 1][l];
						wqw[i][j][l] = wqw[i][j - 1][l];
					}
					if (qwq[i][j][l] < qwq[i][j][l - 1]) {
						qwq[i][j][l] = qwq[i][j][l - 1];
						wqw[i][j][l] = wqw[i][j][l - 1];
					}
				}
			}
	cout<<wqw[n][m][k];
	return 0;
}