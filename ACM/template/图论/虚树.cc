// id为dfs序
inline bool cmp(const int x, const int y) { return id[x] < id[y]; }

void build() {
  sort(h + 1, h + k + 1, cmp);
  sta[top = 1] = 1, g.sz = 0, g.head[1] = -1;
  // 1 号节点入栈，清空 1 号节点对应的邻接表，设置邻接表边数为 1
  for (int i = 1, l; i <= k; ++i)
    if (h[i] != 1) {
      // 如果 1 号节点是关键节点就不要重复添加
      l = lca(h[i], sta[top]);
      // 计算当前节点与栈顶节点的 LCA
      if (l != sta[top]) {
        // 如果 LCA 和栈顶元素不同，则说明当前节点不再当前栈所存的链上
        while (id[l] < id[sta[top - 1]])
          // 当次大节点的 Dfs 序大于 LCA 的 Dfs 序
          g.push(sta[top - 1], sta[top]), top--;
        // 把与当前节点所在的链不重合的链连接掉并且弹出
        if (id[l] > id[sta[top - 1]])
          // 如果 LCA 不等于次大节点（这里的大于其实和不等于没有区别）
          g.head[l] = -1, g.push(l, sta[top]), sta[top] = l;
        // 说明 LCA 是第一次入栈，清空其邻接表，连边后弹出栈顶元素，并将 LCA
        // 入栈
        else
          g.push(l, sta[top--]);
        // 说明 LCA 就是次大节点，直接弹出栈顶元素
      }
      g.head[h[i]] = -1, sta[++top] = h[i];
      // 当前节点必然是第一次入栈，清空邻接表并入栈
    }
  for (int i = 1; i < top; ++i)
    g.push(sta[i], sta[i + 1]);  // 剩余的最后一条链连接一下
  return;
}

/*
void dfs(int u){
    dfn[u]=++tim;
    for (int p=head[u];p;p=nxt[p]){
        int v=a[p];
        if (v!=f[u][0]){
            f[v][0]=u;
            minn[v][0]=b[p];
            dep[v]=dep[u]+1;
            dfs(v); 
        }
    }
}
for (int j=1;j<=20;j++){
    for (int i=1;i<=n;i++) f[i][j]=f[f[i][j-1]][j-1],
    minn[i][j]=min(minn[i][j-1],minn[f[i][j-1]][j-1]);
}
int lca(int x,int y){
    if (dep[x]<dep[y]) swap(x,y);
    int tmp=dep[x]-dep[y];
    for (int i=0;i<=20;i++){
        if (tmp&(1<<i)) x=f[x][i];
    }
    if (x==y) return x;
    for (int i=20;i>=0;i--){
        if (f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
    }
    return f[x][0];
}
int dist(int x,int y){
    if (dep[x]<dep[y]) swap(x,y);
    int tmp=dep[x]-dep[y],ret=1e9;
    for (int i=0;i<=20;i++){
        if (tmp&(1<<i)) ret=min(ret,minn[x][i]),x=f[x][i];
    }
    return ret;
}
void insert(int x){
    if (!top){
        st[++top]=x;
        return;
    }
    int ll=lca(st[top],x);
    while (dep[st[top-1]]>dep[ll]&&top>1){
        add(st[top-1],st[top],dist(st[top-1],st[top]));
        top--;
    }
    if (dep[ll]<dep[st[top]]){
        add(ll,st[top],dist(ll,st[top]));
        top--; 
    }
    if (!top||dep[st[top]]<dep[ll]) st[++top]=ll;
    st[++top]=x;
}

*/