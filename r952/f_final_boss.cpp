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
const int maxI = 1e9;

void solve(){
    int h, n;
    cin >> h >> n;
    vi a(n); vi c(n);
    for (auto &i : a) cin >> i;
    for (auto &i : c) cin >> i;

    map<int, long long> mapp;
    for (int i = 0; i < n; ++i){
        mapp[c[i]] += a[i];
    }

    long long cycle = 1;
    for (auto itr : mapp){
        cycle *= itr.first;
    }

    vector<long long> dp(cycle, 0);
    for (auto itr : mapp){
        dp[0] += itr.second;
    }
    for (int i = 1; i < cycle; ++i){
        dp[i] = dp[i - 1];
        for (auto itr : mapp){
            if (i % itr.first == 0){
                dp[i] += itr.second;
            }
        }
    }

    long long round = 0;
    if (h > dp[cycle - 1]){
        round = h / dp[cycle - 1] * cycle;
        h = h % dp[cycle - 1];
        if (h == 0){
            round -= cycle;
        }
    }

    int remain = 0;
    remain = lower_bound(dp.begin(), dp.end(), h) - dp.begin();

    cout << round + remain + 1 << '\n';
}

int main(){
    int t;
    cin >> t;

    while (t--){
        solve();
    }
}