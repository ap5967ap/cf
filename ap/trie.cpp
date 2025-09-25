class Trie 
{
public:
    static constexpr int ALPHA = 26;
    vector<array<int,ALPHA>> nxt;
    vector<int> cnt, pref;
    int nodes;

    Trie(int mx = 1e6+1) 
    {
        nxt.reserve(mx);
        cnt.reserve(mx);
        pref.reserve(mx);
        newNode(); // create root
    }

    int newNode() 
    {
        nxt.push_back({});
        cnt.push_back(0);
        pref.push_back(0);
        return nodes++;
    }

    // insert s with frequency f (use f=-1 to remove)
    void insert(const string &s, int f = 1) 
    {
        int u = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (!nxt[u][c]) {
                nxt[u][c] = newNode();
            }
            u = nxt[u][c];
            pref[u] += f;
        }
        cnt[u] += f;
    }

    // exact string count
    int count(const string &s) const 
    {
        int u = 0;
        for (char ch : s) 
        {
            int c = ch - 'a';
            if (!nxt[u][c] || pref[nxt[u][c]] <= 0) 
                return 0;
            u = nxt[u][c];
        }
        return cnt[u];
    }

    // count of strings with prefix s
    int prefCount(const string &s) const 
    {
        int u = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (!nxt[u][c] || pref[nxt[u][c]] <= 0)
                return 0;
            u = nxt[u][c];
        }
        return pref[u];
    }

    // sum of prefCounts along path matching s
    int query(const string &s) const 
    {
        // depends on use case

        // int u = 0;
        // int sum = 0;
        // for (char ch : s) {
        //     int c = ch - 'a';
        //     if (!nxt[u][c]) break;
        //     u = nxt[u][c];
        //     sum += pref[u];
        // }
        // return sum;
    }

    // remove s (decrement counts)
    void remove(const string &s) 
    {
        insert(s, -1);
    }
};