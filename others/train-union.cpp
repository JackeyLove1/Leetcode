constexpr int N = 1e6+100;
int p[N];
int find(int x){
    if(x != p[x]) return p[x] = find(x);
    return x;
}

inline void  merge(int a, int b){
    p[find(a)] = find(b);
}

inline void init(){
    for(int i = 0; i < N; i++) p[i] = i;
}