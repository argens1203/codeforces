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


int find_l (const map<int, set<int>>& mapp, int k, int n){
    // cout << k << ":";
    int total = 0;
    int ac = 1;
    int acc_dmg = 0;
    set<int> didx;
    auto curr = mapp.begin();
    while (curr != mapp.end()){
        while (acc_dmg < curr -> first){
            int l_count = max(1, (curr -> first - acc_dmg) / k);
            acc_dmg += (l_count * k);
            total += (l_count * ac);
            // acc_dmg += k;
            // total += ac;
        }
        for (auto idx : curr -> second){
            ac += 1;
            if (didx.find(idx - 1) != didx.end() || (idx == 0)){
                ac -= 1;
            }
            if (didx.find(idx + 1) != didx.end() || (idx == n - 1)) ac -= 1;
            didx.insert(idx);
        }
        curr++;
    }
    return total;
}
 
int main() {
    int n; cin >> n;
    vi a(n);
    for (auto & i : a) cin >> i;
    
    int maxx = -1;
    map<int, set<int>> m;
    for (int i = 0; i < n; ++i){
        int num = a[i];
        // cout << num;
        if (num > maxx) maxx = num;
        if (m.find(num) == m.end()){
            m[num] = set<int>();
        }
        m[num].insert(i);
    }

    for (int k = 1; k < maxx; ++k){
        cout << find_l(m, k, n) << ' ';
    }
    cout << 1 << "\n";
}