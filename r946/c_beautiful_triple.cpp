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

void solve(){
    int n;
    cin >> n; vi a(n);
    for (auto & i : a) cin >> i;

    map<pair<int, int>, unordered_map<int, int>> sett1;
    map<pair<int, int>, unordered_map<int, int>> sett2;
    map<pair<int, int>, unordered_map<int, int>> sett3;
    for (int i = 0; i < n - 2; ++i){
        int f = a[i]; int s = a[i+1]; int l = a[i+2];
        if (sett1.find({f, s}) == sett1.end()) sett1[{f, s}] = unordered_map<int, int>();
        sett1[{f,s}][l]+=1;

        if (sett2.find({f, l}) == sett2.end()) sett2[{f, l}] = unordered_map<int, int>();
        sett2[{f,l}][s]+=1;

        if (sett3.find({s, l}) == sett3.end()) sett3[{s, l}] = unordered_map<int, int>();
        sett3[{s,l}][f]+=1;
    }

    long long total = 0;
    auto calc = [&](const unordered_map<int, int> & mapp) -> int {
        long long tot = 0;
        for (auto itr = mapp.begin(); itr != mapp.end(); itr++){
            for (auto itr2 = next(itr); itr2 != mapp.end(); itr2++){
                tot += (itr -> second * itr2 -> second);
            }
        }
        return tot;
    };
    for (auto itr = sett1.begin(); itr != sett1.end(); itr++){
        // cout << "first: " << itr -> first.first << "second: " << itr -> first.second << "\n";
        // cout << "begin";
        // cout << (itr -> second).size();
        // cout << "end\n";
        // total += comb_2((itr -> second).size());
        total += calc(itr->second);
    }
    for (auto itr = sett2.begin(); itr != sett2.end(); itr++){
        // cout << "first: " << itr -> first.first << "second: " << itr -> first.second << "\n";
        // cout << "begin";
        // cout << (itr -> second).size();
        // cout << "end\n";
        total += calc(itr->second);
        // total += comb_2((itr -> second).size());
    }
    for (auto itr = sett3.begin(); itr != sett3.end(); itr++){
        // cout << "first: " << itr -> first.first << "second: " << itr -> first.second << "\n";
        // cout << "begin";
        // cout << (itr -> second).size();
        // cout << "end\n";
        total += calc(itr->second);
        // total += comb_2((itr -> second).size());
    }
    cout << total << '\n';
}

int main() {
    int t; cin >> t; while (t--) solve();
}