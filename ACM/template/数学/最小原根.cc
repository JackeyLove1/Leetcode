int get_minimum_primitive_root(int m)
{
    int phiM = phi(m);
    for (int i = 1;; ++i)
    {
        if (__gcd(i, m) != 1)
            continue;
        auto factors = get_factors(phiM);
        bool ok = true;
        for (auto e : factors)
            if (e != phiM && qpow(i, e, m) == 1)
            {
                ok = false;
                break;
            }
        if (ok)
            return i;
    }
}