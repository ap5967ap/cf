const int mod = 1e9 + 7;

int add(int a, int b) 
{
    a %= mod; b %= mod;
    int res = a + b;
    if (res >= mod) res -= mod;
    return res;
}

int sub(int a, int b) 
{
    a %= mod; b %= mod;
    int res = a - b;
    if (res < 0) res += mod;
    return res;
}

int mult(int a, int b) 
{
    return 1LL * (a % mod) * (b % mod) % mod;
}

int power(int a, int b, int m = mod) 
{
    a %= m;
    long long res = 1;
    while (b > 0) 
    {
        if (b & 1) res = res * a % m;
        a = 1LL * a * a % m;
        b >>= 1;
    }
    return res;
}

int div(int a, int b) 
{
    return mult(a, power(b, mod - 2, mod));
}
