template <typename T>
class fenwick2d
{
    public:
    int n, m;
    vector<vector<T>> tree;
    fenwick2d(int n, int m)
    {
        this->n = n;
        this->m = m;
        tree.assign(n+1,vector<T>(m+1,0));
    }
    void update(int x, int y, T val) 
    {
        for (int i = x; i <= n; i += (i & -i)) 
        {
            for (int j = y; j <= m; j += (j & -j)) 
            {
                tree[i][j] += val;
            }
        }
    }
    T query(int x, int y) 
    {
        T sum = 0;
        for (int i = x; i > 0; i -= (i & -i)) 
        {
            for (int j = y; j > 0; j -= (j & -j)) 
            {
                sum += tree[i][j];
            }
        }
        return sum;
    }
    T query(int x1, int y1, int x2, int y2) 
    {
        return query(x2, y2) 
             - query(x1 - 1, y2) 
             - query(x2, y1 - 1) 
             + query(x1 - 1, y1 - 1);
    }
    // 1 based and [x1..x2]*[y1..y2]
};