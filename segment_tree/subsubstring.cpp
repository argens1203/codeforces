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
#include <cassert>
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

struct value {
    int middle;
    pair<char, int> left;
    pair<char, int> right;
    int length;
};

class SegTree {
    public: int l, r, m;
    public: struct value val;
    class SegTree* left;
    class SegTree* right;
    public: SegTree (const vector<char> &a, int start, int end){
        l = start;
        r = end;
        m = (l + r) / 2;
        if(l != r) {
            left = new SegTree(a, l, m);
            right = new SegTree(a, m + 1, r);
            this -> val = this -> merge (left -> val, right -> val);
        } else {
            this -> val.left = {a[l], 1};
            this -> val.right = {a[l], 1};
            this -> val.middle = 1;
            this -> val.length = 1;
        }
    }

    public: struct value query(int start, int end) {
        // chance to optimize?

        if (end <= this -> m && this -> l != this -> r) return this -> left -> query (start, end);
        if (start > this -> m && this -> l != this -> r) return this -> right -> query (start, end);
        if (start == end){
            assert(start == l);
            return this -> val;
        }
        if (start == this -> l && end == this -> r) return this -> val;
        return this -> merge(left -> query(start, m), right -> query(m+1, end));
    }

    public: struct value merge(const struct value& l_result, const struct value& r_result){
        int maxx = max(l_result.middle, r_result.middle);
        if (l_result.right.first == r_result.left.first) maxx = max(maxx, l_result.right.second + r_result.left.second);
        struct value ret;
        ret.middle = maxx;

        ret.left = l_result.left;
        ret.right = r_result.right;
        if (ret.left.first == r_result.left.first && l_result.length == l_result.left.second) { ret.left.second += r_result.left.second; }
        if (ret.right.first == l_result.right.first && r_result.length == r_result.right.second) { ret.right.second += l_result.right.second; }
        ret.length = l_result.length + r_result.length;
        return ret;
    }
};

int main() {
    int n, q;
    cin >> n >> q;
    vector<char> a(n);
    for (auto & c : a) cin >> c;

    SegTree segTree(a, 0, n - 1);

    while (q--){
        int start, end;
        cin >> start >> end;
        start--; end--;
        struct value res = segTree.query(start, end);
        cout << res.middle << "\n";
    }
}