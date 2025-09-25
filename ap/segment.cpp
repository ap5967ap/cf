struct Node 
{
    int mx,mn,sm;
};
class segtree
{
    public:
    vector<Node>tree;
    vector<int> arr;
    int n;
    void unite(Node &merged, Node &left, Node &right)
    {   
        merged.mn=min(left.mn,right.mn);
        merged.mx=max(left.mx,right.mx);
        merged.sm=(left.sm+right.sm);
    }
    void build(int idx,int st,int en) 
    {
        if (st==en) tree[idx]={arr[st],arr[st],arr[st]};
        else
        {
            int mid=(st+en)/2;
            build(2*idx+1,st,mid);
            build(2*idx+2,mid+1,en);
            Node left=tree[2*idx+1];
            Node right=tree[2*idx+2];
            unite(tree[idx],left,right);
        }
    }
    Node query(int idx,int st,int en,int l,int r) 
    {
        Node ansNode;
        if (r<st || en<l) ansNode={-inf,inf,0}; 
        else if (l<=st && en<=r) ansNode=tree[idx];
        else
        {
            int mid=(st+en)/2;
            Node left=query(2*idx+1,st,mid,l,r);
            Node right=query(2*idx+2,mid+1,en,l,r);
            unite(ansNode,left,right);
        }
        return ansNode;
    }
    void update(int idx,int st,int en,int pos,int val) 
    {
        if (st==en) tree[idx]={val,val,val},arr[en]=val; 
        else
        {
            int mid=(st+en)/2;
            if (pos<=mid) update(2*idx+1,st,mid,pos,val);
            else update(2*idx+2,mid+1,en,pos,val);
            Node left=(tree[2*idx+1]);
            Node right=tree[2*idx+2];
            unite(tree[idx],left,right);
        }
    }

    segtree(vector<int> input) // 0 based
    {
        this->arr=input;
        this->n=arr.size();
        this->tree.resize(4*n);
        build(0,0,n-1);
    }
    Node query(int l, int r) // 0 based
    {
        return query(0,0,n-1,l,r);
    }
    void update(int pos,int val) // 0 based
    {
        update(0,0,n-1,pos,val);
    }
};