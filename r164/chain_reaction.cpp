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


int find_l (const vector<int>& a, int k){
    int total = 0;
    int acc_dmg = 0;
    for (int num : a){
        if (acc_dmg > num){
            acc_dmg = ceil(num * 1.0 / k) * k;
            continue;
        }
        int l_c = ceil((num - acc_dmg) * 1.0 / k);
        acc_dmg += l_c * k;
        total += l_c;
    }
    return total;
}
 
int main() {
    int n; cin >> n;
    vi a(n);
    for (auto & i : a) cin >> i;
    
    int maxx = *max_element(a.begin(), a.end());

    for (int k = 1; k < maxx; ++k){
        cout << find_l(a, k) << ' ';
    }
    cout << 1 << "\n";
}