#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stack>


#pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

inline int count(int state) {
    return __builtin_popcount(state);
}


using PII = pair<int, int>;
constexpr int N = 100010;

int n, m;

struct Node {
    int s[2], p, v;//儿子,父节点,编号
    int size, flag;//子树节点个数, 有没有翻转

    void init(int _v, int _p) {
        v = _v, p = _p;
        size = 1;
    }
} tr[N];

int root, idx;

void pushup(int x) {
    tr[x].size = tr[tr[x].s[0]].size + tr[tr[x].s[1]].size + 1;
}

void pushdown(int x) {
    // 如果当前子树需要翻转 48.34
    if (tr[x].flag) {
        //要翻转整颗子树，要先把左右两个儿子翻转，然后递归翻转左右两棵子树
        swap(tr[x].s[0], tr[x].s[1]);
        tr[tr[x].s[0]].flag ^= 1;//翻转标记往下传
        tr[tr[x].s[1]].flag ^= 1;//翻转标记往下传
        tr[x].flag = 0;//当前标记清空
    }
}

void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;  // k=0表示x是y的左儿子；k=1表示x是y的右儿子
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;// 边1 z原来的儿子y变为x  x的父节点变为z
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;// 边3 y的左儿子变为x的右儿子B,x的右儿子的父节点变为y
    tr[x].s[k ^ 1] = y, tr[y].p = x;// 边2 x的右儿子变为y,y的父节点变为x
    pushup(y), pushup(x);// A,B,C三个点信息没变,但x,y子树信息变了,又y在x下面,所以先维护更新y子树,再维护更新x子树
}

void splay(int x, int k) {
    while (tr[x].p != k) {
        int y = tr[x].p, z = tr[y].p;
        if (z != k)
            // 如果是折线关系  ==  x是y的右/左儿子 且 y是z的左/右儿子  一0一1
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);//折线rotate两次x
            else rotate(y);//直线rotate 一次y一次x
        rotate(x);
    }
    if (!k) root = x;//如果k==0 根节点更新为x
}

void insert(int v) {
    int u = root, p = 0;
    while (u) p = u, u = tr[u].s[v > tr[u].v];//一直往下递归直到u为null
    u = ++idx;
    if (p) tr[p].s[v > tr[p].v] = u;//如果有父节点,父节点儿子信息更新为u
    tr[u].init(v, p);//初始化点u的值和父节点
    splay(u, 0);//插入后将当前点u转到根节点上
}

int get_k(int k) {
    int u = root;
    while (true) {
        pushdown(u);
        if (tr[tr[u].s[0]].size >= k) u = tr[u].s[0];
        else if (tr[tr[u].s[0]].size + 1 == k) return u;
        else k -= tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
    }
    return -1;//找不到返回-1
}

void output(int u) {
    pushdown(u);
    // 如果u有左儿子 先递归输出左儿子
    if (tr[u].s[0]) output(tr[u].s[0]);
    // 如果u不是哨兵输出当前点
    if (tr[u].v >= 1 && tr[u].v <= n) printf("%d ", tr[u].v);
    // 如果u有右儿子 递归输出右儿子
    if (tr[u].s[1]) output(tr[u].s[1]);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n + 1; i++) insert(i);//插入哨兵 0,n+1 防止L-1和R+1越界
    while (m--) {
        int l, r;
        scanf("%d%d", &l, &r);
        //因为哨兵要翻转的从[L,R]变为[L+1,R+1] 则要找L和R+2作为L+1的前继和R+1的后继
        l = get_k(l), r = get_k(r + 2);
        // 左端点l转到根,右端点r转到左端点下面
        splay(l, 0), splay(r, l);
        // 只要将r的左子树[L+1,R+1]翻转
        tr[tr[r].s[0]].flag ^= 1;
    }
    output(root);
    return 0;
}
