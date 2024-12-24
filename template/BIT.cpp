#include<vector>
using namespace std;
class BIT
{
public:
    int n;
    vector<int>bit;
    BIT(int n)
    {
        this->n=n;
        bit.resize(n+1,0);
    }
    void update(int i, int val)
    {
        for(;i<=n;i+=i&-i)bit[i]+=val;
    }
    int query(int i) //returns sum of elements from 1 to i
    {
        int sum=0;
        for(;i>0;i-=i&-i)sum+=bit[i];
        return sum;
    }
    int query(int l, int r) //returns sum of elements from l to r
    {
        return query(r)-query(l-1);
    }
};