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
typedef multiset<int> msi;

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

umii count_min(umii a, umii b){
    umii overlap;
    for (auto i : a){
        overlap[i.first] = min(i.second, b[i.first]);
    }
    return overlap;
}

int sum (umii u){
    int s = 0;
    for (auto i : u){
        s += i.second;
    }
    return s;
}

// long inversion
void solve(){
    int n;
    cin >> n;
    string s;
    cin >> s;

    vi d(n);
    for (int i = 0; i < n; ++i){
        d[i] = s[i] - '0';
    }

    int j;
    for (j = n; j >= 1; --j){
        int rev = 0;
        vi end(n + 1, 0);
        int i;
        for (i = 0; i < n; ++i){
            rev -= end[i];
            if ((d[i] + rev) & 1) continue;
            rev += 1;
            if (i + j <= n){
                end[i + j] += 1;
            } else {
                break;
            }
        }
        if (i == n) break;
    }

    cout << j << "\n";
}

int main(){
    int t;
    cin >> t;
    while (t--){
        solve();
    }
}