#include<bits/stdc++.h>
#include<cassert>
using namespace std;

// === dsu.cpp ===
class dsu_chan
{
public:
    int n;
    vector<int> par;
    vector<int> siz;
    dsu_chan(int n) : n(n), par(n), siz(n, 1)
    {
        iota(par.begin(), par.end(), 0);
    };
    int get(int x)
    {
        return (par[x] == x ? x : par[x] = get(par[x]));
    }
    void unite(int x, int y)
    {
        x = get(x), y = get(y);
        if (x == y)
            return;
        if (siz[x] > siz[y]) swap(x, y);
        par[x] = y, siz[y] += siz[x];
    }
    vector<vector<int>> group()
    {
        vector<vector<int>> g(n);
        for (int u = 0; u < n; u++)
            g[get(u)].push_back(u);
        return g;
    }
};

// === fenwick.cpp ===
class fenwick_tree_chan
{
public:
    vector<int> fenw;
    int n;
    int pw;

    fenwick_tree_chan() : n(0) {}

    fenwick_tree_chan(int n) : n(n)
    {
        fenw.resize(n);
        pw = (n == 0 ? 0 : 1ULL << (63 - __builtin_clzll(unsigned(n))));
    }
    // a[x] += v;
    void modify(int x, int v)
    {
        assert(0 <= x && x < n);
        while (x < n)
        {
            fenw[x] += v;
            x |= x + 1;
        }
    }
    // sum of prefix [0, .. x]
    int query(int x)
    {
        ++x;
        assert(0 <= x && x <= n);
        int v{};
        while (x > 0)
        {
            v += fenw[x - 1];
            x &= x - 1;
        }
        return v;
    }
    // Returns the length of the longest prefix (0 indexed) with sum <= c
    int max_prefix(int c)
    {
        int v{};
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

// === fenwick_range.cpp ===
fenwick_tree_chan ds1(n), ds2(n);
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

// === random.cpp ===
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// === helpers.cpp ===
#define unq(v) {sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end());}

// === sieve.cpp ===
const int MAX=2e5+1;
bool v[MAX]={false};
vector<int>primes(1,2);
int len,sp[MAX];
void Sieve()
{
    for(int i=2;i<MAX;i+=2)sp[i]=2;
    sp[1]=1;
    for(int i=3;i<MAX;i+=2)
    {
        if(!v[i])
        {
            primes.push_back(i);
            sp[i]=i;
            for(int j=i*i;j<MAX;j+=i)
            {  
                if(!v[j])
                {
                    v[j]=true;
                    sp[j]=i;
                }
            }
        }
    }
}
vector<pair<int,int>> factorize(int k)
{
    vector<pair<int,int>> pf;
    while (k > 1)
    {
        int p = sp[k];
        int cnt = 0;
        while (k%p==0) k/=p,cnt++;
        pf.emplace_back(p, cnt);
    }
    return pf;
}
vector<int>fac[MAX];
void facSieve()
{
    for(int i=1;i<MAX;i++){
        for(int j=i;j<MAX;j+=i){
            fac[j].push_back(i);
        }
    }
}
//phi[n] = n*(1-1/pi)
vector<int> getDivisors(int x) {
//all divisors in O(log n + #divisors(n))
    auto pf = factorize(x);
    vector<int> divisors = {1};
    for (auto [p, cnt] : pf) {
        int sz = divisors.size();
        long long pw = 1;
        for (int i = 1; i <= cnt; i++) {
            pw *= p;
            for (int j = 0; j < sz; j++) {
                divisors.push_back(divisors[j] * pw);
            }
        }
    }
    sort(divisors.begin(), divisors.end());
    return divisors;
}
// === ordered_set.cpp ===
#include<bits/extc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename K, typename V, typename Comp = std::less<K>>
using ordered_map = __gnu_pbds::tree<
    K, V, Comp,
    __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update
>;
template<class T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename Comp = std::less<K>>
using ordered_set = ordered_map<K, __gnu_pbds::null_type, Comp>;
// auto iterator = ordered_set().find_by_order(idx); // 0-indexed
// int num_strictly_smaller = ordered_set().order_of_key(key);
// deletion might not work in ordered_multiset

// === simple_segtree.cpp ===
template <class S, auto op, auto e>
struct simple_segtree
{
    int _n;
    int size;
    std::vector<S> d;
    simple_segtree() : simple_segtree(0) {}
    explicit simple_segtree(int n) { init(n); }
    explicit simple_segtree(const std::vector<S> &v)
    {
        _n = (int)v.size();
        size = 1;
        while (size < _n) size <<= 1;
        d.assign(2 * size, e());
        for (int i = 0; i < _n; ++i) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; --i) d[i] = op(d[2 * i], d[2 * i + 1]);
    }
    void init(int n)
    {
        _n = n;
        size = 1;
        while (size < _n) size <<= 1;
        d.assign(2 * size, e());
    }
    void set(int p, S x)
    {
        assert(0 <= p && p < _n);
        int pos = size + p;
        d[pos] = x;
        pos >>= 1;
        while (pos >= 1)
        {
            d[pos] = op(d[2 * pos], d[2 * pos + 1]);
            pos >>= 1;
        }
    }
    S get(int p)
    {
        assert(0 <= p && p < _n);
        return d[size + p];
    }
    S prod(int l, int r)
    {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return e();
        l += size;
        r += size;
        S sml = e(), smr = e();
        while (l < r)
        {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }
};

// === string_hash.cpp ===
struct Hash {
    using ll = long long;
    const ll mod1 = 1000000007, mod2 = 1000000009;
    const ll base1 = 91138233, base2 = 97266353;
    int n;
    vector<ll> h1, h2, p1, p2;
    Hash(string s) {
        n = s.size();
        h1.resize(n + 1, 0);
        h2.resize(n + 1, 0);
        p1.resize(n + 1, 1);
        p2.resize(n + 1, 1);
        for (int i = 0; i < n; i++) {
            h1[i + 1] = (h1[i] * base1 + s[i]) % mod1;
            h2[i + 1] = (h2[i] * base2 + s[i]) % mod2;
            p1[i + 1] = (p1[i] * base1) % mod1;
            p2[i + 1] = (p2[i] * base2) % mod2;
        }
    }
    pair<ll,ll> get(int l, int r) {
        ll x1 = (h1[r + 1] - h1[l] * p1[r - l + 1] % mod1 + mod1) % mod1;
        ll x2 = (h2[r + 1] - h2[l] * p2[r - l + 1] % mod2 + mod2) % mod2;
        return {x1, x2};
    }
    // H.get(l, r) == RH.get(n - 1 - r, n - 1 - l); for palindrome
};

// matrix expo } } 
using Mat = vector<vector<int>>;

Mat mul(const Mat& A, const Mat& B) {
    int n=A.size(), p=B.size(), m=B[0].size();
    Mat C(n, vector<int>(m));
    for(int i=0;i<n;i++)
        for(int k=0;k<p;k++)
            for(int j=0;j<m;j++)
                C[i][j]=(C[i][j]+1LL*A[i][k]*B[k][j])%mod;
    return C;
}
Mat mpow(Mat A, long long k) {
    int n=A.size();
    Mat R(n, vector<int>(n));
    for(int i=0;i<n;i++) R[i][i]=1;
    while(k) {
        if(k&1) R=mul(R,A);
        A=mul(A,A);
        k>>=1;
    }
    return R;
}

int binpow(int a, int b, long long m){ 
    a %= m; 
    int res = 1; 
    while (b > 0){ if (b & 1) res = res * a % m; a = a * a % m; b >>= 1; } 
    return res%m; 
}

const int MAX = 1e6 + 5;
int fact[MAX], invFact[MAX];
const int mod=1e9+7;
void precompute() {
    fact[0] = invFact[0] = 1;
    for (int i = 1; i < MAX; i++) fact[i] = (1LL * fact[i- 1]* i) % mod;
    invFact[MAX- 1] = binpow(fact[MAX- 1], mod- 2, mod);
    for (int i = MAX- 2; i >= 1; i--) invFact[i] = (1LL *invFact[i + 1] * (i + 1)) % mod;
}
int nCr(int n, int r) { 
    if (r < 0 || r > n) return 0;
    return 1LL * fact[n] * invFact[r] % mod * invFact[n- r] % mod; 
}
// a1+a2+...ar=n
// C(n+r-1,n)

template <class S,
          auto op,
          auto e,
          class F,
          auto mapping,
          auto composition,
          auto id>
struct lazy_segtree
{
public:
    unsigned int bit_ceil(unsigned int n)
    {
        unsigned int x = 1;
        while (x < (unsigned int)(n))
            x *= 2;
        return x;
    }
    int countr_zero(unsigned int n)
    {
        return __builtin_ctz(n);
    }
    lazy_segtree() : lazy_segtree(0) {}
    explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
    explicit lazy_segtree(const std::vector<S> &v) : _n((int)(v.size()))
    {
        size = (int)bit_ceil((unsigned int)(_n));
        log = countr_zero((unsigned int)size);
        d = std::vector<S>(2 * size, e());
        lz = std::vector<F>(size, id());
        for (int i = 0; i < _n; i++)
            d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--)
        {
            update(i);
        }
    }

    void set(int p, S x)
    {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--)
            push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++)
            update(p >> i);
    }

    S get(int p)
    {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--)
            push(p >> i);
        return d[p];
    }

    S prod(int l, int r)
    {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r)
            return e();

        l += size;
        r += size;

        for (int i = log; i >= 1; i--)
        {
            if (((l >> i) << i) != l)
                push(l >> i);
            if (((r >> i) << i) != r)
                push((r - 1) >> i);
        }

        S sml = e(), smr = e();
        while (l < r)
        {
            if (l & 1)
                sml = op(sml, d[l++]);
            if (r & 1)
                smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    void apply(int p, F f)
    {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--)
            push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++)
            update(p >> i);
    }
    void apply(int l, int r, F f)
    {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r)
            return;

        l += size;
        r += size;

        for (int i = log; i >= 1; i--)
        {
            if (((l >> i) << i) != l)
                push(l >> i);
            if (((r >> i) << i) != r)
                push((r - 1) >> i);
        }

        {
            int l2 = l, r2 = r;
            while (l < r)
            {
                if (l & 1)
                    all_apply(l++, f);
                if (r & 1)
                    all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }

        for (int i = 1; i <= log; i++)
        {
            if (((l >> i) << i) != l)
                update(l >> i);
            if (((r >> i) << i) != r)
                update((r - 1) >> i);
        }
    }

    template <bool (*g)(S)>
    int max_right(int l)
    {
        return max_right(l, [](S x)
                         { return g(x); });
    }
    template <class G>
    int max_right(int l, G g)
    {
        assert(0 <= l && l <= _n);
        assert(g(e()));
        if (l == _n)
            return _n;
        l += size;
        for (int i = log; i >= 1; i--)
            push(l >> i);
        S sm = e();
        do
        {
            while (l % 2 == 0)
                l >>= 1;
            if (!g(op(sm, d[l])))
            {
                while (l < size)
                {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l])))
                    {
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

    template <bool (*g)(S)>
    int min_left(int r)
    {
        return min_left(r, [](S x)
                        { return g(x); });
    }
    template <class G>
    int min_left(int r, G g)
    {
        assert(0 <= r && r <= _n);
        assert(g(e()));
        if (r == 0)
            return 0;
        r += size;
        for (int i = log; i >= 1; i--)
            push((r - 1) >> i);
        S sm = e();
        do
        {
            r--;
            while (r > 1 && (r % 2))
                r >>= 1;
            if (!g(op(d[r], sm)))
            {
                while (r < size)
                {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm)))
                    {
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
    std::vector<F> lz;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f)
    {
        d[k] = mapping(f, d[k]);
        if (k < size)
            lz[k] = composition(f, lz[k]);
    }
    void push(int k)
    {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};
// === cut/bridge ===
int n,t; vector<vector<int>> g; vector<bool> vis; vector<int> tin,low;
void cut(int v,int p=-1){
    vis[v]=1; tin[v]=low[v]=t++; int ch=0;
    for(int u:g[v]){
        if(u==p) continue;
        if(vis[u]) low[v]=min(low[v],tin[u]);
        else{
            cut(u,v); low[v]=min(low[v],low[u]);
            if(low[u]>=tin[v]&&p!=-1) /* CUT(v) */;
            ch++;
        }
    }
    if(p==-1&&ch>1) /* CUT(v) */;
}
void bridge(int v,int p=-1){
    vis[v]=1; tin[v]=low[v]=t++; bool skip=0;
    for(int u:g[v]){
        if(u==p&&!skip){skip=1;continue;}
        if(vis[u]) low[v]=min(low[v],tin[u]);
        else{
            bridge(u,v); low[v]=min(low[v],low[u]);
            if(low[u]>tin[v]) /* BRIDGE(v,u) */;
        }
    }
}
void init(int n){
    t=0; g.resize(n); vis.assign(n,0);
    tin.assign(n,-1); low.assign(n,-1);
}

class Trie 
{
public:
    static constexpr int ALPHA = 26;
    vector<array<int,ALPHA>> nxt;
    vector<int> cnt, pref;
    int nodes;

    Trie(int mx = 1e6+1) 
    {
        nodes = 0;
        nxt.reserve(mx);
        cnt.reserve(mx);
        pref.reserve(mx);
        newNode(); // create root
    }

    int newNode() 
    {
        nxt.push_back({});
        cnt.push_back(0);
        pref.push_back(0);
        return nodes++;
    }

    // insert s with frequency f (use f=-1 to remove)
    void insert(const string &s, int f = 1) 
    {
        int u = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (!nxt[u][c]) {
                nxt[u][c] = newNode();
            }
            u = nxt[u][c];
            pref[u] += f;
        }
        cnt[u] += f;
    }

    // exact string count
    int count(const string &s) const 
    {
        int u = 0;
        for (char ch : s) 
        {
            int c = ch - 'a';
            if (!nxt[u][c] || pref[nxt[u][c]] <= 0) 
                return 0;
            u = nxt[u][c];
        }
        return cnt[u];
    }

    // count of strings with prefix s
    int prefCount(const string &s) const 
    {
        int u = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (!nxt[u][c] || pref[nxt[u][c]] <= 0)
                return 0;
            u = nxt[u][c];
        }
        return pref[u];
    }

    // sum of prefCounts along path matching s
    int query(const string &s) const 
    {
        // depends on use case
    }

    // remove s (decrement counts)
    void remove(const string &s) 
    {
        insert(s, -1);
    }
};

class BitTrie 
{
public:
    static constexpr int BITS = 31;       // for 32-bit ints use 31 down to 0
    vector<array<int,2>> nxt;
    vector<int> cnt;                      // count of numbers ending exactly at this node
    vector<int> pref;                     // count of numbers passing through this node
    int nodes = 0;

    BitTrie(int maxNodes = 1e6+1) 
    {
        nxt.reserve(maxNodes);
        cnt.reserve(maxNodes);
        pref.reserve(maxNodes);
        newNode();
    }

    int newNode() 
    {
        nxt.push_back({0,0});
        cnt.push_back(0);
        pref.push_back(0);
        return nodes++;
    }

    // insert x (f=+1) or remove x (f=-1)
    void insert(int x, int f = 1) 
    {
        int u = 0;
        for (int b = BITS; b >= 0; --b) 
        {
            int bit = (x >> b) & 1;
            if (!nxt[u][bit])
                nxt[u][bit] = newNode();
            u = nxt[u][bit];
            pref[u] += f;
        }
        cnt[u] += f;
    }

    void remove(int x) { insert(x, -1); }

    // exact count of x
    int count(int x) const 
    {
        int u = 0;
        for (int b = BITS; b >= 0; --b) 
        {
            int bit = (x >> b) & 1;
            int v = nxt[u][bit];
            if (!v || pref[v] <= 0) return 0;
            u = v;
        }
        return cnt[u];
    }

    // maximize x^y over all y in the trie
    int maxXor(int x) const 
    {
        int u = 0;
        int ans = 0;
        for (int b = BITS; b >= 0; --b) 
        {
            int bit = (x >> b) & 1;
            int want = bit ^ 1;
            if (nxt[u][want] && pref[nxt[u][want]] > 0) 
            {
                ans |= (1 << b);
                u = nxt[u][want];
            } else 
            {
                u = nxt[u][bit];
            }
        }
        return ans;
    }

    // count of elements ≤ x
    int leq(int x) const 
    {
        int u = 0, res = 0;
        for (int b = BITS; b >= 0; --b) 
        {
            int bit = (x >> b) & 1;
            if (bit == 1) 
            {
                if(nxt[u][0])
                    res += pref[nxt[u][0]];
                u = nxt[u][1];
            } 
            else 
            {
                u = nxt[u][0];
            }
        }
        if(u) 
            res += cnt[u];
        return res;
    }
};


int extended_gcd(int a, int b, int &x, int &y) 
{// ax + by = gcd(a, b)
    if (b == 0) { x = 1; y = 0; return a; }
    int x1, y1;
    int g = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

struct binary_lifter_chan
{//up[u][i] -> stores 2^ith ancestor of u
    int n, L, timer;
    vector<int> dep, tin, tout;
    vector<vector<int>> up;
    binary_lifter_chan(int n, int r, const vector<vector<int>> &adj) : 
    n(n), L(ceil(log2(n)) + 1), timer(0), dep(n), tin(n), tout(n), up(n, vector<int> (L, r))
    {
        timer = 0;
        dep[r] = 0;
        dfs(r, r, adj);
    }
    void dfs(int u, int p, const vector<vector<int>> &adj)
    {
        tin[u] = ++ timer;
        up[u][0] = p;
 
        for(int i = 1; i < L; ++i)
            up[u][i] = up[up[u][i - 1]][i - 1];
 
        for(auto v : adj[u])
            if (v != p)
                dep[v] = dep[u] + 1, dfs(v, u, adj);

        tout[u] = ++ timer;
    }
    int get_kth(int v, int k)
    {
        if(k != 0)
            for(int i = L - 1; i >= 0 and v > 0; i --)
                if((1 << i) <= k)
                    k -= (1 << i), v = up[v][i];
        return v;
    }
    bool is_anc(int anc, int v)
    {
        return tin[anc] <= tin[v] and tout[v] <= tout[anc];
    }
    int lca(int u, int v)
    {
        if (is_anc(u, v))
            return u;
        if (is_anc(v, u))
            return v;
        for (int i = L - 1; i >= 0; --i) 
            if (!is_anc(up[u][i], v))
                u = up[u][i];
        return up[u][0];
    }
};


/*
SCC
Run DFS on G (store finish time)
Reverse all edges
Process vertices in decreasing finish
each DFS gives one SCC
*/

struct sparse_table
{
    vector<vector<int>> st;
    vector<int> log;
    int func(int a, int b)
    {return min(a, b);}
    sparse_table(vector<int> &arr)
    {
        int n = arr.size();
        log.resize(n + 1);
        for (int i = 2; i <= n; ++i)
            log[i] = log[i / 2] + 1;
        int k = log[n] + 1;
        st.assign(n, vector<int>(k));
        for (int i = 0; i < n; ++i)
            st[i][0] = arr[i];
        for (int j = 1; (1 << j) <= n; ++j)
            for (int i = 0; i + (1 << j) - 1 < n; ++i)
              st[i][j] = func(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
    int query(int L, int R) 
    {// 0 based indexing [l,r]
        int j = log[R - L + 1];
        return func(st[L][j], st[R - (1 << j) + 1][j]);
    }
};


struct xor_basis{
    static constexpr int MAX_BITS = 30;
    int basis[MAX_BITS];
    int n; 
 
    xor_basis() : n(0) {}; 
    
    bool add(int num){
        if(n == MAX_BITS) return false; 
        for(int i = 0; i < n; ++i) num = min(num, num ^ basis[i]);
        if(num == 0) return false; 
        for(int i = 0; i < n; ++i) basis[i] = min(basis[i], basis[i] ^ num); 
        basis[n++] = num; 
        for(int i = n - 1; i > 0 && basis[i] < basis[i - 1]; i--) swap(basis[i], basis[i - 1]); 
        return true;
    }
 
    //index of num if we sort all numbers possible to make
    int order_of_key(int num){
        int res = 0;
        for(int i = n - 1; i >= 0; i--){
            int d = min(num, num ^ basis[i]); 
            if(num > d) res += (1 << i), num = d; 
        }
        return res; 
    }
 
    //number at idx if we sort all numbers possible to make
    int find_by_order(int idx){
        int res = 0; 
        for(int i = n - 1; i>= 0;i--){
            if(idx >= (1 << i)){
                idx -= (1 << i); 
                res = max(res, res ^ basis[i]); 
            }
        }
        return res;
    } 
    int min_xor(int start = 0){
        for(int i = 0; i < n; ++i) start = min(start, start ^ basis[i]); 
        return start; 
    }
    int max_xor(int start = 0){
        for(int i = 0; i < n; ++i) start = max(start, start ^ basis[i]); 
        return start; 
    }
    bool contains(int num) { return min_xor(num) == 0; }
    int size() { return n;}
    // let sz be basis size
    // distinct xor values = 2^sz
    // Every representable XOR appears exactly 2^(array.size() - sz) times
    // merge two basis for each vector v in B2: B1.add(v) 
};

void segmented_sieve()
{
    int l,r;
    cin>>l>>r;
    int lim = sqrt(r)+1;
    vector<int> base_primes;
    vector<bool> is_prime(lim+1,1);
    for(int i=2;i*i<=r;i++){
        if(!is_prime[i]) continue; 
        for(int j = i*i;j<=lim;j+=i) {
            is_prime[j] = false;
        }
    }
    for(int i = 2;i*i<=r;i++) if(is_prime[i]) base_primes.push_back(i);
    vector<int> is_prime_seg(r-l+1,1);
    for(int p : base_primes){
        int st = ((l+p-1)/p) * p;
        for(int j = st;j<=r;j+=p) is_prime_seg[j-l] = p;
    }
    if(l==1) is_prime_seg[0] = false;
    // is_prime_seg[i] = true ==> l+i is prime
}           

ios_base::sync_with_stdio(false);cin.tie(NULL);

S(n) = sum of digits of number n
S(n) % 9 = n%9

If Ai != Aj, then swapping them changes the parity of number of inversions

Given a connected graph/tree where you can perform an operation on any edge (u, v) that flips/modifies the state of both endpoints u and v. the parity of the total number of modified nodes is always invariant

Substring Flip of Fixed Size x - For each residue i mod x, XOR difference is invariant.
A length-x flip toggles exactly one position in every residue class.
Therefore all residue-class XORs are toggled by the same bit.
To check s -> p:
XOR_s[i] ^ XOR_p[i] must be the same for every i = 0..x-1.

Sub-string reversal with odd length - elements at odd index remain at odd, and elements at even remain at even

Sub-string reversal with s[l] == s[r] - the boundary transitions (00/01/10/11) do not change.

substring reversal of size odd size k - inversion parity toggles
substring reversal of size even size k - inversion parity doesn't change

toggle s[i] and s[i+1] - let d[i] = s[i] ^ s[i-1]. so the operation toggles d[i] and d[i+2]

look at prefix sum, prefix xor, difference array (a[i+1]-a[i]), difference xor(a[i+1]^a[i]), inversion, no. of transitions, elements at odd index and even index

look at pair(a[i], a[n-i+1]) - swapping a prefix of length k with suffix of length k.

look at no. of s[i] == s[i+1]