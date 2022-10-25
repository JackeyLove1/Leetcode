
using ll = long long;
typedef long long LL;
inline ll C(ll m, ll n, ll p)
{
    return m < n ? 0 : fact[m] * inv(fact[n], p) % p * inv(fact[m - n], p) % p;
}
inline ll lucas(ll m, ll n, ll p)
{
    return n == 0 ? 1 % p : lucas(m / p, n / p, p) * C(m % p, n % p, p) % p;
}

LL calc(LL n, LL x, LL P) {
  if (!n) return 1;
  LL s = 1;
  for (LL i = 1; i <= P; i++)
    if (i % x) s = s * i % P;
  s = Pow(s, n / P, P);
  for (LL i = n / P * P + 1; i <= n; i++)
    if (i % x) s = i % P * s % P;
  return s * calc(n / x, x, P) % P;
}

LL multilucas(LL m, LL n, LL x, LL P) {
  int cnt = 0;
  for (LL i = m; i; i /= x) cnt += i / x;
  for (LL i = n; i; i /= x) cnt -= i / x;
  for (LL i = m - n; i; i /= x) cnt -= i / x;
  return Pow(x, cnt, P) % P * calc(m, x, P) % P * inverse(calc(n, x, P), P) %
         P * inverse(calc(m - n, x, P), P) % P;
}

LL exlucas(LL m, LL n, LL P) {
  int cnt = 0;
  LL p[20], a[20];
  for (LL i = 2; i * i <= P; i++) {
    if (P % i == 0) {
      p[++cnt] = 1;
      while (P % i == 0) p[cnt] = p[cnt] * i, P /= i;
      a[cnt] = multilucas(m, n, i, p[cnt]);
    }
  }
  if (P > 1) p[++cnt] = P, a[cnt] = multilucas(m, n, P, P);
  return CRT(cnt, a, p);
}

