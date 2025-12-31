class dsu_chan
{
public:
    int n;
    vector<int> par, siz;
    vector<int> nxt;    // for fast skipping of deleted elements
    vector<bool> dead;  // whether element is deleted

    dsu_chan(int n) : n(n), par(n), siz(n, 1), nxt(n + 1), dead(n, false)
    {
        iota(par.begin(), par.end(), 0);
        iota(nxt.begin(), nxt.end(), 0);
    }

    int get(int x)
    {
        return (par[x] == x ? x : par[x] = get(par[x]));
    }

    void unite(int x, int y)
    {
        x = get(x), y = get(y);
        if (x == y) return;
        if (siz[x] > siz[y]) swap(x, y);
        par[x] = y;
        siz[y] += siz[x];
    }

    // find next alive element >= x
    int next_alive(int x)
    {
        if (x >= n) return n;
        return nxt[x] == x ? x : nxt[x] = next_alive(nxt[x]);
    }

    // delete all elements from l..r (inclusive)
    void erase_range(int l, int r)
    {
        int cnt = 0;
        for (int i = next_alive(l); i <= r; i = next_alive(i))
        {
            dead[i] = true;
            cnt++;
            nxt[i] = i + 1; // skip this element in future
        }
        cout << cnt << "\n";
    }

    vector<vector<int>> group()
    {
        vector<vector<int>> g(n);
        for (int u = 0; u < n; u++)
            if (!dead[u])
                g[get(u)].push_back(u);
        return g;
    }
};

