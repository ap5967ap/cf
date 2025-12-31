#include <bits/stdc++.h>
using namespace std;
#include<atcoder/convolution>
using namespace atcoder;
#define ll long long
void solve(int tc)
{   
    int n;
    cin>>n;
    vector<int>f(5+1);
    vector<int>ar;
    for(int i=0;i<n;i++)
    {
        int a;
        cin>>a;
        ar.push_back(a);
        f[a]++;
    }
    ll ans=0;
    auto c=convolution(f,f);
    for(int i=0;i<c.size();i++)
    {
        cerr<<c[i]<<" ";
    }
    cerr<<endl;
    vector<int>f1(c.size());
    for(int i=0;i<ar.size();i++)
    {
        for(int j=i+1;j<ar.size();j++)
        {
            f1[ar[i]+ar[j]]++;
        }
    }
    for(int i=0;i<c.size();i++) cout<<f1[i]<<" ";
    cout<<endl;
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