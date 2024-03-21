// https://codeforces.com/blog/entry/96344
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

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

#define rep1(a)          for(int i = 0; i < a; i++)
#define rep2(i, a)       for(int i = 0; i < a; i++)
#define rep3(i, a, b)    for(int i = a; i < b; i++)
#define rep4(i, a, b, c) for(int i = a; i < b; i += c)
#define overload4(a, b, c, d, e, ...) e
#define rep(...) overload4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)


#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second
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
