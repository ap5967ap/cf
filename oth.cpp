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
    vector<int>ar(n+1);
    for(int i=1;i<=n;i++)
        cin>>ar[i];
    auto cc = [&](int l, int r)
    {
        vector<int> v;
        for (int i = l; i <= r; i++) v.push_back(ar[i]);
        int n = v.size();
        vector<int> dp(n + 2, 0);
        for (int i = n; i >= 1; i--)
        {
            dp[i] = dp[i + 1];
            for (int j = i; j <= n; j++)
            {
                dp[i] = max(dp[i], dp[j + 1] + v[i - 1] + (j - i));
            }
        }
        return dp[1];
    };
    int ans=0;
    for(int l=1;l<=n;l++)
        for(int r=l;r<=n;r++)  
            ans+=cc(l,r);
    cout<<ans<<endl;
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