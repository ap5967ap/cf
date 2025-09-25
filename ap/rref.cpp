template<typename T>
struct DynamicModularSystem {
    int nvars;
    vector<vector<T>> mat;    
    vector<int> pivot_col;    
    vector<int> where;        
    DynamicModularSystem(int nvars_) : nvars(nvars_), where(nvars_, -1) {}

private:
    bool isZero(const T &x)
    {
        return x == T(0);
    }

public:
    bool addRow(vector<T> row) 
    {
        if ((int)row.size() != nvars + 1) throw runtime_error("row size mismatch");
        for (int i = 0; i < (int)mat.size(); ++i) 
        {
            int pcol = pivot_col[i];
            if (pcol == -1) continue;
            if (!isZero(row[pcol])) 
            {
                T factor = row[pcol];
                for (int j = pcol; j <= nvars; ++j) 
                {
                    row[j] = row[j] - factor * mat[i][j];
                }
            }
        }
        int lead = -1;
        for (int j = 0; j < nvars; ++j) if (!isZero(row[j])) { lead = j; break; }
        if (lead == -1) 
        {
            if (!isZero(row[nvars])) return false;
            return true;
        }
        T pivot_val = row[lead];
       
        for (int j = lead; j <= nvars; ++j) 
        {
            row[j] = row[j] / pivot_val;
        }
        for (int i = 0; i < (int)mat.size(); ++i) 
        {
            if (!isZero(mat[i][lead])) 
            {
                T factor = mat[i][lead];
                for (int j = lead; j <= nvars; ++j) 
                {
                    mat[i][j] = mat[i][j] - factor * row[j];
                }
            }
        }
        pivot_col.push_back(lead);
        mat.push_back(row);
        where[lead] = (int)mat.size() - 1;
        return true;
    }

    pair<bool, vector<T>> solve() const 
    {
        vector<T> solution(nvars, T(0));
        for (int r = 0; r < (int)mat.size(); ++r) 
        {
            int p = pivot_col[r];
            if (p >= 0 && p < nvars) solution[p] = mat[r][nvars];
        }
        return {true, solution};
    }

    void printMatrix(ostream &out = cout) const 
    {
        for (auto &r : mat) 
        {
            for (int j = 0; j <= nvars; ++j) out << r[j] << ' ';
            out << '\n';
        }
    }

    /*
            DynamicModularSystem<double> sys(3);
            sys.addRow({1.0, 2.0, 3.0, 1.0});
            sys.addRow({2.0, 4.0, 6.0, 2.0});
            sys.addRow({1.0, 0.0, 1.0, 3.0});
            sys.printMatrix();
            auto [ok, sol] = sys.solve();
            for (auto &v : sol) cout << v << ' ';
            cout << '\n';
    */
};
