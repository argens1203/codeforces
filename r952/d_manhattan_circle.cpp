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
    int x, y;
    cin >> x >> y;
    // vector<vector<bool>> v(x, vector<bool> (y, false));

    int max = -1;
    int center_y = -1;
    int row = -1;

    for (int i = 0; i < x; ++i){
        int start = -1;
        int end = -1;
        for (int j = 0; j < y; ++j){
            char c; cin >> c;
            if (c == '#'){
                // v[i][j] = true;
                if (start == -1) start = j;
                else end = j;
            }
        }
        if (end == -1) end = start;
        if ((end - start + 1) > max && end != -1){
            max = end - start;
            center_y = (start + end) / 2;
            row = i;
        }
    }

    cout << row + 1 << ' ' << center_y + 1 << '\n';
}

int main(){
    int t;
    cin >> t;

    while (t--){
        solve();
    }
}