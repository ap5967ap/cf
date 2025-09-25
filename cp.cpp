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
/*
    !index is 0 based [l,r)

    S - segment tree node
    op(left, right) - monoid merge of two S values 
    e() - identity element for op
    F - lazy tag type
    mapping - apply a tag f to a node value s
    composition - combine two tags (f applied after g)
    id - neutral tag (no-op)

    void set(int p, S x) - ar[p] = x
    S get(int p) - return ar[p]

    S prod(int l, int r) - Combine values in [l, r) via op.
    S all_prod() == prod for whole array

    void apply(int p, F f) - Apply tag f only to index p.
    void apply(int l, int r, F f) - Apply tag f to every index in [l, r).

    int max_right(int l, G g) - max r s.t g(l...r-1) is true and g(l...r) is false; true for e()
    int min_left(int r, G g) - min l s.t g(l...r-1) is true and g(l-1....r-1) is false; true for e()



    struct S { int sum, size; };
    S op(S left, S right) { return {left.sum + right.sum, left.size + right.size}; }
    S e() { return {0, 0}; }
    struct F { int x; bool is_set; }; // lazy tag type
    S mapping(F f, S s)  // apply tag f to segment s
    {
        if (!f.is_set) return s;
        return {f.x * s.size, s.size};
    }
    
    F composition(F f, F g) { // Compose two tags: new f after old g
        if (f.is_set) return f;
        return g;
    }
    F id() { return {0, false}; }

    * constructor - expects vector<S> 

*/

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