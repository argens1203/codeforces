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
    int n; string s;
    cin >> n; cin >> s;

    set<int> north; set<int> south; set<int> west; set<int> east;
    for (int i = 0; i < n; ++i){
        if (s[i] == 'N') north.insert(i);
        if (s[i] == 'S') south.insert(i);
        if (s[i] == 'E') east.insert(i);
        if (s[i] == 'W') west.insert(i);
    }
    int l = -1; int sl = -1;
    while (!north.empty() && !south.empty()){
        l = *north.begin();
        sl = *south.begin();
        north.erase(north.begin());
        south.erase(south.begin());
    }
    while (!east.empty() && !west.empty()){
        l = *east.begin();
        sl = *west.begin();
        east.erase(east.begin());
        west.erase(west.begin());
    }
    if ((north.size() + south.size() + west.size() + east.size()) == 0){
        if (l == -1 || n == 2){
            cout << "NO\n";
            return;
        }
    }
    if (north.size() % 2 | south.size() % 2 | west.size() % 2 | east.size() % 2){
        cout << "NO\n";
    } else {
        bool next_north = true;
        bool next_south = true;
        bool next_east = true;
        bool next_west = true;

        for (int i = 0; i < n; ++i){
            if (north.find(i) != north.end()){
                cout << (next_north ? 'R' : 'H');
                next_north = !next_north;
            }
            else if (south.find(i) != south.end()){
                cout << (next_south ? 'R' : 'H');
                next_south = !next_south;
            }
            else if (east.find(i) != east.end()){
                cout << (next_east ? 'R' : 'H');
                next_east = !next_east;
            }
            else if (west.find(i) != west.end()){
                cout << (next_west ? 'R' : 'H');
                next_west = !next_west;
            }
            else {
                if (i == l) cout << 'H';
                else if (i == sl) cout << 'H';
                else cout << 'R';
            }
        }
        cout << '\n';
    }
}

int main() {
    int t; cin >> t; while (t--) solve();
}