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

struct fenwick_lazy 
{
    fenwick_tree_chan<int> B1, B2;
    int n;

    fenwick_lazy(int n) : n(n), B1(n), B2(n) {}

    void range_add(int l, int r, int v) 
    {
        B1.modify(l, v);
        if (r + 1 < n) B1.modify(r + 1, -v);
        B2.modify(l, v * (l - 1));
        if (r + 1 < n) B2.modify(r + 1, -v * r);
    }

    int prefix_sum(int x) 
    {
        if (x < 0) return 0;
        return B1.query(x) * x - B2.query(x);
    }

    int range_sum(int l, int r) 
    {
        return prefix_sum(r) - prefix_sum(l - 1);
    }
};
