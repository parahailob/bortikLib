#include <vector>

using namespace std;

namespace bortikLib {

    // Fenwick tree, point-update point-access. 1-based indexing
    template <typename T>
    struct BIT {
        int n;          // number of elements
        vector<T> bit;  // data storage
        BIT(int n_) : n(n_ + 1), bit(n, 0) {}
        BIT(int n_, const vector<T> &src) : n(n_+1), bit(n, 0) {
            vector<T> rws(n, 0);
            for(int i = 1; i < n; i++){
                rws[i] = rws[i-1] + src[i-1];
                bit[i] = rws[i] - rws[i - (i & -i)];
            }
        }
    
        void add(int i, T x){   // add to i
            for(int idx = i; idx < n; idx += (idx & -idx)){
                bit[idx] += x;
            }
        }
    
        T sum(int i){  // segment sum [1, i]      
            T s(0);
            for(int idx = i; idx > 0; idx -= (idx & -idx)){
                s += bit[idx];
            }
            return s;
        }
    
        // get [l, r) sum
        T query(int l, int r) { return sum(r - 1) - sum(l - 1); }
    };
    
    // Fenwick tree with range access and query
    template <typename T>
    struct BIT_RAQ {
        int n;             // number of elements
        vector<T> bit[2];  // data storage
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
        void add(int l, int r, T x) {  // add to segment [l, r)
            add_sub(0, l, -x * (l - 1));
            add_sub(0, r, x * (r - 1));
            add_sub(1, l, x);
            add_sub(1, r, -x);
        }
        void add(int i, T x){ // add to i
            add(i, i+1, x);
        }
        T sum_sub(int p, int i) {
            T s(0);
            for (int idx = i; idx > 0; idx -= (idx & -idx)) {
                s += bit[p][idx];
            }
            return s;
        }
        //[1,i] segment sum
        T sum(int i) { return sum_sub(0, i) + sum_sub(1, i) * i; }  
    
         // [l,r) segment sum
        T query(int l, int r) { return sum(r - 1) - sum(l - 1); }
    };
}