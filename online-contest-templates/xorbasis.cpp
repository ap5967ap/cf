struct xor_basis{
    static constexpr int MAX_BITS = 30;
    int basis[MAX_BITS];
    int n; 
 
    xor_basis() : n(0) {}; 
    
    bool add(int num){
        if(n == MAX_BITS) return false; 
        for(int i = 0; i < n; ++i) num = min(num, num ^ basis[i]);
        if(num == 0) return false; 
        for(int i = 0; i < n; ++i) basis[i] = min(basis[i], basis[i] ^ num); 
        basis[n++] = num; 
        for(int i = n - 1; i > 0 && basis[i] < basis[i - 1]; i--) swap(basis[i], basis[i - 1]); 
        return true;
    }
 
    //index of num if we sort all numbers possible to make
    int order_of_key(int num){
        int res = 0;
        for(int i = n - 1; i >= 0; i--){
            int d = min(num, num ^ basis[i]); 
            if(num > d) res += (1 << i), num = d; 
        }
        return res; 
    }
 
    //number at idx if we sort all numbers possible to make
    int find_by_order(int idx){
        int res = 0; 
        for(int i = n - 1; i>= 0;i--){
            if(idx >= (1 << i)){
                idx -= (1 << i); 
                res = max(res, res ^ basis[i]); 
            }
        }
        return res;
    } 
    int min_xor(int start = 0){
        for(int i = 0; i < n; ++i) start = min(start, start ^ basis[i]); 
        return start; 
    }
    int max_xor(int start = 0){
        for(int i = 0; i < n; ++i) start = max(start, start ^ basis[i]); 
        return start; 
    }
    bool contains(int num) { return min_xor(num) == 0; }
    int size() { return n;}
};