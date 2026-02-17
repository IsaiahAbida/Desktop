#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>

using namespace std;

// Recursively build optimal parenthesization
string build_parens(const vector<vector<int>>& split, int i, int j) {
    if (i == j) {
        return "A" + to_string(i);
    }
    int k = split[i][j];
    return "(" + build_parens(split, i, k) + build_parens(split, k + 1, j) + ")";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        if (n < 1) continue;

        // p array holds matrix dimensions
        vector<long long> p(n + 1);
        for (int i = 0; i <= n; ++i) cin >> p[i];

        // DP table for minimum cost
        const long long INF = (1LL << 62);
        vector<vector<long long>> m(n, vector<long long>(n, 0));
        vector<vector<int>> split(n, vector<int>(n, -1));

        // Bottom-up DP: len = chain length
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                m[i][j] = INF;

                for (int k = i; k < j; ++k) {
                    long long cost = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                    if (cost < m[i][j]) {
                        m[i][j] = cost;
                        split[i][j] = k;
                    }
                }
            }
        }

        // Output results
        if (n == 1) {
            cout << 0 << "\n";
            cout << "A0" << "\n";
        } else {
            cout << m[0][n - 1] << "\n";
            cout << build_parens(split, 0, n - 1) << "\n";
        }
    }

    return 0;
}
