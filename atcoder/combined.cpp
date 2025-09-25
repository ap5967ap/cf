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

template <class S,
          auto op,
          auto e,
          class F,
          auto mapping,
          auto composition,
          auto id>
struct lazy_segtree {
    static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                  "op must work as S(S, S)");
    static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                  "e must work as S()");
    static_assert(
        std::is_convertible_v<decltype(mapping), std::function<S(F, S)>>,
        "mapping must work as F(F, S)");
    static_assert(
        std::is_convertible_v<decltype(composition), std::function<F(F, F)>>,
        "compostiion must work as F(F, F)");
    static_assert(std::is_convertible_v<decltype(id), std::function<F()>>,
                  "id must work as F()");

#else

template <class S,
          S (*op)(S, S),
          S (*e)(),
          class F,
          S (*mapping)(F, S),
          F (*composition)(F, F),
          F (*id)()>
struct lazy_segtree {

#endif

  public:
    lazy_segtree() : lazy_segtree(0) {}
    explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
    explicit lazy_segtree(const std::vector<S>& v) : _n(int(v.size())) {
        size = (int)internal::bit_ceil((unsigned int)(_n));
        log = internal::countr_zero((unsigned int)size);
        d = std::vector<S>(2 * size, e());
        lz = std::vector<F>(size, id());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return e();

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    void apply(int p, F f) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }

        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <bool (*g)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return g(x); });
    }
    template <class G> int max_right(int l, G g) {
        assert(0 <= l && l <= _n);
        assert(g(e()));
        if (l == _n) return _n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) {
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

    template <bool (*g)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return g(x); });
    }
    template <class G> int min_left(int r, G g) {
        assert(0 <= r && r <= _n);
        assert(g(e()));
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm))) {
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
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};

}  // namespace atcoder

using namespace std;
using namespace atcoder;

#ifdef LOCAL
#include "debug.hpp"
#define dbg(x...) cerr << "[" << #x << "]=["; _print(x)
#else
#define dbg(x...) 
#endif

#define inf (long long)1e18
#define endl "\n"
#define x first
#define y second
#define all(x) (x).begin(),(x).end() 
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

struct S {
    mint sum;
    int size;
};

S op(S a, S b) {
    return {a.sum + b.sum, a.size + b.size};
}

S e() {
    return {mint(0), 0};
}

struct F {
    mint x;
    bool is_set;
};

S mapping(F f, S s) {
    if (!f.is_set) return s;
    return {f.x * s.size, s.size};
}

F composition(F f, F g) {
    if (f.is_set) return f;
    return g;
}

F id() {
    return {mint(0), false};
}


void solve(int tc)
{   
    int n,m;
    cin>>n>>m;
    vector<S>ar(n);
    for(int i=0;i<n;i++)
    {
        int x;
        cin>>x;
        ar[i]={x,1};
    }
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(ar);
    for(int i=0;i<m;i++)
    {
        int l,r;
        cin>>l>>r;
        mint rng=r-l+1;
        l--,r--;
        r++;
        mint v=seg.prod(l,r).sum;
        v=v/rng;
        seg.apply(l,r,{v,true});
    }
    for(int i=0;i<n;i++) 
    {
        cout<<seg.prod(i,i+1).sum<<" ";
    }
    cout<<endl;

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