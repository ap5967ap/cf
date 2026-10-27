#include <bits/stdc++.h>
#include <cassert>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#define dbg(x...) cerr << "[" << #x << "]=["; _print(x)
#else
#define dbg(x...) 
#endif

#define inf (long long)1e18
#define endl "\n"
#define int int64_t
#define x first
#define y second
#define all(x) (x).begin(),(x).end() 
#define ii <int,int>
#define pii pair ii
#define pb push_back
#define vi vector<int>
#define vvi vector<vi>
#define vii vector<pii>

template <typename T>
class fenwick_tree_chan
{
public:
    vector<T> fenw;
    int n;
    int pw;

    fenwick_tree_chan() : n(0) {}
    fenwick_tree_chan(int n) : n(n)
    {
        fenw.resize(n);
        pw = (n == 0 ? 0 : 1ULL << (63 - __builtin_clzll(unsigned(n))));
    }

    // a[x] += v;
    void modify(int x, T v)
    {
        assert(0 <= x && x < n);
        while (x < n)
        {
            fenw[x] += v;
            x |= x + 1;
        }
    }

    /// sum of prefix [0, .. x] 
    T query(int x)
    {
        ++ x;
        assert(0 <= x && x <= n);
        T v{};
        while (x > 0)
        {
            v += fenw[x - 1];
            x &= x - 1;
        }
        return v;
    }

    T query(int l, int r)
    {
        T res = query(r);
        if(l) res -= query(l - 1);
        return res;
    }

    // Returns the length of the longest prefix (0 indexed) with sum <= c
    int max_prefix(T c)
    {
        T v{};
        int at = 0;
        for (int len = pw; len > 0; len >>= 1)
        {
            if (at + len <= n)
            {
                auto nv = v;
                nv += fenw[at + len - 1];
                if (!(c < nv))
                {
                    v = nv;
                    at += len;
                }
            }
        }
        assert(0 <= at && at <= n);
        return at;
    }
};


struct range_fenwick_chan
{
    int n;
    fenwick_tree_chan<int> ds1, ds2;
    range_fenwick_chan(int n) : n(n), ds1(n), ds2(n) {}
    void range_add(int l, int r, long long val) 
    {
        ds1.modify(l, val);
        if (r + 1 < n) ds1.modify(r + 1, -val);
        ds2.modify(l, val * l);
        if (r + 1 < n) ds2.modify(r + 1, -val * (r + 1));
    }
    long long prefix_sum(int x) {
        if (x < 0) return 0;
        return (x + 1) * ds1.query(x) - ds2.query(x);
    }
    long long range_sum(int l, int r) {
        return prefix_sum(r) - prefix_sum(l - 1);
    }
};

void solve(int tc)
{   
    
}   
int32_t main()      
{   
    #ifdef LOCAL1
        auto begin = std::chrono::high_resolution_clock::now();
    #endif
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int t=1;
    cin>>t;
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