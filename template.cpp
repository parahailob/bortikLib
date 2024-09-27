// https://codeforces.com/blog/entry/96344
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

#if __cplusplus >= 202002L
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;
#endif

template<typename T>
bool chmax(T& a, const T& b) {
    bool res = a < b;
    a = max(a, b);
    return res;
}
template<typename T>
bool chmin(T& a, const T& b){
    bool res = a > b;
    a = min(a, b);
    return res;
}

typedef vector<long long> vl;
typedef pair<ll,ll> pll;
typedef vector<pair<ll, ll>> vll;
typedef vector<int> vi;
typedef vector<pair<int,int>> vii;
typedef pair<int,int> pii;

const int inf = 1000000009;
const ll linf = 4000000000000000009;


// https://trap.jp/post/1224/
template<class... T>
void input(T&... a){
    (cin >> ... >> a);
}

void print(){
    cout << '\n';
}
template<class T, class... Ts>
void print(const T& a, const Ts&... b){
    cout << a;
    (cout << ... << (cout << ' ', b));
    cout << '\n';
}

template <typename T>
T floor(T a, T b) {
  return a / b - (a % b && (a ^ b) < 0);
}
template <typename T>
T ceil(T x, T y) {
  return floor(x + y - 1, y);
}

int popcnt(int x) { return __builtin_popcount(x); }
int popcnt(u32 x) { return __builtin_popcount(x); }
int popcnt(ll x) { return __builtin_popcountll(x); }
int popcnt(u64 x) { return __builtin_popcountll(x); }
int popcnt_mod_2(int x) { return __builtin_parity(x); }
int popcnt_mod_2(u32 x) { return __builtin_parity(x); }
int popcnt_mod_2(ll x) { return __builtin_parityll(x); }
int popcnt_mod_2(u64 x) { return __builtin_parityll(x); }
// (0, 1, 2, 3, 4) -> (-1, 0, 1, 1, 2)
int topbit(int x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
int topbit(u32 x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
int topbit(ll x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }
int topbit(u64 x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }
// (0, 1, 2, 3, 4) -> (-1, 0, 1, 0, 2)
int lowbit(int x) { return (x == 0 ? -1 : __builtin_ctz(x)); }
int lowbit(u32 x) { return (x == 0 ? -1 : __builtin_ctz(x)); }
int lowbit(ll x) { return (x == 0 ? -1 : __builtin_ctzll(x)); }
int lowbit(u64 x) { return (x == 0 ? -1 : __builtin_ctzll(x)); }

template<typename T, typename U>
T SUM(const vector<U> &A){
    T ret = 0;
    for (auto &&a: A) ret += a;
    return ret;
}

#define rep1(a)          for(int i = 0; i < a; i++)
#define rep2(i, a)       for(int i = 0; i < a; i++)
#define rep3(i, a, b)    for(int i = a; i < b; i++)
#define rep4(i, a, b, c) for(int i = a; i < b; i += c)
#define overload4(a, b, c, d, e, ...) e
#define rep(...) overload4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)

#define rrep(i, a, b)    for(int i = a; i >= b; i--)

#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second
#define all(v) v.begin(), v.end()
//---------------------------------


void solve(){
    
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    //cin >> t;
    rep(i,0,t) solve();
}
