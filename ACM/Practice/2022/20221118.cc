constexpr int N = 1e7 + 100;
int ch[N][30], cnt[N], ne[N], idx{0};
int n, m;

inline void insert(char *s) {
    int p = 0;
    for(int i = 0; s[i]; ++i){
        if (!ch[p][i]) ch[p][i] = ++idx;
        p = ch[p][i];
    }
    ++cnt[p];
}

inline void build(){
    std::queue<int> q;
    for(int i = 0; i < 26; ++i){
        if(ch[0][i]) q.push(ch[0][i]);
    }
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        for(int i = 0; i < 26; ++i){
            int v = ch[u][i];
            if (v) ne[v] = ch[ne[u]][i], q.push(v);
            else ch[u][i] = ch[ne[u]][i];
        }
    }
}

inline int query(char *s) {
    int res = 0;
    for(int i = 0, p = 0; s[i]; ++i){
        p = ch[p][i];
        for(int j = p; j && ~cnt[j] ; j = ne[j]){
            res += cnt[j], cnt[j] = -1;
        
        }
    }
    return res;
}

char s[N];

int main() {
    // fhj();
    cin >> n;
    for (int i = 0; i < n; ++i) {
        scanf("%s", s);
        insert(s);
    }
    build();
    scanf("%s", s);
    cout << query(s) << endl;
    return 0;
}

namespace kmp{
    constexpr int N = 1e7 + 100;
int ch[N][30], cnt[N], ne[N], idx{0};
int n, m;
char s[N], t[N];
int main(){
    std::cin >> s + 1 >> t + 1;
    const int n = std::strlen(s+1), m = std::strlen(t+1);
    memset(ne, 0, sizeof ne);
    for(int i = 1, j = 0; i <= n; ++i){
        while (j && s[i] != s[j+1]) j = ne[j];
        if (s[i] == s[j+1]) ++j;
        ne[i] = j;
    }
    for(int i = 1, j = 0; i <= m; ++i){
        while (j && t[i] != s[j+1]) j = ne[j];
        if (t[i] == s[j+1]) ++j;
        if (j == n){
            std::cout << i - n + 1 << std::endl;
            j = ne[j];
        } 
    }
}
}

namespace exkmp{
    constexpr int N = 1e6 + 100;
char s[N], t[N];
int z[N], p[N];
inline void get_z(const char* s){
    const int n = std::strlen(s+1);
    z[1] = n;
    for(int i = 2, l, r = 0; i <= n; ++i){
        if (i <= r) z[i] = std::min(r - i + 1, z[i -l + 1]);
        while(i <= n && s[1+z[i]] == s[i+z[i]]) ++z[i];
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - r;
    }

}
}


