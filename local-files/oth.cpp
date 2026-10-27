#include <bits/stdc++.h>
#include <cassert>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#define dbg(x...) cerr << "[" << #x << "]=["; _print(x)
#else
#define dbg(x...) 
#endif

#define inf (long long)1e18
#define endl "\n"
#define int int64_t
#define x first
#define y second
#define all(x) (x).begin(),(x).end() 
#define ii <int,int>
#define pii pair ii
#define pb push_back
#define vi vector<int>
#define vvi vector<vi>
#define vii vector<pii>
const int MAX=1e6+1;
bool v[MAX]={false};
vector<int>primes(1,2);
int len,sp[MAX];
void Sieve()
{
    for(int i=2;i<MAX;i+=2)sp[i]=2;
    sp[1]=1;
    for(int i=3;i<MAX;i+=2)
    {
        if(!v[i])
        {
            primes.push_back(i);
            sp[i]=i;
            for(int j=i*i;j<MAX;j+=i)
            {  
                if(!v[j])
                {
                    v[j]=true;
                    sp[j]=i;
                }
            }
        }
    }
}

void solve(int tc)
{   
    int n;
    cin>>n;
    vector<vector<int>>g(n+1);
    for(int i=2;i<=n;i++)
    {
        if(sp[i]==i)
        {
            for(int j=2*i;j<=n;j+=i)
            {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }
    int q;
    cin>>q;
    while(q--)
    {
        int a,b;
        cin>>a>>b;
        vector<int>dis(n+1,inf);
        dis[a]=0;
        queue<int>q;
        q.push(a);
        while(q.size())
        {
            int u=q.front();
            q.pop();
            for(auto v:g[u])
            {
                if(dis[v]>dis[u]+1)
                {
                    q.push(v);
                    dis[v]=dis[u]+1;
                }
            }
        }
        int ans=dis[b];
        if(dis[b]>=inf) ans=-1;
        cout<<ans<<endl;
    }
}   
int32_t main()      
{   
    #ifdef LOCAL1
        auto begin = std::chrono::high_resolution_clock::now();
    #endif
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int t=1;
    Sieve();
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