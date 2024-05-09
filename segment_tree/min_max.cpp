#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include <cmath>
#include <set>
#include <numeric>
#include <limits>
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

// class SegTree;

class SegTree {
    public: int l, r, m, maxx, minn;
    class SegTree* left;
    class SegTree* right;
    public: SegTree (vi const &vector, int start, int end){
        l = start;
        r = end;
        m = (l + r) / 2;
        if (l == r){maxx = vector[m]; minn = vector[m];}
        else {
            left = new SegTree(vector, l, m);
            right = new SegTree(vector, m + 1, r);
            merge();
        }
    }
    public:void update(int pos, int new_value) {
        if (pos < this -> l || pos > this -> r) return;
        if (pos == this -> l && pos == this -> r) {this -> maxx = new_value; this -> minn = new_value; return;}
        if (pos <= m) left -> update(pos, new_value); else right -> update(pos, new_value);
        merge();
    }
    public: pair<int, int> query(int start, int end) {
        int test = this -> l;
        int testt = this -> r;
        int minnn = this -> minn;
        int maxxx = this -> maxx;
        if (start == l && end == r) return {minn, maxx};
        if (start > m) return right -> query(start, end);
        if (end <= m) return left -> query(start, end);

        pair<int, int> leftMinMax = left -> query(start, m);
        pair<int, int> rightMinMax = right -> query(m + 1, end);
        int minn = min(leftMinMax.first, rightMinMax.first);
        int maxx = max(leftMinMax.second, rightMinMax.second);
        return {minn, maxx};
    }
    public: void merge(){
        maxx = max(left -> maxx, right -> maxx);
        minn = min(left -> minn, right -> minn);
    }
};

int main() {
    int n;
    cin >> n;
    vi a(n);
    for (auto & num : a) cin >> num;

    SegTree segTree(a, 0, n - 1);

    int q;
    cin >> q;
    while (q--){
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 1){
            l--;
            segTree.update(l, r);
        } else {
            l--; r--;
            pair<int, int> minMax = segTree.query(l, r);
            cout << minMax.first << ' ' << minMax.second << "\n";
        }
    }
}