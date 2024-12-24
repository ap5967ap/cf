#include<bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int a, int b)
{
    return a+rng()%(b-a+1);
}
void solve()
{
    
}
int main(int argc, char *argv[] )
{
    int t=1;
    srand(stoi(argv[1]));
    cout<<t<<endl;
    while(t--)
    {
        int n=rand(1,5);
        cout<<n<<" ";
        int m=rand(1,5);
        cout<<m<<"\n";
        for(int i=0;i<n;i++)
        {
            cout<<rand(1,10)<<" ";
        }
        cout<<endl;
        for(int i=0;i<m;i++)
        {
            cout<<rand(1,10)<<" ";
        }
        cout<<endl;
    }
}