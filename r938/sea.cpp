#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include <cmath>
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

vi getArray(int n, int c, int d){
    vi ans(pow(n, 2), 0);
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            ans[i * n + j] = c * i + d * j;
        }
    }
    sort(ans.begin(), ans.end());
    // cout << "size: " << ans.size() << endl;
    return ans;
}

void solve(){
    int n;
    long long k;
    cin >> n >> k;
    vi ships(n);
    for (auto & itr : ships) cin >> itr;

    int h = 0; int t = n - 1;
    int count = 0;
    while (t - h >= 1 && k > 0){
        // for (auto s : ships) cout << s << ",";
        // cout << endl;
        int m = min(ships[h], ships[t]);
        if (k > 2 * m){
            k -= 2 * m;
            ships[h] -= m;
            ships[t] -= m;
        } else {
            ships[h] -= (k / 2 + k % 2);
            ships[t] -= k / 2;
            k = 0;
        }
        if (ships[h] == 0){
            ++h; ++count;
        }
        if (ships[t] == 0){
            --t; ++count;
        }
    }

    if (t == h && k >= ships[h]){
        ++count;
    }
    cout << count << "\n";
}

int main(){
    int t;
    cin >> t;
    while (t--){
        solve();
    }
}