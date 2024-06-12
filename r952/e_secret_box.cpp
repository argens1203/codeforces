#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include <cmath>
#include <set>
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

const int R = 12;
const int maxI = 1e9;

void solve(){
    int x, y, z;
    long long t;
    cin >> x >> y >> z >> t;

    long long max = 0;
    for (int i = 1; i <= x; ++i){
        for (int j = 1; j <= y; ++j){
            if (t % i != 0 || ((t / i) % j) != 0) continue;
            int k = t / i / j;
            if (k > z) continue;
            long long total = (long long)((z - k + 1) * (y - j + 1) * (x - i + 1));
            if (total > max) max = total;
        }
    }

    cout << max << '\n';
}

int main(){
    int t;
    cin >> t;

    while (t--){
        solve();
    }
}