#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>
#include <deque>
#include <tuple>

using namespace std;

// --- Constants & Globals ---
const int MAX_OPS = 200000; // Limit roughly based on 2N^3 usually
int N;
vector<vector<int>> grid;
// Stores coordinates for each card value: card_pos[val] = {{r1, c1}, {r2, c2}}
vector<vector<pair<int, int>>> card_pos;

// Time limit for the SA (in seconds)
const double TIME_LIMIT = 1.8; 

// --- Random Number Generation ---
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// --- Helper Structs ---
struct State {
    vector<int> perm; // The order in which we clear numbers
    int cost;         // Estimated Manhattan cost
};

// --- Distance Calculation ---
// Simple Manhattan distance
int dist(pair<int, int> a, pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

// --- Evaluation Function ---
// Calculates the total travel distance to clear cards in the order specified by 'perm'
// We try both orders: (Start -> A -> B) vs (Start -> B -> A) and pick the shorter one.
int evaluate(const vector<int>& perm) {
    int total_cost = 0;
    pair<int, int> cur = {0, 0};

    for (int val : perm) {
        pair<int, int> p1 = card_pos[val][0];
        pair<int, int> p2 = card_pos[val][1];

        // Cost option 1: Go to p1 then p2
        int c1 = dist(cur, p1) + dist(p1, p2);
        
        // Cost option 2: Go to p2 then p1
        int c2 = dist(cur, p2) + dist(p2, p1);

        if (c1 < c2) {
            total_cost += c1;
            cur = p2;
        } else {
            total_cost += c2;
            cur = p1;
        }
    }
    return total_cost;
}

// --- Simulated Annealing ---
vector<int> run_annealing() {
    // 1. Initial State: Random permutation
    int num_pairs = (N * N) / 2;
    vector<int> current_perm(num_pairs);
    iota(current_perm.begin(), current_perm.end(), 0);
    shuffle(current_perm.begin(), current_perm.end(), rng);

    int current_cost = evaluate(current_perm);
    
    vector<int> best_perm = current_perm;
    int best_cost = current_cost;

    // 2. Setup Timing & Temperature
    auto start_time = chrono::steady_clock::now();
    double start_temp = 100.0;
    double end_temp = 0.1;
    
    int iter = 0;
    
    while (true) {
        iter++;
        // Check time every 1024 iterations to minimize overhead
        if ((iter & 1023) == 0) {
            auto now = chrono::steady_clock::now();
            double elapsed = chrono::duration<double>(now - start_time).count();
            if (elapsed > TIME_LIMIT) break;
        }

        // Calculate current temperature based on time
        auto now = chrono::steady_clock::now();
        double elapsed = chrono::duration<double>(now - start_time).count();
        double progress = elapsed / TIME_LIMIT;
        double temp = start_temp + (end_temp - start_temp) * progress;

        // 3. Generate Neighbor: Swap two random elements
        int idx1 = rng() % num_pairs;
        int idx2 = rng() % num_pairs;
        if (idx1 == idx2) continue;

        swap(current_perm[idx1], current_perm[idx2]);
        
        // 4. Calculate New Cost (Delta update could be faster, but full eval is okay for N<=50)
        int new_cost = evaluate(current_perm);
        int delta = new_cost - current_cost;

        // 5. Acceptance Criteria
        if (delta < 0 || exp(-delta / temp) > uniform_real_distribution<>(0, 1)(rng)) {
            // Accept
            current_cost = new_cost;
            if (current_cost < best_cost) {
                best_cost = current_cost;
                best_perm = current_perm;
            }
        } else {
            // Reject: Swap back
            swap(current_perm[idx1], current_perm[idx2]);
        }
    }

    return best_perm;
}

// --- Output Generator (Actual Solver) ---
// Uses BFS to navigate grid based on the optimized permutation
string output_ops;
void add_move(char c) { output_ops += c; }
// CORRECTED BFS
string bfs(pair<int, int> start, pair<int, int> target, const vector<vector<int>>& current_grid) {
    if (start == target) return "";
    
    int n = current_grid.size();
    vector<vector<int>> dist_map(n, vector<int>(n, -1));
    vector<vector<char>> parent_move(n, vector<char>(n, 0));
    vector<vector<pair<int,int>>> parent_pos(n, vector<pair<int,int>>(n, {-1,-1}));
    
    deque<pair<int, int>> q;
    q.push_back(start);
    dist_map[start.first][start.second] = 0;
    
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    char move_char[] = {'U', 'D', 'L', 'R'};

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop_front();

        if (r == target.first && c == target.second) break;

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            // FIXED: We only check boundaries. We DO NOT check current_grid[nr][nc].
            // You are allowed to walk over existing cards.
            if (nr >= 0 && nr < n && nc >= 0 && nc < n && dist_map[nr][nc] == -1) {
                dist_map[nr][nc] = dist_map[r][c] + 1;
                parent_move[nr][nc] = move_char[i];
                parent_pos[nr][nc] = {r, c};
                q.push_back({nr, nc});
            }
        }
    }

    if (dist_map[target.first][target.second] == -1) return "X"; 

    string path = "";
    pair<int, int> cur = target;
    while (cur != start) {
        path += parent_move[cur.first][cur.second];
        cur = parent_pos[cur.first][cur.second];
    }
    reverse(path.begin(), path.end());
    return path;
}

void solve() {
    // Run Simulated Annealing to get optimized order
    vector<int> best_perm = run_annealing();

    // Reconstruct moves based on best_perm
    // NOTE: This uses BFS to account for obstacles. If path is blocked, 
    // a real competitive solution would need to move obstacles. 
    // Here we assume the SA found a "clean enough" path or we force moves.
    
    pair<int, int> cur = {0, 0};
    vector<vector<int>> sim_grid = grid; // Simulation grid

    for (int val : best_perm) {
        pair<int, int> p1 = card_pos[val][0];
        pair<int, int> p2 = card_pos[val][1];

        // Decide which instance to visit first based on simple distance
        int d1 = dist(cur, p1) + dist(p1, p2);
        int d2 = dist(cur, p2) + dist(p2, p1);
        
        pair<int, int> first = (d1 < d2) ? p1 : p2;
        pair<int, int> second = (d1 < d2) ? p2 : p1;

        // Move to first
        string path1 = bfs(cur, first, sim_grid);
        // Fallback: if BFS fails (blocked), use simple moves (Manhattan) 
        // In a real contest, you'd pick up the blocking card.
        if (path1 == "X") { /* Simple walk logic would go here */ } 
        
        // Output moves to first
        for(char c : path1) add_move(c);
        add_move('I'); // Pick up (Operation 2)
        sim_grid[first.first][first.second] = -1; // Remove from grid logic
        cur = first;

        // Move to second
        string path2 = bfs(cur, second, sim_grid);
        for(char c : path2) add_move(c);
        add_move('I'); // Pick up (Operation 2)
        sim_grid[second.first][second.second] = -1;
        cur = second;
        
        // At this point, stack has [val, val]. They cancel out.
    }
    
    cout << output_ops << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> N)) return 0;

    grid.resize(N, vector<int>(N));
    card_pos.resize((N * N) / 2);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
            card_pos[grid[i][j]].push_back({i, j});
        }
    }

    solve();

    return 0;
}