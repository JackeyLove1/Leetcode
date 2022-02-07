#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010, INF = 1e8;

int n;
struct Node
{
    int l, r;
    int key, val;
    int cnt, size;
}tr[N];

int root, idx;

void pushup(int p)
{
    tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + tr[p].cnt;
}

int get_node(int key)
{
    tr[ ++ idx].key = key;
    tr[idx].val = rand();
    tr[idx].cnt = tr[idx].size = 1;
    return idx;
}

void zig(int &p)    // 右旋
{
    int q = tr[p].l;
    tr[p].l = tr[q].r, tr[q].r = p, p = q;
    pushup(tr[p].r), pushup(p);
}

void zag(int &p)    // 左旋
{
    int q = tr[p].r;
    tr[p].r = tr[q].l, tr[q].l = p, p = q;
    pushup(tr[p].l), pushup(p);
}

void build()
{
    get_node(-INF), get_node(INF);
    root = 1, tr[1].r = 2;
    pushup(root);

    if (tr[1].val < tr[2].val) zag(root);
}


void insert(int &p, int key)
{
    if (!p) p = get_node(key);
    else if (tr[p].key == key) tr[p].cnt ++ ;
    else if (tr[p].key > key)
    {
        insert(tr[p].l, key);
        if (tr[tr[p].l].val > tr[p].val) zig(p);
    }
    else
    {
        insert(tr[p].r, key);
        if (tr[tr[p].r].val > tr[p].val) zag(p);
    }
    pushup(p);
}

void remove(int &p, int key)
{
    if (!p) return;
    if (tr[p].key == key)
    {
        if (tr[p].cnt > 1) tr[p].cnt -- ;
        else if (tr[p].l || tr[p].r)
        {
            if (!tr[p].r || tr[tr[p].l].val > tr[tr[p].r].val)
            {
                zig(p);
                remove(tr[p].r, key);
            }
            else
            {
                zag(p);
                remove(tr[p].l, key);
            }
        }
        else p = 0;
    }
    else if (tr[p].key > key) remove(tr[p].l, key);
    else remove(tr[p].r, key);

    pushup(p);
}

int get_rank_by_key(int p, int key)    // 通过数值找排名
{
    if (!p) return 0;   // 本题中不会发生此情况
    if (tr[p].key == key) return tr[tr[p].l].size + 1;
    if (tr[p].key > key) return get_rank_by_key(tr[p].l, key);
    return tr[tr[p].l].size + tr[p].cnt + get_rank_by_key(tr[p].r, key);
}

int get_key_by_rank(int p, int rank)   // 通过排名找数值
{
    if (!p) return INF;     // 本题中不会发生此情况
    if (tr[tr[p].l].size >= rank) return get_key_by_rank(tr[p].l, rank);
    if (tr[tr[p].l].size + tr[p].cnt >= rank) return tr[p].key;
    return get_key_by_rank(tr[p].r, rank - tr[tr[p].l].size - tr[p].cnt);
}

int get_prev(int p, int key)   // 找到严格小于key的最大数
{
    if (!p) return -INF;
    if (tr[p].key >= key) return get_prev(tr[p].l, key);
    return max(tr[p].key, get_prev(tr[p].r, key));
}

int get_next(int p, int key)    // 找到严格大于key的最小数
{
    if (!p) return INF;
    if (tr[p].key <= key) return get_next(tr[p].r, key);
    return min(tr[p].key, get_next(tr[p].l, key));
}

int main()
{
    build();

    scanf("%d", &n);
    while (n -- )
    {
        int opt, x;
        scanf("%d%d", &opt, &x);
        if (opt == 1) insert(root, x);
        else if (opt == 2) remove(root, x);
        else if (opt == 3) printf("%d\n", get_rank_by_key(root, x) - 1);
        else if (opt == 4) printf("%d\n", get_key_by_rank(root, x + 1));
        else if (opt == 5) printf("%d\n", get_prev(root, x));
        else printf("%d\n", get_next(root, x));
    }

    return 0;
}

/*----------------------------------------------------------------
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

const int N = 100010, INF = 1e8 + 7;

int n, m;

struct node{
    int l, r;//左右儿子
    int key;//真正的权值
    int val;//随机的平衡因子
    int cnt;//相同的数有多少个
    int size;//整棵树的结点个数
}tr[N];

int root, idx;

void pushup(int p){
    tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + tr[p].cnt;
}

int get_node(int key){
    tr[ ++ idx].key = key;
    tr[idx].val = rand();//!堆所维护的val是随机值,为了让树变得更随机以增加搜索树效率
    tr[idx].cnt = tr[idx].size = 1;
    return idx;
}

//!往左递归时左儿子val大于根节点val就右旋
//!往右递归时右儿子val大于根节点val就左旋
//      x    右旋         y
//       / \   zig        / \
//      y   b  --->      a   x
//     / \     <---         / \
//    a   z    zag         z   b
//             左旋              

void zig(int &p){//右旋
    int q = tr[p].l;
    tr[p].l = tr[q].r;tr[q].r = p, p = q;
    pushup(tr[p].r), pushup(p);
}

void zag(int &p){//左旋
    int q = tr[p].r;
    tr[p].r = tr[q].l;tr[q].l = p, p = q;
    pushup(tr[p].l), pushup(p);
}

void build(){
    get_node(-INF), get_node(INF);//两个哨兵边界
    root = 1;//-INF
    tr[root].r = 2;//INF
    pushup(root);

    if(tr[1].val < tr[2].val)zag(root);
    //因为val是随机的，所以要判断右儿子（因为当前只有两个点，只有root右儿子）
    //如果右儿子随机到的val大于root就左旋
}

// operator 1 : 插入一个数

void insert(int &p, int key){
    if(!p) p = get_node(key);//如果树中没有这个就新建一个结点
    else if(tr[p].key == key) tr[p].cnt ++ ;
    else if(tr[p].key > key){//大就在左边
        insert(tr[p].l, key);
        if(tr[tr[p].l].val > tr[p].val)zig(p);
    }
    else { // 否则就在右边
        insert(tr[p].r, key);
        if(tr[tr[p].r].val > tr[p].val)zag(p);
    }
    pushup(p);
}

// operator 2 : 删除一个数

void remove(int &p, int key){//删除操作：每次旋转都会使得它的深度+1,一直旋转到叶子节点,然后删除
    if(!p) return ;
    if(tr[p].key == key){//找到了
        if(tr[p].cnt > 1) tr[p].cnt -- ;
        else if(tr[p].l || tr[p].r){

            //!右旋往右走
            if(!tr[p].r || tr[tr[p].l].val > tr[tr[p].r].val){
            //如果没有右子树，右旋一次就到叶子节点了。或者说左子树随机到的val > 右子树随机到的val，那么必须右旋
                zig(p);
                remove(tr[p].r, key);
            }

            //!左旋往左走
            else {
                zag(p);
                remove(tr[p].l, key);
            }
        }
        else p = 0;//如果到了叶子节点就直接删掉
    }
    else if(tr[p].key > key) remove(tr[p].l, key);//往左边找
    else remove(tr[p].r, key);//往右边找

    pushup(p);//每次别忘了pushup，因为本题中维护了一个size
}

//下面的几个函数只是查询不需要修改，所以不用写&p

// operator 3 : 通过数值找排名 

int get_rank_by_key(int p, int key){
    if(!p) return 0;
    
    //如果找到了，返回左子树个数 + 自己(这里不是cnt因为根据题意，要找的排名如果相同就找最左边的,最小的)
    if(tr[p].key == key) return tr[tr[p].l].size + 1;
    if(tr[p].key > key)
        return get_rank_by_key(tr[p].l, key);
    return tr[tr[p].l].size + tr[p].cnt + get_rank_by_key(tr[p].r, key);
}

// operator 4 : 通过排名找数值 

int get_key_by_rank(int p, int rank){
    if(!p) return INF;
    if(tr[tr[p].l].size >= rank) return get_key_by_rank(tr[p].l, rank);
    if(tr[tr[p].l].size + tr[p].cnt >= rank)//左边少加上中间的却大于rank，说明就在中间
        return tr[p].key;
    return get_key_by_rank(tr[p].r, rank - tr[tr[p].l].size - tr[p].cnt);//注意递归到右边时rank要减去左边的
}

// operator 5 : 找到严格小于key的最大数（前驱） 

int get_prev(int p, int key){
    if(!p) return -INF;
    //!左边
    if(tr[p].key >= key) return get_prev(tr[p].l, key);
    //右边和中间
    return max(tr[p].key, get_prev(tr[p].r, key));
}

// operator 6 : 找到严格大于key的最小数（后继） 

int get_next(int p, int key){
    if(!p) return INF;
    //!右边
    if(tr[p].key <= key) return get_next(tr[p].r, key);
    //左边和中间
    return min(tr[p].key, get_next(tr[p].l, key));
}

int main(){
    build();

    scanf("%d", &n);
    while(n -- ){
        int op, x;
        scanf("%d%d", &op, &x);
        if(op == 1)insert(root, x);
        else if(op == 2)remove(root, x);
        else if(op == 3)printf("%d\n", get_rank_by_key(root, x) - 1);//因为最前面有一个自己设的哨兵，所以得到的rank比真实的rank大1
        else if(op == 4)printf("%d\n", get_key_by_rank(root, x + 1));//根据rank找key,前面有一个哨兵,所以rank要从真实的rank+1变成树里的rank
        else if(op == 5)printf("%d\n", get_prev(root, x));
        else printf("%d\n", get_next(root, x));
    }
    return 0;
}

*/