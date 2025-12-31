void segmented_sieve()
{

    int l,r;
    cin>>l>>r;

    int lim = sqrt(r)+1;

    vi base_primes;
    vector<bool> is_prime(lim+1,1);
    for(int i=2;i*i<=r;i++){
        if(!is_prime[i]) continue; 
        for(int j = i*i;j<=lim;j+=i) {
            // dbg(j);
            is_prime[j] = false;
        }
    }

    for(int i = 2;i*i<=r;i++) if(is_prime[i]) base_primes.pb(i);

    vi is_prime_seg(r-l+1,1);
    for(int p : base_primes){
        int st = ((l+p-1)/p) * p;
        for(int j = st;j<=r;j+=p) is_prime_seg[j-l] = p;
    }
    if(l==1) is_prime_seg[0] = false;
    // is_prime_seg[i] = true ==> l+i is prime
}           

