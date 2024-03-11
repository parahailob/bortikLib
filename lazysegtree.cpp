#include <bits/stdc++.h>



template <typename T>
class Segtree{
    private:
        int size;
        std::vector<T> arr;
        std::vector<T> hold;
    public:
        Segtree(int size_){
            size = 1;
            while(size < size_){
                size *= 2;
            }
            arr = std::vector<T>(size*2, 0);
            hold = std::vector<T>(size*2, 0);
        }

        void update(int l, int r, T val){
            update_(l, r, 1, size+1, 1, val);
        }

        void update_(int l, int r, int a, int b, int u, T val){
            if(l <= a && b <= r){
                hold[u] += val;
                arr[u] += val*(b-a);
                return;
            }
            if(b <= l || a >= r) return;
            int m = (a+b)/2;
            propagate(u, a, b, m);
            update_(l, r, a, m, u*2, val);
            update_(l, r, m, b, u*2+1, val);
            arr[u] = arr[u*2] + arr[u*2+1];       
        }

        void propagate(int u, int a, int b, int m){
            hold[u*2] += hold[u];
            arr[u*2] += hold[u]*(m-a);
            hold[u*2+1] += hold[u];
            arr[u*2+1] += hold[u]*(b-m);
            hold[u] = 0;
        }

        T query(int l, int r){
            return query_(l, r, 1, size+1, 1);
        }

        T query_(int l, int r, int a, int b, int u){
            if(a >= l && b <= r) return arr[u];
            if(a >= r || b <= l) return 0;
            int m = (a+b)/2;
            propagate(u, a, b, m);
            T valLeft = query_(l, r, a, m, u*2);
            T valRight = query_(l, r, m, b, u*2+1);
            return valLeft + valRight;
        }
};






int main(){

    int n, q; std::cin >> n >> q;
    Segtree<long long> tree(n);
    while(q--){
        int p; std::cin >> p;
        if(p == 0){
            long long l, r, val; std::cin >> l >> r >> val;
            tree.update(l, r+1, val);
        }
        if(p == 1){
            long long l, r; std::cin >> l >> r; 
            printf("%lld\n", tree.query(l, r+1));
        }
    }

    return 0;
}