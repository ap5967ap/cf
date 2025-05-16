#include<vector>
#include<numeric>
using namespace std;

class dsu
{
public:
    int n;
    vector<int>parent,size;
    dsu(int n)//time complexity O(n)
    {
        this->n=n;
        parent.resize(n);
        size.resize(n,1);
        iota(parent.begin(),parent.end(),0);//? parent[i]=i
    }
    int find(int x) //time complexity O(1) amortized    
    {
        return parent[x]==x?x:parent[x]=find(parent[x]);
    }
    void unite(int x, int y) //time complexity O(1) amortized
    {
        x=find(x),y=find(y);
        if(x!=y)
        {
            if(size[x]<size[y])swap(x, y);
            parent[y]=x,size[x]+=size[y];
        }
    }
};