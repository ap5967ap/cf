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
class SegmentTree {
    private:
        int n;
        vector<long long> tree;
    
        void build(int node, int l, int r) {
            if (l == r) {
                tree[node] = 1;
            } else {
                int mid = (l + r) / 2;
                build(2 * node + 1, l, mid);
                build(2 * node + 2, mid + 1, r);
                tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
            }
        }
    
        long long query(int node, int l, int r, int ql, int qr) {
            if (qr < l || r < ql) return 0;          // No overlap
            if (ql <= l && r <= qr) return tree[node]; // Total overlap
            int mid = (l + r) / 2;
            return query(2 * node + 1, l, mid, ql, qr) +
                   query(2 * node + 2, mid + 1, r, ql, qr);
        }
    
        void update(int node, int l, int r, int idx, int val) {
            if (l == r) {
                tree[node] = val;
            } else {
                int mid = (l + r) / 2;
                if (idx <= mid)
                    update(2 * node + 1, l, mid, idx, val);
                else
                    update(2 * node + 2, mid + 1, r, idx, val);
                tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
            }
        }
    
    public:
        SegmentTree(int n) {
            tree.resize(4 * n);
            build(0, 0, n - 1);
        }
    
        long long query(int l, int r) {
            return query(0, 0, n - 1, l, r);
        }
    
        void update(int idx, int val) {
            update(0, 0, n - 1, idx, val);
        }
    };
    
void solve(int tc)
{   
    int n;
    cin>>n;
    vector<vector<int>>g(n);
    map<int,pair<int,int>>mp;
    for(int i=0;i<n-1;i++) 
    {
        int a,b;
        cin>>a>>b;
        g[a-1].push_back(b-1);
        g[b-1].push_back(a-1);
        mp[i]={a-1,b-1};
    }
    SegmentTree s(n);
    vector<int>st(n);
    vector<int>en(n);
    int tt=0;
    int tot=n;
    auto dfs=[&](int u, int p, auto &&dfs)->void
    {
        st[u]=tt++;
        for(auto v:g[u])
        {
            if(v!=p)
            {
                dfs(v,u,dfs);
            }
        }
        en[u]=tt-1;
    };
    dfs(0,-1,dfs);
    int q;
    cin>>q;
    while(q--)
    {
        int t;
        cin>>t;
        if(t==1)
        {
            int node,v;
            cin>>node>>v;
            --node;
            // s.update(st[node],v);
            tot+=v;
            return;
        }
        else
        {
            int i;
            cin>>i;
            auto [u,v]=mp[i-1];
            int node=u;
            if(st[u]<st[v]) node=v;
            dbg(st[node],en[node]);
            int val=s.query(st[node],en[node]);
            cout<<abs(tot-2*val)<<endl;
        }
    }
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