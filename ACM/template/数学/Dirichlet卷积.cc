int n, mod;
ll f[N], g[N], h[N];

void Dirichlet() {
    memset(h, 0, sizeof h);
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; j += i) {
            h[j] = (h[j] + f[i] * g[j / i]) % mod;
        }
    }
    for (int i = 1; i <= n; ++i) {
        f[i] = h[i];
    }
}

void fpow(ll* res, ll *yi, int k){
    while (k){
        if (k & 1) Dirichlet(res, yi);
        Dirichlet(yi, yi);
        k >>= 1;
    }
}
