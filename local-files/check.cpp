#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "Usage: checker input jury_output contestant_output\n";
        return 1;
    }

    ifstream in(argv[1]);
    ifstream jury(argv[2]);
    ifstream cont(argv[3]);

    int T;
    in >> T;

    auto upper = [](string s) {
        for (char &c : s) c = toupper(c);
        return s;
    };

    for (int tc = 1; tc <= T; tc++) {
        int n, m;
        in >> n >> m;

        vector<tuple<int,int,int>> cons;
        for (int i = 0; i < m; i++) {
            int o, l, r;
            in >> o >> l >> r;
            cons.emplace_back(o, l, r);
        }

        string juryAns, stuAns;

        if (!(jury >> juryAns)) {
            cerr << "Invalid jury output\n";
            return 1;
        }

        if (!(cont >> stuAns)) {
            cout << "Wrong Answer\n";
            return 0;
        }

        juryAns = upper(juryAns);
        stuAns = upper(stuAns);

        if (juryAns == "NO") {
            if (stuAns != "NO") {
                cout << "Wrong Answer\n";
                return 0;
            }
            continue;
        }

        // Jury found a solution.
        if (stuAns != "YES") {
            cout << "Wrong Answer\n";
            return 0;
        }

        vector<long long> a(n + 1);

        for (int i = 1; i <= n; i++) {
            if (!(cont >> a[i])) {
                cout << "Wrong Answer\n";
                return 0;
            }
            if (abs(a[i]) > 1000000000LL) {
                cout << "Wrong Answer\n";
                return 0;
            }
        }

        for (auto [o, l, r] : cons) {
            long long s = a[l] + a[r];
            if (o == 1) {
                if (s < 0) {
                    cout << "Wrong Answer\n";
                    return 0;
                }
            } else {
                if (s >= 0) {
                    cout << "Wrong Answer\n";
                    return 0;
                }
            }
        }
    }

    cout << "Accepted\n";
    return 0;
}