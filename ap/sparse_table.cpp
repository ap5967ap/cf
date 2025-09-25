class sparse_table
{
    vector<vector<int>> st;
    vector<int> log;
    int func(int a, int b)
    {
        return min(a, b);
    }

public:
    sparse_table(vector<int> &arr)
    {
        int n = arr.size();
        log.resize(n + 1);
        for (int i = 2; i <= n; ++i)
        {
            log[i] = log[i / 2] + 1;
        }
        int k = log[n] + 1;
        st.assign(n, vector<int>(k));
        for (int i = 0; i < n; ++i)
        {
            st[i][0] = arr[i];
        }
        for (int j = 1; (1 << j) <= n; ++j)
        {
            for (int i = 0; i + (1 << j) - 1 < n; ++i)
            {
                st[i][j] = func(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int L, int R) // 0 based indexing [l,r]
    {
        int j = log[R - L + 1];
        return func(st[L][j], st[R - (1 << j) + 1][j]);
    }
};
