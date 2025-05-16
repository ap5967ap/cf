#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        int n;
        int64 k;
        cin >> n >> k;
        vector<int64>a(n);
        for(auto &x:a) cin >> x;

        int64 mn = *min_element(a.begin(), a.end());
        int64 mx = *max_element(a.begin(), a.end());
        int64 sum = accumulate(a.begin(), a.end(), 0LL);

        // Case 1: no safe first move
        if (mx - mn > k || k == 0) {
            cout << "Jerry\n";
        }
        else {
            // Otherwise first player wins iff total apples is odd
            cout << ((sum & 1) ? "Tom\n" : "Jerry\n");
        }
    }

    return 0;
}
