#include<bits/stdc++.h>
using namespace std;

struct WaveletTree {
    int lo, hi;
    WaveletTree *l, *r;
    vector<int> b; // b[i] = #elements going to left in prefix [1..i]

// constructor: build from array [from, to)
    WaveletTree(vector<int>::iterator from, vector<int>::iterator to, int x, int y) {
        lo = x, hi = y;
        if (from >= to) return;
        if (lo == hi) return;

        int mid = (lo + hi) >> 1;
        auto f = [mid](int x) { return x <= mid; };

        b.reserve(to - from + 1);
        b.push_back(0);

        for (auto it = from; it != to; it++)
            b.push_back(b.back() + f(*it));

        auto pivot = stable_partition(from, to, f);

        l = new WaveletTree(from, pivot, lo, mid);
        r = new WaveletTree(pivot, to, mid + 1, hi);
    }

    // kth smallest in [l, r]
    int kth(int lq, int rq, int k) {
        if (lq > rq) return 0;
        if (lo == hi) return lo;

        int inLeft = b[rq] - b[lq - 1];
        if (k <= inLeft)
            return l->kth(b[lq - 1] + 1, b[rq], k);
        return r->kth(lq - b[lq - 1], rq - b[rq], k - inLeft);
    }

    // count of elements <= k in [l, r]
    int LTE(int lq, int rq, int k) {
        if (lq > rq || k < lo) return 0;
        if (hi <= k) return rq - lq + 1;

        return l->LTE(b[lq - 1] + 1, b[rq], k) +
               r->LTE(lq - b[lq - 1], rq - b[rq], k);
    }

    // count of elements == k
    int countEqual(int lq, int rq, int k) {
        if (lq > rq || k < lo || k > hi) return 0;
        if (lo == hi) return rq - lq + 1;

        int mid = (lo + hi) >> 1;
        if (k <= mid)
            return l->countEqual(b[lq - 1] + 1, b[rq], k);
        return r->countEqual(lq - b[lq - 1], rq - b[rq], k);
    }

    // count in range [x, y]
    int rangeFreq(int lq, int rq, int x, int y) {
        return LTE(lq, rq, y) - LTE(lq, rq, x - 1);
    }
};

//! require 1-based