#include <iostream>

using namespace std;

const int N = 100010, M = 1000010;

int n, m;
int ne[N];
char s[M], p[N];

int main()
{
    cin >> n >> p + 1 >> m >> s + 1;

    for (int i = 2, j = 0; i <= n; i ++ )
    {
        while (j && p[i] != p[j + 1]) j = ne[j];
        if (p[i] == p[j + 1]) j ++ ;
        ne[i] = j;
    }

    for (int i = 1, j = 0; i <= m; i ++ )
    {   // 在模式串p中找到与匹配串s中第i位匹配的第一位j
        // next数组存放的是字符串的前缀和后缀能匹配的字符个数的最大值
        while (j && s[i] != p[j + 1]) j = ne[j]; // 下一位不匹配，取下一位匹配项
        if (s[i] == p[j + 1]) j ++ ; // 匹配成功j移动到下一位
        if (j == n)
        {
            printf("%d ", i - n);
            j = ne[j];
        }
    }

    return 0;
}

/*
// prefix前缀匹配
// C++ Version
vector<int> prefix_function(string s) {
  int n = (int)s.length();
  vector<int> pi(n);
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) j++;
    pi[i] = j;
  }
  return pi;
}

*/