template<typename T, const int P>
class combinatorics
{
    //combinatorics<mint,2> c(200);
    //2 is the number whose power will be precomputed
public:
    int n;
    vector<T> inv, fac, ifac, pw;
    combinatorics (int n) : n(n), inv(n+1), fac(n+1), ifac(n+1), pw(n+1)
    {
        fac[0] = inv[0] = ifac[0] = pw[0] = T(1);
 
        for(int i = 1; i <= n; i ++)
            inv[i] = T(1)/T(i), fac[i] = fac[i - 1] * T(i), ifac[i] = ifac[i - 1] * inv[i], pw[i] = pw[i - 1] * T(P);
    }

    T ncr(int n, int r)
    {
        if(n < r or r < 0)
            return 0;
        return fac[n] * ifac[r] * ifac[n - r];
    }
};