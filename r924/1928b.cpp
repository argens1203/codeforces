#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <map>
using namespace std;

typedef vector<int> vi;
typedef vector<long long> vl;
typedef unordered_map<long long, int> umlli;

int main(){
    int tc;
    cin >> tc;
    while (tc--){
        int n;
        cin >> n;
        vi a(n);
        for (auto& i : a){
            cin >> i;
        }

        sort(a.begin(), a.end());
        a.resize(unique(a.begin(), a.end()) - a.begin());
        auto start = a.begin();
        int ans = 0;
        for (auto itr = a.begin(); itr != a.end(); ++itr){
            while (*itr - *start >= n) start++;
            if (itr - start + 1 > ans) ans = itr - start + 1;
        }
        cout << ans << "\n";
    }
}