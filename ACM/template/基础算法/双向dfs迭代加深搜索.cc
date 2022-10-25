int D;
bool found;
template <class T>
void dfs(T x, int d, int dir)
{
    if (H[x] + dir == 3)
        found = true;
    H[x] = dir;
    if (d == D)
        return;
    // 这里需要递归搜索当前状态能够转移到的新状态
}

// 在main函数中...
while (D <= MAXD / 2) // MAXD为题中要求的最大深度
{
    dfs(st, 0, 1); // st为起始状态
    if (found)
        // ...
        // 题中所给最大深度为奇数时这里要判断一下
    dfs(ed, 0, 2); // ed为终止状态
    if (found)
        // ...
    D++;
}