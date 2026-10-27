template <typename T,
          typename F = const T& (*)(const T&, const T&)>
class sparse_table_chan
{
    int n;
    vector<vector<T>> mat;
    F unite;

public:
    explicit sparse_table_chan(const vector<T> &a, F op)
        : n(a.size()), unite(op)
    {
        assert(n > 0);

        int LG = 32 - __builtin_clz((unsigned)n);
        mat.resize(LG);
        mat[0] = a;

        for (int j = 1; j < LG; ++j)
        {
            int len = 1LL << j;
            int half = len / 2;

            mat[j].resize(n - len + 1);
            for (int i = 0; i + len <= n; ++i)
                mat[j][i] = unite(mat[j - 1][i],
                                  mat[j - 1][i + half]);
        }
    }

    // [from, to].
    T query(int from, int to) const
    {
        assert(0 <= from && from <= to && to < n);

        int lg = 31 - __builtin_clz((unsigned)(to - from + 1));

        return unite(mat[lg][from],
                     mat[lg][to - (1LL << lg) + 1]);
    }
};

// sparse_table_chan<int> mn(a, min);

// sparse_table_chan gc(a, [](int x, int y) {
//     return gcd(x, y);
// });
