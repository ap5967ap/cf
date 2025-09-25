int power(int a, int b)
{
    if (b == 0)
        return 1;
    int res = power(a, b / 2);
    if (b % 2)
        return res * res * a;
    else
        return res * res;
}
int POWM(int a, int b, int m)
{
    a %= m;
    int res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
int modinv(int a, int m) 
{ 
    return POWM(a, m - 2, m); 
}
