#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <deque>

using namespace std;

// Structure to hold input data
struct Input {
    int N;
    vector<vector<int>> grid;
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: scorer input.txt output.txt\n";
        return 1;
    }

    ifstream fin(argv[1]);
    ifstream fout(argv[2]);

    if (!fin.is_open() || !fout.is_open()) {
        cerr << "Error: Could not open input or output file.\n";
        return 1;
    }

    int N;
    fin >> N;

    Input input;
    input.N = N;
    input.grid.resize(N, vector<int>(N));

    // Read the N x N grid
    // -1 can represent empty if needed, but input 0..N^2/2-1 are valid cards.
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            fin >> input.grid[i][j];
        }
    }

    // Read the output moves
    string moves;
    fout >> moves;

    // Simulation variables
    int r = 0; // Current row
    int c = 0; // Current col
    deque<int> deck; // Your deck (stack behavior)
    vector<vector<int>> current_grid = input.grid; // Mutable grid
    
    long long K = moves.length();
    long long max_ops = 2LL * N * N * N;
    bool is_valid = true;

    // Validate operation limit
    if (K > max_ops) {
        is_valid = false;
        cerr << "Invalid: Exceeded operation limit (" << K << " > " << max_ops << ")\n";
    }

    // Process moves
    if (is_valid) {
        for (char op : moves) {
            if (op == 'U') {
                if (r > 0) r--;
                else is_valid = false;
            } else if (op == 'D') {
                if (r < N - 1) r++;
                else is_valid = false;
            } else if (op == 'L') {
                if (c > 0) c--;
                else is_valid = false;
            } else if (op == 'R') {
                if (c < N - 1) c++;
                else is_valid = false;
            } else if (op == 'I') {
                // Interaction logic
                if (current_grid[r][c] != -1) {
                    // 1. Pick up card from grid
                    int card = current_grid[r][c];
                    deck.push_back(card);
                    current_grid[r][c] = -1; // -1 represents empty cell

                    // 2. Check for matching pair on top of deck
                    if (deck.size() >= 2) {
                        int top = deck.back();
                        int second = deck[deck.size() - 2];
                        if (top == second) {
                            deck.pop_back();
                            deck.pop_back();
                        }
                    }
                } else {
                    // 3. Place card from deck to grid
                    if (!deck.empty()) {
                        int card = deck.back();
                        deck.pop_back();
                        current_grid[r][c] = card;
                    } else {
                        is_valid = false; // Cannot place from empty deck
                    }
                }
            } else {
                is_valid = false; // Invalid character
            }

            if (!is_valid) break;
        }
    }

    // Calculate X (Remaining cards on grid + in deck)
    int X = deck.size();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (current_grid[i][j] != -1) {
                X++;
            }
        }
    }

    // Final Scoring
    long long score = 0;
    if (!is_valid) {
        score = 0; // Or minimal score for invalid solutions
    } else {
        if (X == 0) {
            score = (long long)N * N + max_ops - K;
        } else {
            score = (long long)N * N - X;
        }
    }

    cout << score << endl;

    return 0;
}