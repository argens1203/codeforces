#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include <cmath>
#include <set>
#include <numeric>
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

ll comb_2(ll n){
    return n * (n - 1) / 2;
}

int gcd(int a, int b){
    if (b == 0) return a;
    if (a == b) return a;
    if (a > b) return gcd(b, a % b);
    return gcd(b, a);
}

double dist(pair<int, int> a, pair<int, int> b){
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

int choose_furthest(const vi& arr){
    if (arr.size() == 1) return 0;
    int sum_size = arr.size() / 2 + 1;
    vi odd(sum_size);
    vi even(sum_size);

    for (int i = 0; i < arr.size() - 1; ++i){
        if (i % 2 == 0){
            // even
            even[i / 2 + 1] = even[i / 2] + arr[i + 1] - arr[i];
        } else {
            // odd
            odd[i / 2 + 1] = odd[i / 2] + arr[i + 1] - arr[i];
        }
    }

    int minn = odd[sum_size - 1];
    int idx = 0;

    if (even[sum_size - 1] < minn){
        minn = even[sum_size - 1];
        idx = arr.size() - 1;
    }

    for (int i = 2; i < arr.size() - 1; i += 2){
        int total = even[i / 2] + (odd[sum_size - 1] - odd[i / 2]);
        if (total < minn){
            minn = total;
            idx = i;
        }
    }
    return idx;
}

void solve(){
    int n, k;
    cin >> n >> k;
    
    vector<int> a(n);
    for (auto &i : a) cin >> i;

    // --

    unordered_map<int, vector<int>> mapp;
    for (int i : a){
        mapp[(i % k)].push_back(i);
    }
    
    int total = 0;
    bool hasOdd = false;
    for (auto itr : mapp){
        sort(itr.second.begin(), itr.second.end());
        if (itr.second.size() % 2 == 1){
            if (hasOdd) {
                cout << -1 << '\n';
                return;
            } else {
                hasOdd = true;
                itr.second.erase(itr.second.begin() + choose_furthest(itr.second));
            }
        }
    
        for (int i = 0; i < itr.second.size(); i += 2){
            total += ((itr.second[i + 1] - itr.second[i]) / k);
        }
    }

    cout << total << '\n';
}

int main() {
    int t; cin >> t; while (t--) solve();
}