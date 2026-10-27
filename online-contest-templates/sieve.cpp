constexpr int32_t MAX = 1000001;

int32_t sp[MAX] = {};
vector<int32_t> primes;
void Sieve()
{
    sp[1] = 1;
    primes.push_back(2);
    for (int32_t i = 2; i < MAX; i += 2)
        sp[i] = 2;
    for (int32_t i = 3; i < MAX; i += 2)
    {
        if (sp[i]) continue;
        sp[i] = i;
        primes.push_back(i);
        if (1LL * i * i >= MAX) continue;
        for (int32_t j = i * i; j < MAX; j += 2 * i)
        {
            if (!sp[j]) sp[j] = i;
        }
    }
}

vector<pair<int, int>> factorize(int k)
{
    vector<pair<int, int>> pf;
    while (k > 1)
    {
        int p = sp[k];
        int cnt = 0;
        do
        {
            k /= p;
            ++cnt;
        }
        while (k > 1 and sp[k] == p);
        pf.emplace_back(p, cnt);
    }
    return pf;
}

vector<int> getDivisors(int x)
{
    auto pf = factorize(x);
    int total = 1;
    for (auto [p, cnt] : pf)
        total *= cnt + 1;
    vector<int> divisors;
    divisors.reserve(total);
    divisors.push_back(1);
    for (auto [p, cnt] : pf)
    {
        int sz = divisors.size();
        int pw = 1;
        for (int e = 1; e <= cnt; ++e)
        {
            pw *= p;
            for (int j = 0; j < sz; ++j)
                divisors.push_back(divisors[j] * pw);
        }
    }
    return divisors;
}

vector<vector<int32_t>> fac;

void facSieve(int32_t MX = MAX - 1)
{
    fac.clear();
    fac.resize(MX + 1);

    for (int32_t i = 1; i <= MX; ++i)
    {
        for (int32_t j = i; j <= MX; j += i)
            fac[j].push_back(i);
    }
}
