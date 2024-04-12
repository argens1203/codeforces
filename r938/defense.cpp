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

void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<int, int>> path;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            char temp;
            cin >> temp;
            if (temp == '#'){
                path.push_back({i, j});
            }
        }
    }

    map<pair<int, int>, int> towers;
    for (int i = 0; i < k; ++i){
        int row, col, pow;
        cin >> row >> col >> pow;
        --row; --col;
        towers[{row, col}] = pow;
    }

    auto getdmg = [&](pair<int, int> towerKey, int radius) -> long long {
        long long dmg = 0;
        for (auto tile : path){
            if (dist(tile, towerKey) <= radius){
                dmg += (long long) towers[towerKey];
            }
        }
        return dmg;
    };

    int maxRange = (int)ceil(sqrt(pow(n, 2) + pow(m, 2))) + 1;

    vector<tuple<pair<int, int>, int, long long>> tow_dmg; // coo, range, dmg
    vll costs (maxRange, 0);
    for (int i = 0; i < maxRange; ++i){
        costs[i] = pow(3, i);
    }
    for (auto itr : towers){
        for (int i = 1; i < maxRange; ++i){
            int cost = costs[i];
            long long dmg = getdmg(itr.first, i);
            tuple<pair<int, int>, int, long long> tmp;
            get<0>(tmp) = itr.first;
            get<1>(tmp) = i;
            get<2>(tmp) = (long long) dmg - cost;
            tow_dmg.push_back(tmp);
        }
    }

    auto comp = [&](tuple<pair<int, int>, int, long long> a, tuple<pair<int, int>, int, long long> b) -> int {
        return get<2>(a) < get<2>(b) || (get<2>(a) == get<2>(b) && get<1>(a) > get<1>(b));
    };

    sort(tow_dmg.rbegin(), tow_dmg.rend(), comp);

    long long maxHp = 0;
    set<tuple<pair<int, int>, int, long long>> seen;
    for (int i = 0; i < max(k, maxRange); ++i){
        long long hp = 0;
        set<pair<int, int>> chosen;
        set<int> chosenRange;
        bool first = true;
        for (auto itr : tow_dmg){
            if (seen.find(itr) != seen.end()) continue;
            if (first){seen.insert(itr); first = false;}
            // auto t = get<0>(itr);
            // cout << t.first << ", " << t.second << ": (" << get<1>(itr) << ") " << get<2>(itr) << endl;
            if (chosen.find(get<0>(itr)) == chosen.end() && chosenRange.find(get<1>(itr)) == chosenRange.end()){
                if (get<2>(itr) > 0){
                    hp += get<2>(itr);
                    chosenRange.insert(get<1>(itr));
                    chosen.insert(get<0>(itr));
                }
            } else {
                continue;
            }
        }
        if (hp > maxHp) maxHp = hp; 
    }
    cout << maxHp << "\n";
}

int main(){
    int t;
    cin >> t;
    while (t--){
        solve();
    }
}