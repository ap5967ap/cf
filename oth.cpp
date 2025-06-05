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
    vector<int>ar(n);
    for(int i=0;i<n;i++)
    {
        cin>>ar[i];
    }
    int lo,hi;
    cin>>lo>>hi;
	int ans=hi-lo+1;
	for(int i=lo;i<=hi;i++)
	{
		bool fg=1;
		for(int j=0;j<n;j++) fg=fg&((i%ar[j])==0);
		ans-=fg;
	}
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