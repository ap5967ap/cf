import sys
sys.setrecursionlimit(10**7)
from functools import lru_cache

def G(h, w):
    # worst‐case #turns to reduce an h×w grid to 1×1
    if h == 1 and w == 1:
        return 0
    # if we cut rows, worst‐case new height = floor((h+1)/2)
    cut_rows = G((h+1)//2, w)
    # if we cut cols, worst‐case new width  = floor((w+1)/2)
    cut_cols = G(h, (w+1)//2)
    return 1 + min(cut_rows, cut_cols)

def turns(n, m, a, b):
    # if already 1×1, zero turns
    if n == 1 and m == 1:
        return 0
    # compute the “smaller‐side” distances
    h_prime = min(a, n - a + 1)
    w_prime = min(b, m - b + 1)
    # first cut (1 turn), then the worst‐case for the smaller of the two options
    return 1 + min(G(h_prime, m), G(n, w_prime))

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n, m, a, b = map(int, input().split())
    print(turns(n, m, a, b))
