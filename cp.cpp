#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#define dbg(x...) cerr << "[" << #x << "]=["; _print(x)
#else
#define dbg(x...) 
#endif

template <const int &MOD>
struct modular_int
{
    int val;

    modular_int(int64_t v = 0)
    {
        if (v < 0)
            v = v % MOD + MOD;
        if (v >= MOD)
            v %= MOD;
        val = int(v);
    }

    modular_int(uint64_t v)
    {
        if (v >= MOD)
            v %= MOD;
        val = int(v);
    }

    modular_int(int v) : modular_int(int64_t(v)) {}
    modular_int(unsigned v) : modular_int(uint64_t(v)) {}

    explicit operator int() const { return val; }
    explicit operator unsigned() const { return val; }
    explicit operator int64_t() const { return val; }
    explicit operator uint64_t() const { return val; }
    explicit operator double() const { return val; }
    explicit operator long double() const { return val; }

    modular_int &operator+=(const modular_int &other)
    {
        val -= MOD - other.val;
        if (val < 0)
            val += MOD;
        return *this;
    }

    modular_int &operator-=(const modular_int &other)
    {
        val -= other.val;
        if (val < 0)
            val += MOD;
        return *this;
    }

    static unsigned fast_mod(uint64_t x, unsigned m = MOD)
    {
#if !defined(_WIN32) || defined(_WIN64)
        return unsigned(x % m);
#endif
        // Optimized mod for Codeforces 32-bit machines.
        // x must be less than 2^32 * m for this to work, so that x / m fits in an unsigned 32-bit int.
        unsigned x_high = unsigned(x >> 32), x_low = unsigned(x);
        unsigned quot, rem;
        asm("divl %4\n"
            : "=a"(quot), "=d"(rem)
            : "d"(x_high), "a"(x_low), "r"(m));
        return rem;
    }

    modular_int &operator*=(const modular_int &other)
    {
        val = fast_mod(uint64_t(val) * other.val);
        return *this;
    }

    modular_int &operator/=(const modular_int &other)
    {
        return *this *= other.inv();
    }

    friend modular_int operator+(const modular_int &a, const modular_int &b) { return modular_int(a) += b; }
    friend modular_int operator-(const modular_int &a, const modular_int &b) { return modular_int(a) -= b; }
    friend modular_int operator*(const modular_int &a, const modular_int &b) { return modular_int(a) *= b; }
    friend modular_int operator/(const modular_int &a, const modular_int &b) { return modular_int(a) /= b; }

    modular_int &operator++()
    {
        val = val == MOD - 1 ? 0 : val + 1;
        return *this;
    }

    modular_int &operator--()
    {
        val = val == 0 ? MOD - 1 : val - 1;
        return *this;
    }

    modular_int operator++(int)
    {
        modular_int before = *this;
        ++*this;
        return before;
    }
    modular_int operator--(int)
    {
        modular_int before = *this;
        --*this;
        return before;
    }

    modular_int operator-() const
    {
        return val == 0 ? 0 : MOD - val;
    }

    friend bool operator==(const modular_int &a, const modular_int &b) { return a.val == b.val; }
    friend bool operator!=(const modular_int &a, const modular_int &b) { return a.val != b.val; }
    friend bool operator<(const modular_int &a, const modular_int &b) { return a.val < b.val; }
    friend bool operator>(const modular_int &a, const modular_int &b) { return a.val > b.val; }
    friend bool operator<=(const modular_int &a, const modular_int &b) { return a.val <= b.val; }
    friend bool operator>=(const modular_int &a, const modular_int &b) { return a.val >= b.val; }

    static const int SAVE_INV = int(1e6) + 5;
    static modular_int save_inv[SAVE_INV];

    static void prepare_inv()
    {
        // Ensures that MOD is prime, which is necessary for the inverse algorithm below.
        for (int64_t p = 2; p * p <= MOD; p += p % 2 + 1)
            assert(MOD % p != 0);

        save_inv[0] = 0;
        save_inv[1] = 1;

        for (int i = 2; i < SAVE_INV; i++)
            save_inv[i] = save_inv[MOD % i] * (MOD - MOD / i);
    }

    modular_int inv() const
    {
        if (save_inv[1] == 0)
            prepare_inv();

        if (val < SAVE_INV)
            return save_inv[val];

        modular_int product = 1;
        int v = val;

        do
        {
            product *= MOD - MOD / v;
            v = MOD % v;
        } while (v >= SAVE_INV);

        return product * save_inv[v];
    }

    modular_int pow(int64_t p) const
    {
        if (p < 0)
            return inv().pow(-p);

        modular_int a = *this, result = 1;

        while (p > 0)
        {
            if (p & 1)
                result *= a;

            p >>= 1;

            if (p > 0)
                a *= a;
        }

        return result;
    }

    friend ostream &operator<<(ostream &os, const modular_int &m)
    {
        return os << m.val;
    }
};
template <const int &MOD>
modular_int<MOD> modular_int<MOD>::save_inv[modular_int<MOD>::SAVE_INV];
const int MOD = 998244353;
using mint = modular_int<MOD>;
void __print(mint x) { cerr << x; }

#define inf (long long)1e18
#define endl "\n"
#define int int64_t
#define x first
#define y second
#define all(x) (x).begin(),(x).end() 
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
combinatorics<mint,2>c(1e6+1);
void solve(int tc)
{   
    vector<vector<mint>>pre(1e6+1,vector<mint>(100));
    for(int i=1;i<=1e6;i++)
    {
        for(int j=0;j<=min(i,(int)99);j++)
        {
            pre[i][j]=c.ncr(i,j);
            if(j) pre[i][j]+=pre[i][j-1];
        }
    }
    auto cc=[&](int n, int l, int r)->mint //ncl+..+ncr
    {
        assert(n<=1e6);
        assert(l<100);
        assert(r<100);
        if(l>r || l<0 || r<0) return 0;
        mint ret=pre[n][r];
        if(l) ret-=pre[n][l-1];
        return ret;
    };
    int n;
    cin>>n;
    int q;
    cin>>q;
    vector<int>f(61);
    for(int i=1;i<=n;i++)
    {
        int a;
        cin>>a;
        f[a]++;
    }
    dbg("here");
    auto dfs=[&](int i, int j, int x, mint &ans, bool st, mint &ways,auto &&dfs)->void
    {
        if(i<0) 
        {
            ans+=ways;
            return;
        }
        st=st|((x&(1LL<<i))!=0);
        int sm=0;
        for(int k=i-1;k>=0;k--) sm+=f[k];
        if(!st)
        {
            if(f[i])
                ans+=ways*(c.pw[f[i]]-1)*c.pw[sm];
            dfs(i-1,j,x,ans,st,ways,dfs);
            return;
        }
        j=min(i,j);
        if(j<0)
        {
            int sm=0;
            for(;i>=0;i--) sm+=f[i];
            ans+=ways*c.pw[sm];
            return;
        }
        if(j>=0 && ((x&(1LL<<j))==0)) j--;
        int cnt=0;
        while(j>=0 && ((x&(1LL<<j))!=0)) cnt++,j--;
        if(cnt>f[i]) return;

        // case 2 loose
        
        if(f[i])
            ans+=ways*(c.pw[f[i]]-cc(f[i],0,cnt))*c.pw[sm];

        // case 1 satisfy current path with i and stay tight;
        if(f[i])
            ways*=c.ncr(f[i],cnt);

        dfs(i-1,j,x,ans,st,ways,dfs);
        // j is previous patch end
        
    };
    while(q--)
    {
        int ty,x;
        cin>>ty>>x;
        if(ty==1)
        {
            f[x]++;
            n++;
        }
        else if(ty==2)
        {
            f[x]--;
            n--;
        }
        else
        {
            mint ans=0,ways=1;
            dfs(60,60,x,ans,0,ways,dfs);
            cout<<ans<<endl;
        }
    }
}   
int32_t main()      
{   
    #ifdef LOCAL1
        auto begin = std::chrono::high_resolution_clock::now();
    #endif
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int t=1;
    int tc=1;
    while (t--)
    {
        solve(tc),tc++;
    }
    #ifdef LOCAL1
        auto end = std::chrono::high_resolution_clock::now();
        cerr << setprecision(4) << fixed;
        cerr << "-> " << std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count() << " sec" << endl;
    #endif
    return 0;
}