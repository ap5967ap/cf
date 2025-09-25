template<typename T>
class combinatorics2d
{   
    public:
    int n;
    vector<vector<T>> C;
    combinatorics2d(int n) : n(n), C(n+1, vector<T>(n+1, 0)) 
    {
        for (int i = 0; i <= n; i++) 
        {
            C[i][0] = C[i][i] = T(1);   
            for (int j = 1; j < i; j++) 
            {
                C[i][j] = C[i-1][j-1] + C[i-1][j];
            }
        }
    }

    T ncr(int N, int R)
    {
        if (R < 0 || R > N) return T(0);
        return C[N][R];
    }
};