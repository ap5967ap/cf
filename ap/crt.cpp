#include<bits/stdc++.h>
using namespace std;

// Extended Euclidean Algorithm
int extended_gcd(int a, int b, int &x, int &y) 
{
    if (b == 0) { x = 1; y = 0; return a; }
    int x1, y1;
    int g = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// Modular inverse using extended Euclid
int modinv(int a, int m) 
{
    int x, y;
    int g = extended_gcd(a, m, x, y);
    if (g != 1) return -1; // Inverse doesn't exist
    return (x % m + m) % m;
}

// Chinese Remainder Theorem solver
int crt(vector<int> &a,  vector<int> &m) 
{
    int M = 1;
    for (int mi : m) M *= mi;

    int result = 0;
    for (int i = 0; i < a.size(); ++i) {
        int Mi = M / m[i];
        int inv = modinv(Mi, m[i]);
        result = (result + a[i] * Mi % M * inv % M) % M;
    }

    return (result % M + M) % M; // Ensure positive
}
