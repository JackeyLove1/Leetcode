/*
unsigned constexpr const_hash(char const *input) {
    return *input ?
           static_cast<unsigned int>(*input) + 33 * const_hash(input + 1) :
           5381;
}
*/
class HashString {
private:
    typedef unsigned long long ull;
    const int P = 131;
    vector<ull> p;
    vector<ull> prefix;
    int n;
public:
    HashString (string s) {
        n = s.size();
        s.insert(0, "0");
        p.resize(n + 1), p[0] = 1;
        prefix.resize(n + 1, 0);
        for(int i=1; i<=n; i++) {
            p[i] = p[i-1] * P;
            prefix[i] = prefix[i - 1] * P + s[i];
        }
    }

    ull get (int l, int r) {
        l++, r++;
        return prefix[r] - prefix[l - 1] * p[r - l + 1];
    }
};

int find (string s) {
    int n = (int) s.size();
    auto hs = HashString(s);
    for (int i = 1; i < n; i++) {
        auto v = hs.get(0, i-1);
        int j = i, flag = 1;
        for (; j + i - 1 < n; j += i) {
            if (! (v == hs.get(j, j + i - 1))) {
                flag = 0;
                break;
            }
        }
        if (flag ) {
            if (j == n) {
                return 0;
            } else if (hs.get(j, n - 1) == hs.get(0, n - j - 1)) {
                return i - (n - j);
            }
        }
    }
    return n;
}

int main () {
    int n; cin >> n;
    while (n -- ) {
        string s; cin >> s;
        cout << find(s) << endl;
    }
    return 0;
} 