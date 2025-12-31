#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#define dbg(x...) cerr << "[" << #x << "]=["; _print(x)
#else
#define dbg(x...) 
#endif

#define inf (long long)1e18
#define endl "\n"
#define int long long
#define x first
#define y second
#define all(x) (x).begin(),(x).end() 
#define ld long double
struct randdom : std::mt19937
{
    using std::mt19937::mt19937;
    using std::mt19937::operator();
    static int64_t gen_seed()
    {
        return std::chrono::steady_clock::now().time_since_epoch().count();
    }
    randdom() : std::mt19937(gen_seed()) {}
    template <class Int>
    auto operator()(Int a, Int b)
        -> std::enable_if_t<std::is_integral_v<Int>, Int>
    {
        return std::uniform_int_distribution<Int>(a, b)(*this);
    }
    template <class Int>
    auto operator()(Int a) -> std::enable_if_t<std::is_integral_v<Int>, Int>
    {
        return std::uniform_int_distribution<Int>(0, a - 1)(*this);
    }
    template <class Real>
    auto operator()(Real a, Real b)
        -> std::enable_if_t<std::is_floating_point_v<Real>, Real>
    {
        return std::uniform_real_distribution<Real>(a, b)(*this);
    }
};
inline double get_time() 
{
    static auto start_time = chrono::steady_clock::now();
    auto now = chrono::steady_clock::now();
    return chrono::duration<double>(now - start_time).count();
}
struct rect
{
    int x1,y1,x2,y2;
};  
void __print(rect r)
{
    cerr<<"{"<<r.x1<<","<<r.y1<<","<<r.x2<<","<<r.y2<<"}";
}
void solve()
{   
    int n;
    cin>>n;
    int W=10000;
    struct a
    {
        int x,y,ar;
    };
    vector<a>ar(n);
    for(int i=0;i<n;i++)
    {
        cin>>ar[i].x>>ar[i].y>>ar[i].ar;
    }
    
    vector<rect>state(n);
    auto valid=[&](int idx=-1)->bool
    {
        for(int i=0;i<n;i++)
        {
            if(idx>=0)
            {
                i=idx;
            }
            auto r1=state[i];
            for(int j=0;j<n;j++)
            {
                if(j==i) continue;
                auto r2=state[j];
                if((min(r1.x2, r2.x2) > max(r1.x1, r2.x1)) && (min(r1.y2, r2.y2) > max(r1.y1, r2.y1)))
                {
                    return 0;
                }
            }
            if(min(r1.x1,r1.x2)<0 || max(r1.x1,r1.x2)>W) return 0;
            if(min(r1.y1,r1.y2)<0 || max(r1.y1,r1.y2)>W) return 0;
            if(r1.x1 >= r1.x2 || r1.y1 >= r1.y2) return 0; 
            if(idx>=0)
            {
                break;
            }
        }
        return 1;
    };
    ld score=0;
    auto scorer=[&](int idx=-1)->ld
    {
        ld sco=0;
        for(int i=0;i<n;i++)
        {
            if(idx>=0)
            {
                i=idx;
            }
            auto [x,y,area]=ar[i];
            auto r=state[i];
            if(!(r.x1<=x && x<r.x2 && r.y1<=y && y<r.y2 )){}
            else
            {
                ld given=(r.x2-r.x1)*(r.y2-r.y1);
                ld s=min(given,(ld)area)/max(given,(ld)area);
                sco+=(ld)1-((ld)1-s)*((ld)1-s);
            }
            if(idx>=0)
            {
                break;
            }
        }
        if(idx>=0)
        {
            return sco;
        }
        return sco/(ld)n;
    };      
    for(int i=0;i<n;i++)
    {
        auto [x,y,_]=ar[i];
        state[i]={x,y,x+1,y+1};
    }
    score=scorer();
    auto print=[&]()
    {
        for(auto [x1,y1,x2,y2]:state)
        {
            cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
        }
    };
    ld tl=4.9;
    ld T0 = 2000.0;
    ld T1 = 600.0;
    randdom rng;
    while(true)
    {
        ld time=get_time()/tl;
        if(time>=1) break;
        ld temp=pow(T0,1.0-time)*pow(T1,time);
        // first select a randdom rectange
        int idx=rng(n);
        // expansion or translation
        int choice=(rng(2))?1:-1;
        ld oldcontri=scorer(idx);
        auto oldr=state[idx];
        auto& r=state[idx];
            // select dir
        int dir=rng(4);
        int amt=rng(1,100);
        if(dir==0)
        {
            // left 
            r.x1=r.x1-amt*choice;
        }
        else if(dir==1)
        {
            // right
            r.x2=r.x2+amt*choice;

        }
        else if(dir==2)
        {
            // bottom
            r.y1=r.y1-amt*choice;
        }
        else
        {
            // top
            r.y2=r.y2+amt*choice;
        }
        // dbg(choice,amt,dir,oldr,r,valid(idx));
        if(valid(idx))
        {
            ld nscore=(score*n-oldcontri+scorer(idx))/n;
            ld diff=nscore-score;
            diff/=temp;
            diff=exp(diff);
            ld prob=rng(0.0,1.0);
            if(diff>=0 || prob<=diff)
            {
                score=nscore;
            }
            else
            {
                state[idx]=oldr;
            }
        }
        else
        {
            state[idx]=oldr;
        }
    }
    print();
}   
int32_t main()      
{   
    #ifdef LOCAL1
        auto begin = std::chrono::high_resolution_clock::now();
    #endif
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    solve();
    #ifdef LOCAL1
        auto end = std::chrono::high_resolution_clock::now();
        cerr << setprecision(4) << fixed;
        cerr << "-> " << std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count() << " sec" << endl;
    #endif
    return 0;
}