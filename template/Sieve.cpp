#include<vector>
using namespace std;


const int MAX=1e6+1;
bool v[MAX];
int len, sp[MAX]; //*sp[i] stores the smallest prime factor of i
void Sieve(){
	for(int i=2;i<MAX;i+=2)sp[i]=2;//even numbers have smallest prime factor 2
	for(int i=3;i<MAX;i+=2)
    {
		if (!v[i])
        {
			sp[i]=i;
			for(int j=i;(j*i)<MAX;j+=2)
            {
				if(!v[j*i]) v[j*i]=true,sp[j*i]=i;
			}
		}
	}
}
vector<int> factorize(int k) 
{
	vector<int> ans;
	while(k>1)
    {
		ans.push_back(sp[k]);
		k/=sp[k];
	}
	return ans;
}