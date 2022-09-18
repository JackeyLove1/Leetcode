using ll = long long;
char s[999];
int m;
const int N = 1e6 + 10;
ll p[N], st[N], cnt;

// x * y % mod = ((x % mod) * (y % mod)) % mod
int big_mod(int k) {
	int q = 0;
	for (int i = 0; s[i]; i++) {
		q = (q * 10 + s[i] - '0') % k;
	}
	return q;
}

/*
int big_mod(const char *s, int mod) {
    int q = 0;
    const auto len = strlen(s);
    for (int i = 0; i < len; ++i) {
        q = (q * 10 + s[i] - '0') % mod;
    }
    return q;
}
*/
