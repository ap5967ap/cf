#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y, z, id, w = 1;
    long long ans = 0;
};

struct BIT {
    int n;
    vector<int> f;
    
    BIT(int n = 0) : n(n), f(n + 1, 0) {}
    
    void add(int i, int v) {
        for (; i <= n; i += i & -i) {
            f[i] += v;
        }
    }
    
    int sum(int i) {
        int r = 0;
        for (; i; i -= i & -i) {
            r += f[i];
        }
        return r;
    }
};

void cdq(vector<Point>& a, int l, int r, BIT &bit) {
    if (r - l <= 1) return;
    
    int m = l + (r - l) / 2;
    cdq(a, l, m, bit);
    cdq(a, m, r, bit);

    // Two-pointer logic for counting answers
    int j = l;
    for (int i = m; i < r; i++) {
        while (j < m && a[j].y <= a[i].y) {
            bit.add(a[j].z, a[j].w);
            j++;
        }
        a[i].ans += bit.sum(a[i].z);
    }

    // Clean up the BIT
    for (int k = l; k < j; k++) {
        bit.add(a[k].z, -a[k].w);
    }


    // inplace_merge(a.begin() + l, a.begin() + m, a.begin() + r, [](const Point &p, const Point &q) {
    //     return p.y < q.y || (p.y == q.y && p.z < q.z);
    // });
    
    vector<Point> temp;
    temp.reserve(r - l); // Pre-allocate to prevent reallocation overhead
    
    int p1 = l, p2 = m;
    while (p1 < m && p2 < r) {
        // Sort primarily by y, and secondarily by z
        if (a[p1].y < a[p2].y || (a[p1].y == a[p2].y && a[p1].z < a[p2].z)) {
            temp.push_back(a[p1++]);
        } else {
            temp.push_back(a[p2++]);
        }
    }
    
    // Append any remaining elements from either half
    while (p1 < m) temp.push_back(a[p1++]);
    while (p2 < r) temp.push_back(a[p2++]);
    
    // Copy the merged sorted elements back into the original array
    for (int i = 0; i < (int)temp.size(); i++) {
        a[l + i] = temp[i];
    }
}