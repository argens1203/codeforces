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
    int n; cin >> n;
    vi a(n);
    for (auto &i : a){
        cin >> i;
    }

    long long total = 0;
    int count = 0;
    int max = -1;
    for (auto i : a){
        total += i;
        if (i > max) max = i;
        if ((long long) max * 2 == total) count ++;
    }
    cout << count << '\n';
}

int main(){
    int t;
    cin >> t;

    while (t--){
        solve();
    }
}