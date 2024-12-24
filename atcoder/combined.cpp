#include <bits/stdc++.h>

#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>


#ifdef _MSC_VER
#include <intrin.h>
#endif

#if __cplusplus >= 202002L
#include <bit>
#endif

namespace atcoder {

namespace internal {

#if __cplusplus >= 202002L

using std::bit_ceil;

#else

unsigned int bit_ceil(unsigned int n) {
    unsigned int x = 1;
    while (x < (unsigned int)(n)) x *= 2;
    return x;
}

#endif

int countr_zero(unsigned int n) {
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}

constexpr int countr_zero_constexpr(unsigned int n) {
    int x = 0;
    while (!(n & (1 << x))) x++;
    return x;
}

}  // namespace internal

}  // namespace atcoder


namespace atcoder {

#if __cplusplus >= 201703L

template <class S, auto op, auto e> struct segtree {
    static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                  "op must work as S(S, S)");
    static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                  "e must work as S()");

#else

template <class S, S (*op)(S, S), S (*e)()> struct segtree {

#endif

  public:
    segtree() : segtree(0) {}
    explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
    explicit segtree(const std::vector<S>& v) : _n(int(v.size())) {
        size = (int)internal::bit_ceil((unsigned int)(_n));
        log = internal::countr_zero((unsigned int)size);
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) const {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    S prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() const { return d[1]; }

    template <bool (*f)(S)> int max_right(int l) const {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n) return _n;
        l += size;
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*f)(S)> int min_left(int r) const {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0) return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};

}  // namespace atcoder

using namespace std;
using namespace atcoder;
#define int long long
#define inf (long long)1e18
#define ll long long
#define MOD 1000000007
#define MOD1 998244353
#define endl "\n"
#define x first
#define y second
#define sz size()
#ifdef LOCAL
#include "debug.hpp"
#define dbg(x...) cerr << "[" << #x << "]=["; _print(x)
#define fastio 
#else
#define dbg(x...) 
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#endif
#define all(x) (x).begin(), (x).end() 
#define NL cout<<endl;
#define f(i, a, n) for (int i=a; i<n; i++)
#define fr(i, n) for (int i=0; i<n; i++)
#define fr1(i, n) for(int i=1;i<=n;i++)
#define frr(i,n) for(int i=n-1;i>=0;i--)
#define each(x, a) for(auto &x : a)
#define gcd(x, y) __gcd(x, y)
#define lcm(x, y) ((x*y) / gcd(x, y))
#define cl(a, b) ((a+b - 1)) /( b) //?ceill
#define unq(v) {sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end());}
int power(int a, int b){if(b==0)return 1;int res=power(a,b/2);if(b%2)return res*res*a;else return res*res;}int POWM(int a,int b,int m=MOD){a%=m;int res=1;while(b>0){if(b&1)res=res*a%m;a=a*a%m;b>>=1;}return res;}int modinv(int a,int m=MOD){return POWM(a,m-2,m);}
#define sort_(a) sort(a.begin(),a.end())
#define rev(a) reverse(a.begin(),a.end())
#define ld long double
#define pb push_back
#define eb emplace_back
#define em emplace
struct custom_hash{static uint64_t splitmix64(uint64_t x){x+=0x9e3779b97f4a7c15;x=(x^(x>>30))*0xbf58476d1ce4e5b9;x=(x^(x>>27))*0x94d049bb133111eb;return x^(x>>31);}size_t operator()(uint64_t x)const{static const uint64_t FIXED_RANDOM=chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x+FIXED_RANDOM);}};
typedef vector<ll>vi;typedef pair<ll,ll>pii;typedef vector<pii>vii;typedef vector<vi>vvi;typedef deque<int>dq;typedef map<int,int>mi;typedef map<pii,int>mii;typedef queue<int>qi;typedef queue<pii>qii;typedef vvi grf;typedef set<int>si;typedef priority_queue<int, vi> pq; typedef priority_queue<int, vi, greater<int>> mpq;typedef unordered_map<int, int,custom_hash> unmap;typedef unordered_set<int, custom_hash> unset;
#define sum(a) accumulate(all(a),0LL)
#define maxx(a) (*max_element(all(a)))
#define minn(a) (*min_element(all(a)))
#define no {cout<<"NO"<<endl; return;}
#define yes {cout<<"YES"<<endl; return;}
#define rpt return pt
void in(vi &a,int n){a.resize(n);fr(i,n)cin>>a[i];}void in(grf &g, int nodes,int edges=-1){if(edges==-1)edges=nodes-1; g.clear();g.resize(nodes);int a,b;fr(i,edges){cin>>a>>b,--a,--b,g[a].pb(b),g[b].pb(a);}}
void pt(vi &v){each(i,v)cout<<i<<" ";NL}void pt(int x){cout<<x;NL}void pt(string s){cout<<s;NL}void pt(char &c){cout<<c;NL}void pt(pii p){cout<<p.x<<" "<<p.y;NL}void pt(mi &mp){each(i,mp)cout<<i.x<<" "<<i.y;NL}void pt(unmap &mp){each(i,mp)cout<<i.x<<" "<<i.y;NL}void pt(vvi &v){each(i,v)pt(i);}void pt(vii &v){each(i,v)cout<<i.x<<" "<<i.y<<endl;}void pt(double &d){cout<<d;NL}void pt(float &f){cout<<f;NL}template<typename T>void pt(set<T>&s){each(i,s)cout<<i<<" ";NL}
int op(int a, int b) {return max(a,b);}
int e() {return 0ll;}
void solve(int tc)
{   
    int n;
    cin>>n;
    vi ar(n);
    in(ar,n);
    segtree<int,op,e>st(n+1);
    vi pf(n,0);
    pf[0]=0;
    auto imax=[&](int a, int b)
    {
        return ar[a]>=ar[b]?a:b;
    };
    f(i,1,n)
    {
        pf[i]=imax(pf[i-1],i);
    }
    vi ans(n,-1);
    function<int(int)> solve=[&](int idx)->int
    {
        if(ans[idx]!=-1)
        {
            return ans[idx];
        }
        int ans1=ar[pf[idx]];
        if(ans1!=ar[idx])
        {
            solve(pf[idx]);
            int ans2=ans[pf[idx]];
            ans[idx]=max(ans1,ans2);
        }
        else
        {
            ans[idx]=max(ar[idx],st.prod(0,ar[idx]));
        }
        int prev=st.get(ar[idx]);
        st.set(ar[idx],max(prev,ans[idx]));
        return ans[idx];
    };
    frr(i,n) ans[i]=solve(i);
    pt(ans);
}   
int32_t main()      
{   
    fastio
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int t;
    cin>>t;
    // t=1;
    int tc=1;
    while (t--)
    {
        solve(tc),tc++;
    }
    return 0;
}  