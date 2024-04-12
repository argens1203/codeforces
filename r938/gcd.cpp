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
    vvi mapp(n);
    vector<vector<set<int>>> ans(n);
    for (int i = 0; i < n; i++){
        vi row(m);
        vector<set<int>> arow(m);
        for (int j = 0; j < m; j++){
            cin >> row[j];
            set<int> possibles;
            arow[j] = possibles;
        }
        mapp[i] = row;
        ans[i] = arow;
    }

    for (int i = n - 1; i >= 0; --i){
        for (int j = m - 1; j >= 0; --j){
            if (i == n - 1 && j == m - 1){
                ans[i][j].insert(mapp[n - 1][m - 1]);
            }
            else {
                if (j != m - 1)
                    for (auto pos : ans[i][j + 1]){
                        ans[i][j].insert(gcd(mapp[i][j], pos));
                    }
                if (i != n - 1) 
                    for (auto pos : ans[i + 1][j]){
                        ans[i][j].insert(gcd(mapp[i][j], pos));
                    }
            }
        }
    }
    int max = -1;
    for (auto i : ans[0][0]){
        if (i > max) max = i;
    }
    cout << max << "\n";
}

int main(){
    int t;
    cin >> t;
    while (t--){
        solve();
    }
}