#include <bits/stdc++.h>
#include <atcoder/modint>

using namespace std;
using namespace atcoder;
using mint = modint998244353;

#define N 60

mint c[N+1][N+1]; //c[i][j]=(the number of x  s.t. 0<=x<(2^i), popcount(x)=j) for 0<=j<=i<=60
mint s[N+1][N+1]; //s[i][j]=(the sum    of x  s.t. 0<=x<(2^i), popcount(x)=j) for 0<=j<=i<=60

void preset(void){
	for(int i=0;i<=N;i++)for(int j=0;j<=N;j++){
		c[i][j]=0,s[i][j]=0;
	}
	c[0][0]=1;
	for(int i=0;i<60;i++){
		for(int j=0;j<=i;j++){
			c[i+1][j+1]+=c[i][j];
			s[i+1][j+1]+=s[i][j];
			s[i+1][j+1]+=(c[i][j]*((mint)2).pow(i));
			c[i+1][j]+=c[i][j];
			s[i+1][j]+=s[i][j];
		}
	}
	return;
}

int solve(long long n,int k){
	int a[N];
	for(int i=0;i<N;i++){
		a[i]=n&1;
		n=(n>>1);
	}
	int cur=0;
	mint offset=0;
	mint ans=0;
	for(int i=N-1;i>=0;i--){
		if(a[i]==1){
			if(cur<=k){
				ans+=s[i][k-cur];
				ans+=offset*c[i][k-cur];
			}
			cur++;
			offset+=((mint)2).pow(i);
		}
	}
	if(cur==k)ans+=offset;
	return (ans.val());
}

int main(void){
	preset();
	int t,k;
	long long n;
	cin>>t;
	for(int i=0;i<t;i++){
		cin>>n>>k;
		cout<<solve(n,k)<<endl;
	}
	return 0;
}
