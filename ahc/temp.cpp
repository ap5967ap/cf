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
    int n;
    cin>>n;
    int N=n;
    n=pow(3,n);
    string s;
    cin>>s;
    int sz=1,add=1;
    for(int i=0;i<N;i++)
    {
        add*=3;
        sz+=add;
    }
    vector<int>v(sz+1);
    vector<array<int,2>>dp(sz+1,{-1,-1});
    int i=sz-add+1;
    for(int j=0;j<n;j++)
    {
        v[i]=(s[j]-'0');
        if((s[j]-'0')) dp[i]={1,0};
        else dp[i]={0,1};
    }
    i=sz-add;
    while(i>0)
    {
        int c1=3*i-1;
        int c2=3*i;
        int c3=3*i+1;
        if(v[c1]+v[c2]+v[c3]>=2) v[i]=1;
        else v[i]=0;
        i--;
    }
    auto dfs=[&](int u, int val, auto &&dfs)->int
    {
        if(dp[u][val]!=-1) return dp[u][val];
        int cnt=0;
        int c1=3*i-1;
        int c2=3*i;
        int c3=3*i+1;
        if(v[c1]==val) cnt++;
        if(v[c2]==val) cnt++;
        if(v[c3]==val) cnt++;
        if(cnt>=2) 
        {
            dp[u][val]=0;
        }
        else if(cnt==1)
        {
            int v1=dfs(c1,val,dfs),v2=dfs(c2,val,dfs),v3=dfs(c3,val,dfs);
            dp[u][val]=min({v1,v2,v3});
        }
        else
        {
            int v1=dfs(c1,val,dfs),v2=dfs(c2,val,dfs),v3=dfs(c3,val,dfs);
            dp[u][val]=v1+v2+v3-max({v1,v2,v3});
        }
        return dp[u][val];
    };
    cout<<dfs(1,1-v[1],dfs);
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