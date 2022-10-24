#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

const int N = 100010;
int n, m;
std::array<int, N> a, root;
int idx{0};
vector<int> nums;

struct Node {
    int l, r, cnt;
};

std::array<Node, N * 24> tr{};


int find(int x) {
    return lower_bound(nums.begin(), nums.end(), x) - nums.begin();
}

// 对左右边界建立节点并编号, build是建立好骨架, 每个版本insert改不同数据
int build(int l, int r) {
    int p = ++idx;
    if (l == r) return p;
    int mid = l + r >> 1;
    tr[p].l = build(l, mid), tr[p].r = build(mid + 1, r);
    return p;
}

// l, r是要放入的坐标范围, x是要插入的数离散化后的位置
int insert(int p, int l, int r, int x) {
    // 假设现在是从外界第一次执行insert, 那么调用的时候, p必定是根节点,
    // 那么q就相当于复制了一个根节点, 从节点q进入这棵树的时候, 也能得到之前的所有内容.
    // 同理, 再往下二分递归的时候, insert会继续复制根节点的左(右)子树, 一直递归直到l==r之前,
    // q和原来的p都是一毛一样. 直到l==r才真正插入了新点, 每次插入的时间空间复杂度都是lgk,
    // 总加起来就是lg1+lg2+...+lgn = lg(n!), 根据stirling公式, 结果为nlgn   (大O)
    int q = ++idx;
    tr[q] = tr[p];
    if (l == r)  // 如果区间长度为1, 说明就是放这里了
    {
        // tr[q].cnt++是表示插在这个叶节点上
        // 这个线段树只是保存的每个区间里面的元素个数
        // 每次插入都只是覆盖到的那堆区间里面的cnt发生+1
        tr[q].cnt++;
        return q;
    }

    int mid = l + r >> 1;
    if (x <= mid) tr[q].l = insert(tr[p].l, l, mid, x);
    else tr[q].r = insert(tr[p].r, mid + 1, r, x);
    tr[q].cnt = tr[tr[q].l].cnt + tr[tr[q].r].cnt;  // 相当于pushup了
    return q;
}


// l ,r是检索范围, q是当前第r个节点root[r]能包含1~r之间所有
// p的输入是root[l-1], 作用是剔除这个根节点所包含数据的影响
int query(int q, int p, int l, int r, int k) {
    if (l == r) return r; // 如果找到位置

    // 目标是求l r之间的第k小
    // tr[tr[q].l].cnt - tr[tr[p].l].cnt的结果是求出在p之后插入到q这些数之后,
    // 有多少个数(cnt)插入了p的左子树, 由于p的内容肯定不能出现在l r之间(p根节点就是root[l-1]),
    // 所以cnt就是相当于"存在q左子树里面但不存在于1, l 之间的数的个数"
    int cnt = tr[tr[q].l].cnt - tr[tr[p].l].cnt;

    int mid = l + r >> 1;
    // k <= cnt说明要找的元素在q的左子树里面, 同时这里面也要剔除掉包含在p左子树的内容
    if (k <= cnt) return query(tr[q].l, tr[p].l, l, mid, k);
    else return query(tr[q].r, tr[p].r, mid + 1, r, k - cnt);  // 类似同上
}


int main() {
    scanf("%d%d", &n, &m);
    nums.reserve(n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        nums.push_back(a[i]);  //离散化使用
    }

    // 离散化
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    // 构造线段树, 构造n个版本的线段树
    // 第0个版本的什么都没有就用build, build是建立好骨架, 每个版本insert改不同数据
    root[0] = build(0, nums.size() - 1);
    // 后面的每插入一个点算一个版本, 每次插入都只是比上一个版本多1个数
    // 左右参数给0和nums.size()-1是因为离散化之后的值域就是在0, nums.size()-1之间
    // 要插入必须得把这些地方全包才能保证找得到插入点
    for (int i = 1; i <= n; i++)
        root[i] = insert(root[i - 1], 0, nums.size() - 1, find(a[i]));


    while (m--) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", nums[query(root[r], root[l - 1], 0, nums.size() - 1, k)]);
    }
    return 0;
}