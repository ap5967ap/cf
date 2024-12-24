#include<bits/stdc++.h>
using namespace std;

struct custom_hash{static uint64_t splitmix64(uint64_t x){x+=0x9e3779b97f4a7c15;x=(x^(x>>30))*0xbf58476d1ce4e5b9;x=(x^(x>>27))*0x94d049bb133111eb;return x^(x>>31);}size_t operator()(uint64_t x)const{static const uint64_t FIXED_RANDOM=chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x+FIXED_RANDOM);}};



//!bit manipulation notes
//* n & (n-1) removes the last set bit from LSB 
//* n & (-n) gives the last set bit from LSB
//* n & (n+1)  clears all trailing ONES
//* n | (n+1)  sets the last cleared bit 0011 0101 -> 0011 0111
//* a+b=(a^b)+2(a&b) = (a|b) + (a&b) 
//__builtin_ffs //? returns the first bit set in a number
//__has_single_bit(n) //? returns true if n is a power of 2
// __builtin_clzll(n) //? returns the number of leading 0-bits in n, starting at the most significant bit position. If n is 0, the result is undefined.
// __builtin_ctzll(n) //? returns the number of trailing 0-bits in n, starting at the least significant bit position. If n is 0, the result is undefined.
// __builtin_popcountll(n) //? returns the number of 1-bits in n.
// __builtin_parityll(n) //? returns the number of 1-bits in n modulo 2 =parity = Parity of a number refers to whether it contains an odd or even number of 1-bits.
// bit_ceil / bit_floor //?round up/down to the next power of two


//! coordinate compression 
// for 2 44 234 2 2
// gives 1 2 3 1 1
void compress(vector<int> &v)
{
    map<int,int> mp;
    int ind=1;
    for(int i=0;i<v.size();i++) if(!mp[v[i]]) mp[v[i]]=ind++;
    for(int i=0;i<v.size();i++) v[i]=mp[v[i]];
}