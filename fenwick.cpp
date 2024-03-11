#include <vector>

using namespace std;

namespace bortikLib {
    template <typename T>
    struct BIT {
        int n;          //要素数
        vector<T> bit;  //データの格納先
        BIT(int n_) : n(n_ + 1), bit(n, 0) {}
        BIT(int n_, const vector<T> &src) : n(n_+1), bit(n, 0) {
            vector<T> rws(n, 0);
            for(int i = 1; i < n; i++){
                rws[i] = rws[i-1] + src[i-1];
                bit[i] = rws[i] - rws[i - (i & -i)];
            }
        }
    
        void add(int i, T x){   //i　に加算
            for(int idx = i; idx < n; idx += (idx & -idx)){
                bit[idx] += x;
            }
        }
    
        T sum(int i){  //[1,i] 区間の総和         
            T s(0);
            for(int idx = i; idx > 0; idx -= (idx & -idx)){
                s += bit[idx];
            }
            return s;
        }
    
        // [l,r) の区間和を取得
        T query(int l, int r) { return sum(r - 1) - sum(l - 1); }
    };

    template <typename T>
    struct BIT_RAQ {
        int n;             // 要素数
        vector<T> bit[2];  // データの格納先
        BIT_RAQ(int n_) { init(n_); }
        void init(int n_) {
            n = n_ + 1;
            for (int p = 0; p < 2; p++) bit[p].assign(n, 0);
        }
        void add_sub(int p, int i, T x) {
            for (int idx = i; idx < n; idx += (idx & -idx)) {
                bit[p][idx] += x;
            }
        }
        void add(int l, int r, T x) {  // [l,r) に加算
            add_sub(0, l, -x * (l - 1));
            add_sub(0, r, x * (r - 1));
            add_sub(1, l, x);
            add_sub(1, r, -x);
        }
        void add(int i, T x){ //i に加算
            add(i, i+1, x);
        }
        T sum_sub(int p, int i) {
            T s(0);
            for (int idx = i; idx > 0; idx -= (idx & -idx)) {
                s += bit[p][idx];
            }
            return s;
        }
        //[1,i] 区間の総和
        T sum(int i) { return sum_sub(0, i) + sum_sub(1, i) * i; }  
    
         // [l,r) の区間和を取得
        T query(int l, int r) { return sum(r - 1) - sum(l - 1); }
    };
}