#include<bits/stdc++.h>
using namespace std;
const int MAX=2e5+1;
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

map<int,int>factorize(int k)
{
    map<int,int> mp;
    while(k >1)
	{
        mp[sp[k]]++;
        k/=sp[k];
    }
    return mp;
}
