#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;

#ifdef LOCAL
#include "codes/debug.h"
#else
#define debug(...)
#endif

using ll = int64_t;
#define sz(x) ((int)(x).size())
const char nl = '\n';

void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> c, p;
  for (int i = 1, x; i < n; ++i) {
    cin >> x;
    if (x > k)
      c.push_back (x);
  }
  for (int i = 0, x; i < m; ++i) {
    cin >> x;
    if (x > k)
      p.push_back (x);
  }

  sort (p.begin (), p.end ());
  sort (c.begin (), c.end ());

  int s = sz (p);
  vector<int> v (s, 0);
  int j = 0;
  for (int i = 0; i < s; ++i) {
    while (j < sz (c) and c[j] < p[i])
      ++j;
    v[i] = sz (c) - j;
  }

  for (int i = 1; i <= m; ++i) {
    ll ans = m / i;
    int rem = m % i;

    for (int j = rem; j < s; j += i)
      ans += 1ll * v[j];

    cout << ans << ' ';
  }

  cout << nl;
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t = 1;
  cin >> t;
  for (int i = 1; i <= t; i++)
    solve();
  return 0;
}