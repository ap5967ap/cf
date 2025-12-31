#include<bits/stdc++.h>
using namespace std;

const int N = 10000000;
vector<int> lp(N+1); //lowest prime factor
vector<int> pr; // prime list

void sieve(){
    for(int i = 2; i <= N; ++i){
        if (lp[i] == 0) {
                lp[i] = i;
                pr.push_back(i);
        }
        for (int j = 0; i * pr[j] <= N  && j < (int)pr.size(); ++j) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                    break;
                }
        }
    }
}

map<int,int>factorize(int k)
{
    map<int,int> mp;
    while(k >1)
    {
        mp[lp[k]]++;
        k/=lp[k];
    }
    return mp;
}
