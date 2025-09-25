template <class S,
          auto op,
          auto e,
          class F,
          auto mapping,
          auto composition,
          auto id,
          const bool islazy,
          const bool on_edge>
class heavy_light_chan
{
    /*
        info:
            - 0 indexed
            - range [pos[u], out[u]) represents subtree of u
        vars:
            - r = tree root
            - heavy[u] = heavy child v (edge (u,v) is heavy edge) 
            - root[u] = It is the starting point of the heavy chain (for u-v it is u, if v is heavy and u is not heavy). 
            - on_edge = true => values on edges. Internally, value of edge is stored at lower node (node more away from root)
        warning:
            - handle segtree initialization correctly
    */
    using lazy_t = lazy_segtree<S, op, e, F, mapping, composition, id>;
    using simple_t = simple_segtree<S, op, e, F, mapping>;
    using seg_t = std::conditional_t<islazy, lazy_t, simple_t>;

public:
    int n, r;
    vector<int> par, heavy, dep, root, pos, out;
    seg_t seg;
    heavy_light_chan(int n, vector<vector<int>> adj, int r = 0) : 
    n(n), r(r), par(n, -1), heavy(n, -1), dep(n), root(n), pos(n), out(n), 
    seg(n) 
    {   
        assert(r < n);
        auto dfs_sz = [&](int u, auto &&dfs) -> int
        {
            //* ensure that in adj list first child is the heavy child
            int sz = 1, mx_sz = 0; 
            for(auto &v : adj[u])
            {
                if(v != par[u])
                {
                    par[v] = u, dep[v] = dep[u] + 1;
                    int s = dfs(v, dfs);
                    sz += s;
                    if(s > mx_sz)
                    heavy[u] = v, mx_sz = s, swap(adj[u][0], v); 
                }
            }
            return sz;
        };
        int timer = 0;
        auto dfs_hld = [&](int u, auto &&dfs) -> void
        {
            pos[u] = timer++;
            for(auto v : adj[u])
            {
                if(v != par[u])
                {
                    root[v] = (heavy[u] == v ? root[u] : v);
                    dfs(v, dfs);
                }
            }
            out[u] = timer ; // exclusive
        };
        par[r] = -1;
        dep[r] = 0;
        root[r] = r;
        dfs_sz(r, dfs_sz);
        dfs_hld(r, dfs_hld);
    }
    int lca(int u, int v)
    {
        for (; root[u] != root[v]; v = par[root[v]])
        {
            if (dep[root[u]] > dep[root[v]])
            {
                swap(u, v);
            }
        }
        return (dep[u] < dep[v] ? u : v);
    }

    // *process_path [u, v] in O(logn * logn)
    template <typename O>
    void process_path(int u, int v, O oper)
    {
        for (; root[u] != root[v]; v = par[root[v]])
        {
            if (dep[root[u]] > dep[root[v]])
                swap(u, v);
            oper(pos[root[v]], pos[v]);
        }
        if (dep[u] > dep[v])
            swap(u, v);
        
        if(!on_edge)
            oper(pos[u], pos[v]);
        else if(u != v)
            oper(pos[u] + 1, pos[v]);
    }

    void set(int v, const S &value) 
    {
        seg.set(pos[v], value);
    }
    
    S get(int v) 
    {
        return seg.get(pos[v]);
    }

    void modify_path(int u, int v, const F &f) 
    {
        process_path(u, v, [this, &f](int l, int r) 
        {
            seg.apply(l, r + 1, f); // convert inclusive [l,r] -> atcoder apply [l, r+1)
        });
    }

    S query_path(int u, int v) 
    {
        S res = e();
        process_path(u, v, [this, &res](int l, int r) 
        {
            S part = seg.prod(l, r + 1);
            res = op(res, part);
        });
        return res;
    }

    void modify_subtree(int u, const F &f) 
    {
        if (!on_edge) 
        {
            seg.apply(pos[u], out[u], f); // subtree = [pos[u], out[u])
        } 
        else 
        {
            // edges stored at children; exclude its parent values that it at u
            if (pos[u] < out[u] - 1)
                seg.apply(pos[u] + 1, out[u], f);
        }
    }
    S query_subtree(int u) 
    {
        if (on_edge) 
        {
            if (pos[u] < out[u] - 1)
            {
                return seg.prod(pos[u] + 1, out[u]);
            }
            else
            {
                return e();
            }
        }
        return seg.prod(pos[u], out[u]);
    }

};
