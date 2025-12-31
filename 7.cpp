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

void solve(int tc)
{   
    int n,q;
    cin>>n>>q;
    vector<int>ar(n);
    vector<int>pos(n);
    vector<vector<int>>g(n);
    vector<int>par(n,-1);
    for(int i=1;i<n;i++)
    {
        int p;
        cin>>p;
        p--;
        par[i]=p;
        g[p].push_back(i);
    }
    vector<int>sz(n);
    auto dfs=[&](int u, auto &&dfs)->void
    {
        sz[u]++;
        for(auto v:g[u])
        {
            dfs(v,dfs);
            sz[u]+=sz[v];
        }
    };
    dfs(0,dfs);
    for(int i=0;i<n;i++)
    {
        cin>>ar[i];
        ar[i]--;
        pos[ar[i]]=i;
        sz[i]--;
    }
    dbg(par);
    auto cmp = [&](int c1, int c2) {
        return pos[c1] < pos[c2];
    };
    vector<set<int, decltype(cmp)>> v(n, set<int, decltype(cmp)>(cmp));
    vector<set<pair<int,int>>>bad(n);
    set<int>glo;
    int cnt=0;
    for(int i=0;i<n;i++)
    {
        if(g[i].size()==0) continue;
        for(auto adj:g[i])
        {
            v[i].insert(adj);
        }
        if(pos[i]+1!=pos[*v[i].begin()])
        {
            cnt++;
            glo.insert(i);
        }
        for(auto it=v[i].begin();it!=v[i].end();it++)
        {
            if(next(it)==v[i].end()) break;
            auto it1=next(it);
            int c1=*it,c2=*it1;
            if(pos[c2]-pos[c1]!=sz[c1]+1)
            {
                cnt++;
                bad[i].insert({c1,c2});
            }
        }
        dbg(i,v[i]);
    }
    auto comp=[&](int u, int oldp, int newp)
    {
        int p=par[u];
        if(p>=0)
        {
            if(glo.find(p)!=glo.end())
            {
                glo.erase(p);
                cnt--;
            }
            auto it=v[p].find(u);
            if(it!=v[p].begin())
            {
                auto it1=prev(it);
                int prevchild=*it1;
                if(bad[p].find({prevchild,u})!=bad[p].end())
                {
                    bad[p].erase({prevchild,u});
                    cnt--;
                }
                auto it2=next(it);
                if(it2!=v[p].end())
                {
                    int nextchild=*it2;
                    if(pos[nextchild]-pos[prevchild]!=sz[prevchild]+1)
                    {
                        bad[p].insert({prevchild,nextchild});
                        cnt++;
                    }
                }
            }
            if(next(it)!=v[p].end())
            {
                auto it2=next(it);
                int nextchild=*it2;
                if(bad[p].find({u,nextchild})!=bad[p].end())
                {
                    bad[p].erase({u,nextchild});
                    cnt--;
                }
            }
            v[p].erase(u);
        
            v[p].insert(p);
            int fs=*v[p].begin();
            if(pos[p]+1!=pos[fs])
            {
                glo.insert(p);
                cnt++;
            }
            it=v[p].find(u);
            if(it!=v[p].begin())
            {
                auto it1=prev(it);
                auto it2=next(it);
                if(it2!=v[p].end())
                {
                    if(bad[p].find({*it1,*it2})!=bad[p].end())
                    {
                        bad[p].erase({*it1,*it2});
                        cnt--;
                    }
                }
                if(pos[*it1]+sz[*it1]+1!=pos[u])
                {
                    bad[p].insert({*it1,u});
                    cnt++;
                }
            }
            if(next(it)!=v[p].end())
            {
                auto it2=next(it);
                if(pos[u]+sz[u]+1!=pos[*it2])
                {
                    bad[p].insert({u,*it2});
                    cnt++;
                }
            }
        }
        if(g[u].size())
        {
            int fs=*v[u].begin();
            if(glo.find({u})!=glo.end())
            {
                glo.erase(u);
                cnt--;
            }
            if(pos[u]+1!=pos[fs])
            {
                glo.insert(u);
                cnt++;
            }
        }
    };
    dbg(cnt);
    while(q--)
    {
        int x,y;
        cin>>x>>y;
        x--,y--;
        int a=ar[x],b=ar[y];
        pos[a]=y;pos[b]=x;
        swap(ar[x],ar[y]);
        comp(a,x,y);
        comp(b,y,x);
        dbg(cnt);
        if(cnt) cout<<"NO"<<endl;
        else cout<<"YES"<<endl;
    }
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