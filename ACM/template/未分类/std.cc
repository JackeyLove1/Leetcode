// 求二进制中1的个数
std::popcount(x) // C++20
__builtin_popcount 

// fast read/write
namespace IO {
template<typename T>inline bool read(T &x) {
    x = 0;
    char ch = getchar();
    bool flag = 0, ret = 0;

    while (ch < '0' || ch > '9')
        flag = flag || (ch == '-'), ch = getchar();

    while (ch >= '0' && ch <= '9')
        x = x * 10 + ch - '0', ch = getchar(), ret = 1;

    x = flag ? -x : x;
    return ret;
}
template<typename T, typename ...Args>inline bool read(T &a, Args &...args) {
    return read(a) && read(args...);
}
template<typename T>void prt(T x) {
    if (x > 9)
        prt(x / 10);

    putchar(x % 10 + '0');
}
template<typename T>inline void put(T x) {
    if (x < 0)
        putchar('-'), x = -x;

    prt(x);
}
template<typename T>inline void put(char ch, T x) {
    if (x < 0)
        putchar('-'), x = -x;

    prt(x);
    putchar(ch);
}
template<typename T, typename ...Args>inline void put(T a, Args ...args) {
    put(a);
    put(args...);
}
template<typename T, typename ...Args>inline void put(const char ch, T a, Args ...args) {
    put(ch, a);
    put(ch, args...);
}
inline void put(string s) {
    for (int i = 0, sz = s.length(); i < sz; i++)
        putchar(s[i]);
}
inline void put(const char *s) {
    for (int i = 0, sz = strlen(s); i < sz; i++)
        putchar(s[i]);
}
}
using namespace IO;

static constexpr int N = 1e6 + 100;
using ll = long long;

// 并查集
class DSU {
public:
    DSU() {
        for (int i = 1; i < N * 2; ++i)
            fa[i] = i;
    }
    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    inline void unity(int x, int y) {
        fa[find(x)] = find(y);
    }
private:
    int fa[N << 1];
} dsu;

// 边
class Edge {
public:
    int u, v;
    ll w;
} e[N << 1];

