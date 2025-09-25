class BitTrie 
{
public:
    static constexpr int BITS = 31;       // for 32-bit ints use 31 down to 0
    vector<array<int,2>> nxt;
    vector<int> cnt;                      // count of numbers ending exactly at this node
    vector<int> pref;                     // count of numbers passing through this node
    int nodes = 0;

    BitTrie(int maxNodes = 1e6+1) 
    {
        nxt.reserve(maxNodes);
        cnt.reserve(maxNodes);
        pref.reserve(maxNodes);
        newNode();
    }

    int newNode() 
    {
        nxt.push_back({0,0});
        cnt.push_back(0);
        pref.push_back(0);
        return nodes++;
    }

    // insert x (f=+1) or remove x (f=-1)
    void insert(int x, int f = 1) 
    {
        int u = 0;
        for (int b = BITS; b >= 0; --b) 
        {
            int bit = (x >> b) & 1;
            if (!nxt[u][bit])
                nxt[u][bit] = newNode();
            u = nxt[u][bit];
            pref[u] += f;
        }
        cnt[u] += f;
    }

    void remove(int x) { insert(x, -1); }

    // exact count of x
    int count(int x) const 
    {
        int u = 0;
        for (int b = BITS; b >= 0; --b) 
        {
            int bit = (x >> b) & 1;
            int v = nxt[u][bit];
            if (!v || pref[v] <= 0) return 0;
            u = v;
        }
        return cnt[u];
    }

    // maximize x^y over all y in the trie
    int maxXor(int x) const 
    {
        int u = 0;
        int ans = 0;
        for (int b = BITS; b >= 0; --b) 
        {
            int bit = (x >> b) & 1;
            int want = bit ^ 1;
            if (nxt[u][want] && pref[nxt[u][want]] > 0) 
            {
                ans |= (1 << b);
                u = nxt[u][want];
            } else 
            {
                u = nxt[u][bit];
            }
        }
        return ans;
    }

    // count of elements ≤ x
    int leq(int x) const 
    {
        int u = 0, res = 0;
        for (int b = BITS; b >= 0; --b) 
        {
            int bit = (x >> b) & 1;
            if (bit == 1) 
            {
                if(nxt[u][0])
                    res += pref[nxt[u][0]];
                u = nxt[u][1];
            } 
            else 
            {
                u = nxt[u][0];
            }
        }
        if(u) 
            res += cnt[u];
        return res;
    }
};