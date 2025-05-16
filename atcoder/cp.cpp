#include <iostream>
#include <vector>
#include <algorithm>
#include <atcoder/convolution>  // AtCoder library header for convolution_ll

using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // Read the array and find maximum value (M)
    vector<int> arr(n);
    int M = 0;
    for (int i = 0; i < n; i++){
        cin >> arr[i];
        M = max(M, arr[i]);
    }

    // Build frequency array: F[v] = # of times v appears (v in [0, M])
    vector<ll> freq(M + 1, 0);
    for (int i = 0; i < n; i++){
        freq[arr[i]]++;
    }

    // Build the reversed frequency array: rev[i] = freq[M - i]
    vector<ll> freq_rev = freq;
    reverse(freq_rev.begin(), freq_rev.end());

    // Compute convolution using AtCoder's convolution_ll.
    // The convolution calculates c[k] = sum_{i+j=k} freq[i]*freq_rev[j].
    vector<ll> conv = atcoder::convolution_ll(freq, freq_rev);
    // conv will have size (M+1 + M+1 - 1) = 2*M + 1.

    // For differences d from -M to M, we have:
    //    f[d] = conv[M - d]
    // because index M in conv corresponds to difference 0.
    for (int d = -M; d <= M; d++){
        ll count = conv[M - d];
        cout << "f[" << d << "] = " << count << "\n";
    }

    return 0;
}
