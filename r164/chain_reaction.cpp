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

ll comb(ll n, int r){
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

int main() {
    int n; cin >> n;
    vi a(n);
    for (auto & i : a) cin >> i;
    
    int maxx = *max_element(a.begin(), a.end());
    vll dp(maxx + 1, 0ll); // accumulate the number of coefficients and iterate by value instead of number
    for (int i = 0; i < n; ++i){
        int coef = 0;
        if (i == 0 || a[i] > a[i - 1]) coef++;
        if (i + 1 < n && a[i + 1] > a[i]) coef--;
        dp[a[i]] += coef; // store the original coefficient
    }
    // calculate prefix sum since eg. for k = 5, values 1 - 5 are all needing exactly one blow
    // so sum of coefficient * 1, that is ceil(value / k) over value 1 - 5, is going to sum to dp[5] * 1
    for (int i = 1; i <= maxx; ++i) dp[i] += dp[i - 1];

    // loop from 1 to maxx
    // loop from 1 to ceil(maxx / k)
    for (int k = 1; k <= maxx; ++k){
        ll total = 0;
        for (int i = 1; i <= ceil(maxx * 1.0 /k); ++i){
            total += i * (dp[min(maxx, i * k)] - dp[(i - 1) * k]);
        }
        cout << total << ' ';
    }
    cout << "\n";
}