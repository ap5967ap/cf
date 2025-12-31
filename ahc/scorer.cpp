#include <bits/stdc++.h>
using namespace std;
#include <bits/stdc++.h>
using namespace std;

static const long long W = 10000;

struct Input {
    vector<pair<long long, long long>> ps;
    vector<long long> size;
};

struct Rect {
    long long x1, x2, y1, y2;

    long long area() const {
        return (x2 - x1) * (y2 - y1);
    }
};

bool intersect(const Rect& r1, const Rect& r2) {
    return ((min(r1.x2, r2.x2) > max(r1.x1, r2.x1)) && (min(r1.y2, r2.y2) > max(r1.y1, r2.y1)));
}

long long score(const Input& input, const vector<Rect>& out) {
    int n = input.ps.size();
    double total_score = 0.0;

    for (int i = 0; i < n; i++) {
        const Rect& r = out[i];

        // Bounds check
        if (r.x1 < 0 || r.x2 > W || r.y1 < 0 || r.y2 > W) {
            cerr << "rectangle " << i << " is out of range\n";
            return 0;
        }

        // Positive area check
        if (r.x1 >= r.x2 || r.y1 >= r.y2) {
            cerr << "rectangle " << i << " does not have positive area\n";
            return 0;
        }

        // Point containment check
        auto [px, py] = input.ps[i];
        if (!(r.x1 <= px && px < r.x2 &&
              r.y1 <= py && py < r.y2)) {
            // cerr << "rectangle " << i << " does not contain point " << i << "\n";
            continue;
        }

        // Overlap check
        for (int j = 0; j < i; j++) {
            if (intersect(r, out[j])) {
                cerr << "rectangles " << j << " and " << i << " overlap\n";
                return 0;
            }
        }

        long long rect_area = r.area();
        long long target_area = input.size[i];

        double s = (double)min(rect_area, target_area) /
                   (double)max(rect_area, target_area);

        total_score += 1.0 - (1.0 - s) * (1.0 - s);
    }

    return (long long) llround(1e9 * total_score / n);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: scorer input.txt output.txt\n";
        return 1;
    }

    ifstream fin(argv[1]);
    ifstream fout(argv[2]);

    int N;
    fin >> N;

    Input input;
    input.ps.resize(N);
    input.size.resize(N);

    for (int i = 0; i < N; i++) {
        fin >> input.ps[i].first >> input.ps[i].second >> input.size[i];
    }

    vector<Rect> out(N);
    for (int i = 0; i < N; i++) {
        fout >> out[i].x1 >> out[i].y1 >> out[i].x2 >> out[i].y2;
    }

    cout << score(input, out) << "\n";
}
