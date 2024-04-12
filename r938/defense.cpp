#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include <cmath>
#include <set>
using namespace std;

#define all(a) (a).begin(), (a).end()

typedef long long ll;
typedef vector<vector<int>> vvi;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef unordered_map<long long, int> umlli;
typedef unordered_map<int, int> umii;
typedef unsigned long long ull;
typedef map<pair<int, int>, int> mpii;

const int R = 12;
const int NINF = -2e9;

vector<int>cost (R);

void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<bool>> grid(n, vector<bool>(m, 0));
    for (int i = 0; i < n; ++i){
        string s;
        cin >> s;
        for (int j = 0; j < m; ++j){
            grid[i][j] = (s[j] == '#');
        }
    }

    vector<pair<int, int>> tower(k);
    vector<int> power(k);
    for (int i = 0; i < k; ++i){
        cin >> tower[i].first >> tower[i].second >> power[i];
        --tower[i].first;
        --tower[i].second;
    }
    // end of taking input

    auto benefit = [&](int t_idx, int r) -> int {
        int tx = tower[t_idx].first;
        int ty = tower[t_idx].second;
        int total = 0;
        for (int i = tx - r; i <= tx + r; ++i){
            if (i < 0) continue;
            if (i >= n) continue;
            for (int j = ty - r; j <= ty + r; ++j){
                if (j < 0) continue;
                if (j >= m) continue;
                if ((j - ty) * (j - ty) + (i - tx) * (i - tx) > r * r) continue;
                if (grid[i][j]) total += power[t_idx];
            }
        }
        return max(total - cost[r - 1], 0);
    };

    vector<vector<int>> precal(k, vi(R));
    for (int i = 0; i < k; ++i){
        for (int j = 0; j < R; ++j){
            precal[i][j] = benefit(i, j);
        }
    }
    // end of precal

    vector<vector<int>> dp(k + 1, vector<int>(1 << R, NINF));
    dp[0][0] = 0;
    for (int i = 1; i <= k; ++i){
        int t_idx = i - 1;
        for (int mask = 0; mask < (1 << R); ++mask){
            dp[i][mask] = dp[i - 1][mask];
            for (int r = 1; r <= R; ++r){
                if (!(mask & (1 << (r - 1)))) {
                    continue;
                }
                dp[i][mask] = max(dp[i][mask],
                    dp[i - 1][mask ^ (1 << (r - 1))] + precal[t_idx][r - 1]
                );
            }
        }
    }

    int maxx = 0;
    for (int i = 0; i < (1 << R); ++i){
        maxx = max(maxx, dp[k][i]);
    }
    cout << maxx << "\n";
}

int main(){
    int t;
    cin >> t;

    int c = 1;
    for (int i = 0; i < R; ++i){
        c *= 3;
        cost[i] = c;
    }

    while (t--){
        solve();
    }
}