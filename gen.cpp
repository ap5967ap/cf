#include<bits/stdc++.h>
using namespace std;
#define ll long long int
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define pbds tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>
#define endl '\n'
void treeTCgenerator(int n)
{
    pbds inT;
    pbds notinT;
    ll root = 1;//almost centroid
    //*uncomment the below line to create random root
    //*root = ((ll) rand() * rand()) % n + 1;
    inT.insert(root);
    for (ll i = 1; i <= n; i++)
    {
        if(i != root){
            notinT.insert(i);
        }
    }
    for (ll i = 0; i < n - 1; i++)
    {
        ll r = rand();
        ll incSize = inT.size();

        r %= incSize;

        auto itU = inT.find_by_order(r);
        ll u = *itU;

        r = rand();
        
        ll notIncSize = notinT.size();

        r %= notIncSize;

        auto itV = notinT.find_by_order(r);
        ll v = *itV;

        notinT.erase(itV);
        inT.insert(v);

        cout << u << " " << v << "\n";
    }
}

int rand(int a, int b)
{
    return a+rand()%(b-a+1);
}
int32_t main(int argc, char *argv[] )
{
    srand(stoi(argv[1]));
    cout<<1<<endl;
    int n=rand(2,5);
    cout<<n<<endl;
    cout<<rand(1,7)<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<rand(1,7)<<" ";
    }
    cout<<endl;
    
}