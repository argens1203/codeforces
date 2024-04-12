#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include <cmath>
#include <set>
using namespace std;

typedef long long ll;
typedef vector<vector<int>> vvi;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef unordered_map<long long, int> umlli;
typedef unordered_map<int, int> umii;
typedef unsigned long long ull;
typedef map<pair<int, int>, int> mpii;

// 1 use unsigned long long
// 2 optimize NcR
// 3 make sure sum up before averaging to prevent rounding error

umii intoMap(vi v){
    umii ma;
    for (auto& i : v){
        if (ma.find(i) == ma.end()){
            ma[i] = 1;
        } else {
            ma[i]++;
        }
    }
    return ma;
}

unsigned long long fac(int x, int start = 1){
    unsigned long long total = 1;
    for (int i = start; i <= x; i++){
        total *= i;
    }
    return total;
}

unsigned long long c(int n, int r){
    if (r < n / 2) return c (n, n - r);
    return fac(n, r + 1) / fac(n - r);
}

long long avg(int n, int m){
    int total = c(n, m);

    unsigned long long digit = (unsigned long long) total * m / n;
    unsigned long long sum = 0;
    for (int i = 0; i < n; i++){
        sum += (unsigned long long) (digit << i);
    }
    unsigned long long a = sum / total;
    return a;
}

mpii spread(mpii mapp, int w, int h){
    mpii minusOne;
    for (auto itr : mapp){
        int x = itr.first.first;
        int y = itr.first.second;
        int value = itr.second;
        if (x >= 2) minusOne[{x - 1, y}] = max(minusOne[{x - 1,y}], value );
        if (x <= w - 1) minusOne[{x + 1, y}] = max(minusOne[{x + 1,y}], value);
        minusOne[{x, y}] = max(minusOne[{x,y}], value);
        if (y >= 2) minusOne[{x, y - 1}] = max(minusOne[{x,y - 1}], value);
        if (y <= h - 1) minusOne[{x, y + 1}] = max(minusOne[{x,y + 1}], value);
    }
    return minusOne;
}

ll comb(ll n, int r){
    return n * (n - 1) / 2;
}

int gcd(int a, int b){
    if (b == 0) return a;
    if (a == b) return a;
    if (a > b) return gcd(b, a % b);
    return gcd(b, a);
}

void solve(){
    int n, m;
    cin >> n >> m;
    vvi num (n, vi(m));

    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> num[i][j];

    int max_cand = gcd(num[0][0], num[n - 1][m - 1]);
    vector<vector<bool>> grid (n, vector<bool> (m, false));
    auto works = [&](int cand) -> bool {
        for (int i = 0; i < n; ++i) grid[i].assign(m, 0);
        for (int i = n - 1; i >= 0; --i){
            for (int j = m - 1; j >= 0; --j){
                if ((num[i][j] % cand) != 0){
                    continue;
                }
                if (j + 1 < m && grid[i][j + 1]) {
                    grid[i][j] = true;
                    continue;
                }
                if (i + 1 < n && grid[i + 1][j]){
                    grid[i][j] = true;
                    continue;
                }
                if (i == n - 1 && j == m - 1){
                    grid[i][j] = true;
                    continue;
                }
            }
        }
        return grid[0][0];
    };
    int maxx = 1;
    for (int i = 1; i * i <= max_cand; ++i){
        if (max_cand % i > 0) continue;
        if (works(i)){maxx = max(maxx, i);}
        if (works(max_cand / i)) {maxx = max(maxx, max_cand / i);}
    }
    cout << maxx << endl;
}

int main(){
    int t;
    cin >> t;
    while (t--){
        solve();
    }
}