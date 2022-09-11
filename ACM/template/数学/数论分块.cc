// ceil(n / ceil(n / l))
for (int l = 1, r; l <= n; l = r + 1)
{
    r = n / (n / l);
    ans += (r - l + 1) * (n / l);
}