#include <bits/stdc++.h>

using namespace std;

#define int long long 

#define piii pair<int, pair<int,int>>



int32_t  main() {

	// your code goes here

	int t; cin>>t; while(t--)

	{

	    int n, m, s, t; cin>>n>>m>>s>>t;

	    

	    vector<pair<int,int>>adj[n+1][26]; // here we have to create a adjanency list which is defind as below

	    // adj is a 2d matrix with n+1 rows and 26 columns and each element of matrix is a vector of pairs 

	    

	    for(int i = 0; i<m; i++)

	    {

	        int u, v, wt ; cin>>u>>v>>wt;

	        char c; cin>>c;

	                                            // taking the inputs 

	        adj[u][c - 'a'].push_back({v,wt});

	        adj[v][c - 'a'].push_back({u,wt});

	    }

	    

	    vector<vector<int>>dist(n+1, vector<int>(n+1, 1e18));

	    // dist[i][j] --> indicates cost from travelling from s to i and from j to t in a palindromic path 

	    // thus a path is completed if (i == j ) OR i and j are connected 

	    

	    int ans = 1e18;

	    

	    dist[s][t] = 0; // base case 

	    

	    priority_queue<piii, vector<piii>, greater<piii>>pq; // using a priority queue and solving it in a dijkstra manner 

	    

	    pq.push({0, {s, t}}); // initally cost is 0 and start is at s and end is at t

	    

	    while(!pq.empty())

	    {

	        int wt = pq.top().first;

	        int start = pq.top().second.first;

	        int end = pq.top().second.second;

	        

	        pq.pop();

	        

	        if(dist[start][end] < wt)  continue; 

	        

	        if(start == end)

	        {

	            ans = min(ans, wt);     // checking for path completion 

	        }

	        

	        for(int i = 0; i<26; i++) // palindromic walk can occur iff both have same character in their next traversal 

	        {

	            for(auto it: adj[start][i])

	            {

	                if(it.first == end) // path completion checking if start and end are connected 

	                {

	                    ans = min(ans, wt+ it.second);

	                }

	                

	                for(auto p:adj[end][i])

	                {

	                    int n1 = it.first; int n2 = p.first;

	                    int wt1 = it.second, wt2 = p.second;

	                    

	                    if(dist[n1][n2] > wt2 + wt1 + wt)

	                    {

	                        dist[n1][n2] = wt  + wt1 + wt2;

	                        pq.push({dist[n1][n2], {n1, n2}}); // updating the distance array and pushing it into pq 

	                    }

	                    

	                    

	                }

	            }

	        }

	        

	    }

	        ans == 1e18 ? ans = -1: ans; // checking if ans doesn't exist 

	        cout<<ans<<endl;

	}

}

