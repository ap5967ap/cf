template <class S, auto op, auto e, class F, auto mapping>
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
        for (int i = size - 1; i >= 1; --i) d[i] = op(d[2*i], d[2*i+1]);
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
            d[pos] = op(d[2*pos], d[2*pos+1]);
            pos >>= 1;
        }
    }

    S get(int p)
    {
        assert(0 <= p && p < _n);
        return d[size + p];
    }

    // prod on [l, r)
    S prod(int l, int r)
    {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return e();
        l += size; r += size;
        S sml = e(), smr = e();
        while (l < r)
        {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1; r >>= 1;
        }
        return op(sml, smr);
    }

    // apply range [l, r) with mapping(f, s) done as point-wise updates (O(range * (log n))!)
    void apply(int l, int r, F f)
    {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;
        for (int i = l; i < r; ++i)
        {
            S cur = get(i);
            S nxt = mapping(f, cur);
            set(i, nxt);
        }
    }

    template <bool (*g)(S)>
    int max_right(int l)
    {
        return max_right(l, [](S x){ return g(x); });
    }

    template <class G>
    int max_right(int l, G g)
    {
        assert(0 <= l && l <= _n);
        assert(g(e()));
        if (l == _n) return _n;
        int idx = l + size;
        S sm = e();
        do
        {
            while ((idx & 1) == 0) idx >>= 1;
            if (!g(op(sm, d[idx])))
            {
                while (idx < size)
                {
                    idx <<= 1;
                    if (g(op(sm, d[idx])))
                    {
                        sm = op(sm, d[idx]);
                        ++idx;
                    }
                }
                return idx - size;
            }
            sm = op(sm, d[idx]);
            ++idx;
        } while ((idx & -idx) != idx);
        return _n;
    }

    template <bool (*g)(S)>
    int min_left(int r)
    {
        return min_left(r, [](S x){ return g(x); });
    }

    template <class G>
    int min_left(int r, G g)
    {
        assert(0 <= r && r <= _n);
        assert(g(e()));
        if (r == 0) return 0;
        int idx = r + size;
        S sm = e();
        do
        {
            --idx;
            while (idx > 1 && (idx & 1))
                idx >>= 1;
            if (!g(op(d[idx], sm)))
            {
                while (idx < size)
                {
                    idx = idx * 2 + 1;
                    if (g(op(d[idx], sm)))
                    {
                        sm = op(d[idx], sm);
                        --idx;
                    }
                }
                return idx + 1 - size;
            }
            sm = op(d[idx], sm);
        } while ((idx & -idx) != idx);
        return 0;
    }
};

//* 0 based indexing 
//* [l,r)
//* int max_right(int l, G g) - max r s.t g(l...r-1) is true and g(l...r) is false; true for e()
//* int min_left(int r, G g) - min l s.t g(l...r-1) is true and g(l-1....r-1) is false; true for e()
//* monoid - op is associative and e() is identity
