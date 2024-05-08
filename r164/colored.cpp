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

const int MOD = 998244353;
 
int add(int x, int y) {
  x += y;
  if (x >= MOD) x -= MOD;
  return x;
} 
 
int mul(int x, int y) {
  return x * 1LL * y % MOD; // use 1LL to prevent overflow
}
 
int main() {
    int n;
    cin >> n;
    vi a(n);
    for (auto & i : a) cin >> i;

    // From here on, sum means sum of balls given a set of colors
    int s = accumulate(a.begin(), a.end(), 0); // get maximum sum and by definition s <= 5000
    vi dp(s + 1, 0); // use dp to store + calc. the no. of sets which has an exact sum
    dp[0] = 1; // only way to have sum = 0 is empty set
    for (auto num : a){
        // by looping it in reversing order, each number cannot be added in set twice
        for (int j = s - num; j >= 0; --j){
            dp[j + num] = add(dp[j + num], dp[j]); // not using += can be confusing
        }
    }

    int total = 0;
    for (int j = 1; j <= s; j++){
        // (j + 1 / 2) is round_up(j / 2)
        // # of set = dp[j], value = (j + 1) / 2, sum of value = sum of mult
        total = add(total, mul(dp[j], (j + 1) / 2));
    }

    // total has been undershot by cases where 1 number is greater than sum of all
    for (auto num : a){
        // hence the less than sign (<) is critical
        // by looping sum directly, up to less than "num"
        // we get the number of sets we undershot, since we 100% constructed a set from those by adding a "num" to it, which also 100% didn't already exist since j < num
        for (int j = 0; j < num; ++j){
            // add num, minus (j + num + 1) / 2, which is the set we supposedly constructed
            // multiply by number of sets we undershot
            total = add(total, mul(dp[j], num - (j + num + 1) / 2)); // <----------- HIGHLIGHT of the question
        }
    }
    cout << total << "\n";
}