#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#define dbg(x...) cerr << "[" << #x << "]=["; _print(x)
#else
#define dbg(x...) 
#endif

#define inf (long long)1e18
#define endl "\n"
#define int long long
#define x first
#define y second
#define all(x) (x).begin(),(x).end() 
class node_chan
{
public:
    int v = 0;

    inline void operator+=(node_chan &other)
    {
        v += other.v;
    }
    inline bool operator<(node_chan &other)
    {
        return v < other.v;
    }
};
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
void solve(int tc)
{   
    int n;
    cin>>n;
    int x;
    vector<int>odd;
    vector<int>even;
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        if(i%2) odd.push_back(x);
        else even.push_back(x);
    }
    fenwick_tree_chan<int> ds_odd(n+1);
    fenwick_tree_chan<int> ds_even(n+1);
    int inv=0;
    for(int i=0;i<odd.size();i++)
    {
        inv+=ds_odd.query(n)-ds_odd.query(odd[i]);
        ds_odd.modify(odd[i],1);
    }
    for(int i=0;i<even.size();i++)
    {
        inv+=ds_even.query(n)-ds_even.query(even[i]);
        ds_even.modify(even[i],1);
    }
    sort(all(odd));
    sort(all(even));
    vector<int>ar(n);
    int j=0,k=0;
    for(int i=1;i<=n;i++)
    {
        if(i%2) ar[i-1]=odd[j++];
        else ar[i-1]=even[k++];
    }
    if(inv%2)
    {
        swap(ar.back(),ar[n-3]);
    }
    for(auto i:ar) cout<<i<<" ";
    cout<<endl;
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