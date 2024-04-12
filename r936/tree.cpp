#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include <cmath>
#include <limits>
#include <set>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef unordered_map<long long, int> umlli;
typedef unordered_map<int, int> umii;
typedef unsigned long long ull;
typedef map<pair<int, int>, int> mpii;
typedef pair<int, int> pii;
typedef map<int, int> mii;

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

void solve(){
    int n, k;
    cin >> n >> k;
    vector<vector<int>> edges(n);

    int edgeCount = n - 1;
    while (edgeCount--){
        int s, e;
        cin >> s >> e;
        --s, --e;
        edges[s].emplace_back(e); // better than push_back
        edges[e].emplace_back(s);
    }

    auto check = [&](int x) {
        int res = 0;
        auto dfs = [&](auto self, int v, int p) -> int { // lambda, self, declare return type for using self
            int size = 1;
            for (auto u : edges[v]){
                if (u == p) continue; // if trying to go back to parent, disallow
                size += self(self, u, v); // recursive find size
            }
            if (size >= x){ // if big enough, greedy trim
            // Model answer (removed and tested): handle the edge case of 0, 0 (initialized for laziness)
            // if (size >= x && v != p){
                size = 0;
                res++; // increment tree count
            }
            return size;
        };
        int remainder = dfs(dfs, 0, 0);
        return res > k || (res == k && remainder >= x);
        
        // if result = cut count, is not enough, because cut count + 1 = tree count
        // remainder need to be greater than x as well
    };
    int low = 1;
    int high = n / (k + 1) + 1;
    while (low < high - 1){ // if just usual low < high, will have infinite loop
        int mid = (low + high) / 2;
        if (check(mid)){
            low = mid;
        } else {
            high = mid;
        }
    }
    cout << low << "\n";
}

// https://codeforces.com/blog/entry/127439

int main(){
    int t;
    cin >> t;
    while (t--){
        solve();
    }
}