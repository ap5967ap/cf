#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf (long long)1e18
#define ll long long
#define MOD 1000000007
#define MOD1 998244353
#define endl "\n"
#define x first
#define y second
#define sz size()
#ifdef LOCAL
#include "debug.hpp"
#define dbg(x...) cerr << "[" << #x << "]=["; _print(x)
#define fastio 
#else
#define dbg(x...) 
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#endif
#define all(x) (x).begin(), (x).end() 
#define NL cout<<endl;
#define f(i, a, n) for (int i=a; i<n; i++)
#define fr(i, n) for (int i=0; i<n; i++)
#define fr1(i, n) for(int i=1;i<=n;i++)
#define frr(i,n) for(int i=n-1;i>=0;i--)
#define each(x, a) for(auto &x : a)
#define gcd(x, y) __gcd(x, y)
#define lcm(x, y) ((x*y) / gcd(x, y))
#define cl(a, b) ((a+b - 1)) /( b) //?ceill
#define unq(v) {sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end());}
int power(int a, int b){if(b==0)return 1;int res=power(a,b/2);if(b%2)return res*res*a;else return res*res;}int POWM(int a,int b,int m=MOD){a%=m;int res=1;while(b>0){if(b&1)res=res*a%m;a=a*a%m;b>>=1;}return res;}int modinv(int a,int m=MOD){return POWM(a,m-2,m);}
#define sort_(a) sort(a.begin(),a.end())
#define rev(a) reverse(a.begin(),a.end())
#define ld long double
#define pb push_back
#define eb emplace_back
#define em emplace
struct custom_hash{static uint64_t splitmix64(uint64_t x){x+=0x9e3779b97f4a7c15;x=(x^(x>>30))*0xbf58476d1ce4e5b9;x=(x^(x>>27))*0x94d049bb133111eb;return x^(x>>31);}size_t operator()(uint64_t x)const{static const uint64_t FIXED_RANDOM=chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x+FIXED_RANDOM);}};
typedef vector<ll>vi;typedef pair<ll,ll>pii;typedef vector<pii>vii;typedef vector<vi>vvi;typedef deque<int>dq;typedef map<int,int>mi;typedef map<pii,int>mii;typedef queue<int>qi;typedef queue<pii>qii;typedef vvi grf;typedef set<int>si;typedef priority_queue<int, vi> pq; typedef vector<vvi> vvvi;typedef priority_queue<int, vi, greater<int>> mpq;typedef unordered_map<int, int,custom_hash> unmap;typedef unordered_set<int, custom_hash> unset;
typedef vector<ll>vi;typedef pair<ll,ll>pii;typedef vector<pii>vii;typedef vector<vi>vvi;typedef deque<int>dq;typedef map<int,int>mi;typedef map<pii,int>mii;typedef queue<int>qi;typedef queue<pii>qii;typedef vvi grf;typedef set<int>si;typedef priority_queue<int, vi> pq; typedef priority_queue<int, vi, greater<int>> mpq;typedef unordered_map<int, int,custom_hash> unmap;typedef unordered_set<int, custom_hash> unset;
#define sum(a) accumulate(all(a),0LL)
#define maxx(a) (*max_element(all(a)))
#define minn(a) (*min_element(all(a)))
#define no {cout<<"NO"<<endl; return;}
#define yes {cout<<"YES"<<endl; return;}
#define rpt return pt
void in(vi &a,int n){a.resize(n);fr(i,n)cin>>a[i];}void in(grf &g, int nodes,int edges=-1){if(edges==-1)edges=nodes-1; g.clear();g.resize(nodes);int a,b;fr(i,edges){cin>>a>>b,--a,--b,g[a].pb(b),g[b].pb(a);}}
void pt(vi &v){each(i,v)cout<<i<<" ";NL}void pt(int x){cout<<x;NL}void pt(string s){cout<<s;NL}void pt(char &c){cout<<c;NL}void pt(pii p){cout<<p.x<<" "<<p.y;NL}void pt(mi &mp){each(i,mp)cout<<i.x<<" "<<i.y;NL}void pt(unmap &mp){each(i,mp)cout<<i.x<<" "<<i.y;NL}void pt(vvi &v){each(i,v)pt(i);}void pt(vii &v){each(i,v)cout<<i.x<<" "<<i.y<<endl;}void pt(double &d){cout<<d;NL}void pt(float &f){cout<<f;NL}template<typename T>void pt(set<T>&s){each(i,s)cout<<i<<" ";NL}
int chmin(int &a, int b){return a=min(a,b);}
int chmax(int &a, int b){return a=max(a,b);}
void solve(int tc)
{   
    
}   
int32_t main()      
{   
    fastio
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int t;
    cin>>t;
    // t=1;
    int tc=1;
    while (t--)
    {
        solve(tc),tc++;
    }
    return 0;
}  