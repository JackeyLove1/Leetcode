// Author: Jacky
// Time: 2021-09-29
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>

using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

const int debug = 0;

string add(string a, string b)//只限两个非负整数相加
{
    const int L = 1e5;
    string ans;
    int na[L] = {0}, nb[L] = {0};
    int la = a.size(), lb = b.size();
    for (int i = 0; i < la; i++) na[la - 1 - i] = a[i] - '0';
    for (int i = 0; i < lb; i++) nb[lb - 1 - i] = b[i] - '0';
    int lmax = la > lb ? la : lb;
    for (int i = 0; i < lmax; i++) na[i] += nb[i], na[i + 1] += na[i] / 10, na[i] %= 10;
    if (na[lmax]) lmax++;
    for (int i = lmax - 1; i >= 0; i--) ans += na[i] + '0';
    return ans;
}

string sub(string a, string b)//只限大的非负整数减小的非负整数
{
    const int L = 1e5;
    string ans;
    int na[L] = {0}, nb[L] = {0};
    int la = a.size(), lb = b.size();
    for (int i = 0; i < la; i++) na[la - 1 - i] = a[i] - '0';
    for (int i = 0; i < lb; i++) nb[lb - 1 - i] = b[i] - '0';
    int lmax = la > lb ? la : lb;
    for (int i = 0; i < lmax; i++) {
        na[i] -= nb[i];
        if (na[i] < 0) na[i] += 10, na[i + 1]--;
    }
    while (!na[--lmax] && lmax > 0);
    lmax++;
    for (int i = lmax - 1; i >= 0; i--) ans += na[i] + '0';
    return ans;
}

string mul(string a, string b)//高精度乘法a,b,均为非负整数
{
    const int L = 1e5;
    string s;
    int na[L], nb[L], nc[L], La = a.size(), Lb = b.size();//na存储被乘数，nb存储乘数，nc存储积
    fill(na, na + L, 0);
    fill(nb, nb + L, 0);
    fill(nc, nc + L, 0);//将na,nb,nc都置为0
    for (int i = La - 1; i >= 0; i--) na[La - i] = a[i] - '0';//将字符串表示的大整形数转成i整形数组表示的大整形数
    for (int i = Lb - 1; i >= 0; i--) nb[Lb - i] = b[i] - '0';
    for (int i = 1; i <= La; i++)
        for (int j = 1; j <= Lb; j++)
            nc[i + j - 1] += na[i] * nb[j];//a的第i位乘以b的第j位为积的第i+j-1位（先不考虑进位）
    for (int i = 1; i <= La + Lb; i++)
        nc[i + 1] += nc[i] / 10, nc[i] %= 10;//统一处理进位
    if (nc[La + Lb]) s += nc[La + Lb] + '0';//判断第i+j位上的数字是不是0
    for (int i = La + Lb - 1; i >= 1; i--)
        s += nc[i] + '0';//将整形数组转成字符串
    return s;
}

string mul(string a, string b)//高精度乘法a,b,均为非负整数
{
    const int L = 1e5;
    string s;
    int na[L], nb[L], nc[L], La = a.size(), Lb = b.size();//na存储被乘数，nb存储乘数，nc存储积
    fill(na, na + L, 0);
    fill(nb, nb + L, 0);
    fill(nc, nc + L, 0);//将na,nb,nc都置为0
    for (int i = La - 1; i >= 0; i--) na[La - i] = a[i] - '0';//将字符串表示的大整形数转成i整形数组表示的大整形数
    for (int i = Lb - 1; i >= 0; i--) nb[Lb - i] = b[i] - '0';
    for (int i = 1; i <= La; i++)
        for (int j = 1; j <= Lb; j++)
            nc[i + j - 1] += na[i] * nb[j];//a的第i位乘以b的第j位为积的第i+j-1位（先不考虑进位）
    for (int i = 1; i <= La + Lb; i++)
        nc[i + 1] += nc[i] / 10, nc[i] %= 10;//统一处理进位
    if (nc[La + Lb]) s += nc[La + Lb] + '0';//判断第i+j位上的数字是不是0
    for (int i = La + Lb - 1; i >= 1; i--)
        s += nc[i] + '0';//将整形数组转成字符串
    return s;
}

int sub(int *a, int *b, int La, int Lb) {
    if (La < Lb) return -1;//如果a小于b，则返回-1
    if (La == Lb) {
        for (int i = La - 1; i >= 0; i--)
            if (a[i] > b[i]) break;
            else if (a[i] < b[i]) return -1;//如果a小于b，则返回-1

    }
    for (int i = 0; i < La; i++)//高精度减法
    {
        a[i] -= b[i];
        if (a[i] < 0) a[i] += 10, a[i + 1]--;
    }
    for (int i = La - 1; i >= 0; i--)
        if (a[i]) return i + 1;//返回差的位数
    return 0;//返回差的位数

}

// 高精度除以高精度
string div(string n1, string n2, int nn)
//n1,n2是字符串表示的被除数，除数,nn是选择返回商还是余数
{
    const int L = 1e5;
    string s, v;//s存商,v存余数
    int a[L], b[L], r[L], La = n1.size(), Lb = n2.size(), i, tp = La;
    //a，b是整形数组表示被除数，除数，tp保存被除数的长度
    fill(a, a + L, 0);
    fill(b, b + L, 0);
    fill(r, r + L, 0);//数组元素都置为0
    for (i = La - 1; i >= 0; i--) a[La - 1 - i] = n1[i] - '0';
    for (i = Lb - 1; i >= 0; i--) b[Lb - 1 - i] = n2[i] - '0';
    if (La < Lb || (La == Lb && n1 < n2)) {
        //cout<<0<<endl;
        return n1;
    }//如果a<b,则商为0，余数为被除数
    int t = La - Lb;//除被数和除数的位数之差
    for (int i = La - 1; i >= 0; i--)//将除数扩大10^t倍
        if (i >= t) b[i] = b[i - t];
        else b[i] = 0;
    Lb = La;
    for (int j = 0; j <= t; j++) {
        int temp;
        while ((temp = sub(a, b + j, La, Lb - j)) >= 0)//如果被除数比除数大继续减
        {
            La = temp;
            r[t - j]++;
        }
    }
    for (i = 0; i < L - 10; i++) r[i + 1] += r[i] / 10, r[i] %= 10;//统一处理进位
    while (!r[i]) i--;//将整形数组表示的商转化成字符串表示的
    while (i >= 0) s += r[i--] + '0';
    //cout<<s<<endl;
    i = tp;
    while (!a[i]) i--;//将整形数组表示的余数转化成字符串表示的</span>
    while (i >= 0) v += a[i--] + '0';
    if (v.empty()) v = "0";
    //cout<<v<<endl;
    if (nn == 1) return s;//返回商
    if (nn == 2) return v;//返回余数
}

// 高精度除以单精度
string div(string a, int b)//高精度a除以单精度b
{
    string r, ans;
    int d = 0;
    if (a == "0") return a;//特判
    for (int i = 0; i < a.size(); i++) {
        r += (d * 10 + a[i] - '0') / b + '0';//求出商
        d = (d * 10 + (a[i] - '0')) % b;//求出余数
    }
    int p = 0;
    for (int i = 0; i < r.size(); i++)
        if (r[i] != '0') {
            p = i;
            break;
        }
    return r.substr(p);
}

// 高精度取模
int mod(string a, int b)//高精度a除以单精度b
{
    int d = 0;
    for (int i = 0; i < a.size(); i++) d = (d * 10 + (a[i] - '0')) % b;//求出余数
    return d;
}

// 高精度阶乘
string fac(int n) {
    const int L = 100005;
    int a[L];
    string ans;
    if (n == 0) return "1";
    fill(a, a + L, 0);
    int s = 0, m = n;
    while (m) a[++s] = m % 10, m /= 10;
    for (int i = n - 1; i >= 2; i--) {
        int w = 0;
        for (int j = 1; j <= s; j++) a[j] = a[j] * i + w, w = a[j] / 10, a[j] = a[j] % 10;
        while (w) a[++s] = w % 10, w /= 10;
    }
    while (!a[s]) s--;
    while (s >= 1) ans += a[s--] + '0';
    return ans;
}

// 高精度幂
#define L(x) (1 << (x))
const double PI = acos(-1.0);
const int Maxn = 133015;
double ax[Maxn], ay[Maxn], bx[Maxn], by[Maxn];
char sa[Maxn / 2], sb[Maxn / 2];
int sum[Maxn];
int x1[Maxn], x2[Maxn];

int revv(int x, int bits) {
    int ret = 0;
    for (int i = 0; i < bits; i++) {
        ret <<= 1;
        ret |= x & 1;
        x >>= 1;
    }
    return ret;
}

void fft(double *a, double *b, int n, bool rev) {
    int bits = 0;
    while (1 << bits < n) ++bits;
    for (int i = 0; i < n; i++) {
        int j = revv(i, bits);
        if (i < j)
            swap(a[i], a[j]), swap(b[i], b[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int half = len >> 1;
        double wmx = cos(2 * PI / len), wmy = sin(2 * PI / len);
        if (rev) wmy = -wmy;
        for (int i = 0; i < n; i += len) {
            double wx = 1, wy = 0;
            for (int j = 0; j < half; j++) {
                double cx = a[i + j], cy = b[i + j];
                double dx = a[i + j + half], dy = b[i + j + half];
                double ex = dx * wx - dy * wy, ey = dx * wy + dy * wx;
                a[i + j] = cx + ex, b[i + j] = cy + ey;
                a[i + j + half] = cx - ex, b[i + j + half] = cy - ey;
                double wnx = wx * wmx - wy * wmy, wny = wx * wmy + wy * wmx;
                wx = wnx, wy = wny;
            }
        }
    }
    if (rev) {
        for (int i = 0; i < n; i++)
            a[i] /= n, b[i] /= n;
    }
}

int solve(int a[], int na, int b[], int nb, int ans[]) {
    int len = max(na, nb), ln;
    for (ln = 0; L(ln) < len; ++ln);
    len = L(++ln);
    for (int i = 0; i < len; ++i) {
        if (i >= na) ax[i] = 0, ay[i] = 0;
        else ax[i] = a[i], ay[i] = 0;
    }
    fft(ax, ay, len, 0);
    for (int i = 0; i < len; ++i) {
        if (i >= nb) bx[i] = 0, by[i] = 0;
        else bx[i] = b[i], by[i] = 0;
    }
    fft(bx, by, len, 0);
    for (int i = 0; i < len; ++i) {
        double cx = ax[i] * bx[i] - ay[i] * by[i];
        double cy = ax[i] * by[i] + ay[i] * bx[i];
        ax[i] = cx, ay[i] = cy;
    }
    fft(ax, ay, len, 1);
    for (int i = 0; i < len; ++i)
        ans[i] = (int) (ax[i] + 0.5);
    return len;
}

string mul(string sa, string sb) {
    int l1, l2, l;
    int i;
    string ans;
    memset(sum, 0, sizeof(sum));
    l1 = sa.size();
    l2 = sb.size();
    for (i = 0; i < l1; i++)
        x1[i] = sa[l1 - i - 1] - '0';
    for (i = 0; i < l2; i++)
        x2[i] = sb[l2 - i - 1] - '0';
    l = solve(x1, l1, x2, l2, sum);
    for (i = 0; i < l || sum[i] >= 10; i++) // 进位
    {
        sum[i + 1] += sum[i] / 10;
        sum[i] %= 10;
    }
    l = i;
    while (sum[l] <= 0 && l > 0) l--; // 检索最高位
    for (i = l; i >= 0; i--) ans += sum[i] + '0'; // 倒序输出
    return ans;
}

string Pow(string a, int n) {
    if (n == 1) return a;
    if (n & 1) return mul(Pow(a, n - 1), a);
    string ans = Pow(a, n / 2);
    return mul(ans, ans);
}

// 高精度GCD
string add(string a, string b) {
    const int L = 1e5;
    string ans;
    int na[L] = {0}, nb[L] = {0};
    int la = a.size(), lb = b.size();
    for (int i = 0; i < la; i++) na[la - 1 - i] = a[i] - '0';
    for (int i = 0; i < lb; i++) nb[lb - 1 - i] = b[i] - '0';
    int lmax = la > lb ? la : lb;
    for (int i = 0; i < lmax; i++) na[i] += nb[i], na[i + 1] += na[i] / 10, na[i] %= 10;
    if (na[lmax]) lmax++;
    for (int i = lmax - 1; i >= 0; i--) ans += na[i] + '0';
    return ans;
}

string mul(string a, string b) {
    const int L = 1e5;
    string s;
    int na[L], nb[L], nc[L], La = a.size(), Lb = b.size();//na存储被乘数，nb存储乘数，nc存储积
    fill(na, na + L, 0);
    fill(nb, nb + L, 0);
    fill(nc, nc + L, 0);//将na,nb,nc都置为0
    for (int i = La - 1; i >= 0; i--) na[La - i] = a[i] - '0';//将字符串表示的大整形数转成i整形数组表示的大整形数
    for (int i = Lb - 1; i >= 0; i--) nb[Lb - i] = b[i] - '0';
    for (int i = 1; i <= La; i++)
        for (int j = 1; j <= Lb; j++)
            nc[i + j - 1] += na[i] * nb[j];//a的第i位乘以b的第j位为积的第i+j-1位（先不考虑进位）
    for (int i = 1; i <= La + Lb; i++)
        nc[i + 1] += nc[i] / 10, nc[i] %= 10;//统一处理进位
    if (nc[La + Lb]) s += nc[La + Lb] + '0';//判断第i+j位上的数字是不是0
    for (int i = La + Lb - 1; i >= 1; i--)
        s += nc[i] + '0';//将整形数组转成字符串
    return s;
}

int sub(int *a, int *b, int La, int Lb) {
    if (La < Lb) return -1;//如果a小于b，则返回-1
    if (La == Lb) {
        for (int i = La - 1; i >= 0; i--)
            if (a[i] > b[i]) break;
            else if (a[i] < b[i]) return -1;//如果a小于b，则返回-1

    }
    for (int i = 0; i < La; i++)//高精度减法
    {
        a[i] -= b[i];
        if (a[i] < 0) a[i] += 10, a[i + 1]--;
    }
    for (int i = La - 1; i >= 0; i--)
        if (a[i]) return i + 1;//返回差的位数
    return 0;//返回差的位数

}

string div(string n1, string n2, int nn)//n1,n2是字符串表示的被除数，除数,nn是选择返回商还是余数
{
    const int L = 1e5;
    string s, v;//s存商,v存余数
    int a[L], b[L], r[L], La = n1.size(), Lb = n2.size(), i, tp = La;//a，b是整形数组表示被除数，除数，tp保存被除数的长度
    fill(a, a + L, 0);
    fill(b, b + L, 0);
    fill(r, r + L, 0);//数组元素都置为0
    for (i = La - 1; i >= 0; i--) a[La - 1 - i] = n1[i] - '0';
    for (i = Lb - 1; i >= 0; i--) b[Lb - 1 - i] = n2[i] - '0';
    if (La < Lb || (La == Lb && n1 < n2)) {
        //cout<<0<<endl;
        return n1;
    }//如果a<b,则商为0，余数为被除数
    int t = La - Lb;//除被数和除数的位数之差
    for (int i = La - 1; i >= 0; i--)//将除数扩大10^t倍
        if (i >= t) b[i] = b[i - t];
        else b[i] = 0;
    Lb = La;
    for (int j = 0; j <= t; j++) {
        int temp;
        while ((temp = sub(a, b + j, La, Lb - j)) >= 0)//如果被除数比除数大继续减
        {
            La = temp;
            r[t - j]++;
        }
    }
    for (i = 0; i < L - 10; i++) r[i + 1] += r[i] / 10, r[i] %= 10;//统一处理进位
    while (!r[i]) i--;//将整形数组表示的商转化成字符串表示的
    while (i >= 0) s += r[i--] + '0';
    //cout<<s<<endl;
    i = tp;
    while (!a[i]) i--;//将整形数组表示的余数转化成字符串表示的</span>
    while (i >= 0) v += a[i--] + '0';
    if (v.empty()) v = "0";
    //cout<<v<<endl;
    if (nn == 1) return s;
    if (nn == 2) return v;
}

bool judge(string s)//判断s是否为全0串
{
    for (int i = 0; i < s.size(); i++)
        if (s[i] != '0') return false;
    return true;
}

string gcd(string a, string b)//求最大公约数
{
    string t;
    while (!judge(b))//如果余数不为0，继续除
    {
        t = a;//保存被除数的值
        a = b;//用除数替换被除数
        b = div(t, b, 2);//用余数替换除数
    }
    return a;
}

// 高精度进制转换
//将字符串表示的10进制大整数转换为m进制的大整数
//并返回m进制大整数的字符串
bool judge(string s)//判断串是否为全零串
{
    for (int i = 0; i < s.size(); i++)
        if (s[i] != '0') return 1;
    return 0;
}

string solve(string s, int n, int m)//n进制转m进制只限0-9进制，若涉及带字母的进制，稍作修改即可
{
    string r, ans;
    int d = 0;
    if (!judge(s)) return "0";//特判
    while (judge(s))//被除数不为0则继续
    {
        for (int i = 0; i < s.size(); i++) {
            r += (d * n + s[i] - '0') / m + '0';//求出商
            d = (d * n + (s[i] - '0')) % m;//求出余数
        }
        s = r;//把商赋给下一次的被除数
        r = "";//把商清空
        ans += d + '0';//加上进制转换后数字
        d = 0;//清空余数
    }
    reverse(ans.begin(), ans.end());//倒置下
    return ans;
}

// 高精度求平方根
const int L = 2015;

string add(string a, string b)//只限两个非负整数相加
{
    string ans;
    int na[L] = {0}, nb[L] = {0};
    int la = a.size(), lb = b.size();
    for (int i = 0; i < la; i++) na[la - 1 - i] = a[i] - '0';
    for (int i = 0; i < lb; i++) nb[lb - 1 - i] = b[i] - '0';
    int lmax = la > lb ? la : lb;
    for (int i = 0; i < lmax; i++) na[i] += nb[i], na[i + 1] += na[i] / 10, na[i] %= 10;
    if (na[lmax]) lmax++;
    for (int i = lmax - 1; i >= 0; i--) ans += na[i] + '0';
    return ans;
}

string sub(string a, string b)//只限大的非负整数减小的非负整数
{
    string ans;
    int na[L] = {0}, nb[L] = {0};
    int la = a.size(), lb = b.size();
    for (int i = 0; i < la; i++) na[la - 1 - i] = a[i] - '0';
    for (int i = 0; i < lb; i++) nb[lb - 1 - i] = b[i] - '0';
    int lmax = la > lb ? la : lb;
    for (int i = 0; i < lmax; i++) {
        na[i] -= nb[i];
        if (na[i] < 0) na[i] += 10, na[i + 1]--;
    }
    while (!na[--lmax] && lmax > 0);
    lmax++;
    for (int i = lmax - 1; i >= 0; i--) ans += na[i] + '0';
    return ans;
}

string mul(string a, string b)//高精度乘法a,b,均为非负整数
{
    string s;
    int na[L], nb[L], nc[L], La = a.size(), Lb = b.size();//na存储被乘数，nb存储乘数，nc存储积
    fill(na, na + L, 0);
    fill(nb, nb + L, 0);
    fill(nc, nc + L, 0);//将na,nb,nc都置为0
    for (int i = La - 1; i >= 0; i--) na[La - i] = a[i] - '0';//将字符串表示的大整形数转成i整形数组表示的大整形数
    for (int i = Lb - 1; i >= 0; i--) nb[Lb - i] = b[i] - '0';
    for (int i = 1; i <= La; i++)
        for (int j = 1; j <= Lb; j++)
            nc[i + j - 1] += na[i] * nb[j];//a的第i位乘以b的第j位为积的第i+j-1位（先不考虑进位）
    for (int i = 1; i <= La + Lb; i++)
        nc[i + 1] += nc[i] / 10, nc[i] %= 10;//统一处理进位
    if (nc[La + Lb]) s += nc[La + Lb] + '0';//判断第i+j位上的数字是不是0
    for (int i = La + Lb - 1; i >= 1; i--)
        s += nc[i] + '0';//将整形数组转成字符串
    return s;
}

int sub(int *a, int *b, int La, int Lb) {
    if (La < Lb) return -1;//如果a小于b，则返回-1
    if (La == Lb) {
        for (int i = La - 1; i >= 0; i--)
            if (a[i] > b[i]) break;
            else if (a[i] < b[i]) return -1;//如果a小于b，则返回-1

    }
    for (int i = 0; i < La; i++)//高精度减法
    {
        a[i] -= b[i];
        if (a[i] < 0) a[i] += 10, a[i + 1]--;
    }
    for (int i = La - 1; i >= 0; i--)
        if (a[i]) return i + 1;//返回差的位数
    return 0;//返回差的位数

}

string div(string n1, string n2, int nn)//n1,n2是字符串表示的被除数，除数,nn是选择返回商还是余数
{
    string s, v;//s存商,v存余数
    int a[L], b[L], r[L], La = n1.size(), Lb = n2.size(), i, tp = La;//a，b是整形数组表示被除数，除数，tp保存被除数的长度
    fill(a, a + L, 0);
    fill(b, b + L, 0);
    fill(r, r + L, 0);//数组元素都置为0
    for (i = La - 1; i >= 0; i--) a[La - 1 - i] = n1[i] - '0';
    for (i = Lb - 1; i >= 0; i--) b[Lb - 1 - i] = n2[i] - '0';
    if (La < Lb || (La == Lb && n1 < n2)) {
        //cout<<0<<endl;
        return n1;
    }//如果a<b,则商为0，余数为被除数
    int t = La - Lb;//除被数和除数的位数之差
    for (int i = La - 1; i >= 0; i--)//将除数扩大10^t倍
        if (i >= t) b[i] = b[i - t];
        else b[i] = 0;
    Lb = La;
    for (int j = 0; j <= t; j++) {
        int temp;
        while ((temp = sub(a, b + j, La, Lb - j)) >= 0)//如果被除数比除数大继续减
        {
            La = temp;
            r[t - j]++;
        }
    }
    for (i = 0; i < L - 10; i++) r[i + 1] += r[i] / 10, r[i] %= 10;//统一处理进位
    while (!r[i]) i--;//将整形数组表示的商转化成字符串表示的
    while (i >= 0) s += r[i--] + '0';
    //cout<<s<<endl;
    i = tp;
    while (!a[i]) i--;//将整形数组表示的余数转化成字符串表示的</span>
    while (i >= 0) v += a[i--] + '0';
    if (v.empty()) v = "0";
    //cout<<v<<endl;
    if (nn == 1) return s;
    if (nn == 2) return v;
}

bool cmp(string a, string b) {
    if (a.size() < b.size()) return 1;//a小于等于b返回真
    if (a.size() == b.size() && a <= b) return 1;
    return 0;
}

string DeletePreZero(string s) {
    int i;
    for (i = 0; i < s.size(); i++)
        if (s[i] != '0') break;
    return s.substr(i);
}

string BigInterSqrt(string n) {
    n = DeletePreZero(n);
    string l = "1", r = n, mid, ans;
    while (cmp(l, r)) {
        mid = div(add(l, r), "2", 1);
        if (cmp(mul(mid, mid), n)) ans = mid, l = add(mid, "1");
        else r = sub(mid, "1");
    }
    return ans;
}