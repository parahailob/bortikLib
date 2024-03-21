#include <template.cpp>

// point range segment tree, zero-based indexing
template<typename T, T (*op)(T, T), T (*up)(T, T), T e>
class PRSegTree{
    public:
        PRSegTree(size_t size_, T initial){
            size = 1;
            while(size < size_) size *= 2;
            arr = std::vector<T>(size*2, initial);
        }

        PRSegTree(size_t size_, const std::vector<T> &initvec){
            size = 1;
            while(size < size_) size *= 2;
            arr = std::vector<T>(size*2, e);
            for(size_t i = 0; i < initvec.size(); i++){
                arr[size+i] = initvec[i];
            }
            for(size_t i = size-1; i > 0; i--){
                arr[i] = op(arr[i*2], arr[i*2+1]);
            }
        }

        PRSegTree(const std::vector<T> &initvec){
            size = 1;
            while(size < initvec.size()) size *= 2;
            arr = std::vector<T>(size*2, e);
            for(size_t i = 0; i < initvec.size(); i++){
                arr[size+i] = initvec[i];
            }
            for(size_t i = size-1; i > 0; i--){
                arr[i] = op(arr[i*2], arr[i*2+1]);
            }
        }

        void update(int pos, T val){
            pos += size;
            arr[pos] = up(arr[pos], val);
            while(pos >= 2){
                pos /= 2;
                arr[pos] = op(arr[pos*2], arr[pos*2+1]);
            }
        }

        T query(int l, int r){
            return query_(l, r, 0, size, 1);
        }

        T query_(int l, int r, int a, int b, int u){
            if(a >= l && b <= r) return arr[u];
            if(a >= r || b <= l) return e;
            int m = (a+b)/2;
            T valRight = query_(l, r, a, m, u*2);
            T valLeft = query_(l, r, m, b, u*2+1);
            return op(valRight, valLeft);
        }

    private:
        size_t size;
        std::vector<T> arr;
};


// Range-Point lazy segment tree
template <typename T, T (*up)(T, T), T (*e)()>
class RPSegTree{
    private:
        int size;
        std::vector<T> arr;
        std::vector<bool> hold;
    public:
        RPSegtree(int size_, T initial){
            size = 1;
            while(size < size_){
                size *= 2;
            }
            arr = std::vector<T>(size*2, initial);
            hold = std::vector<bool>(size*2, false);
        }

        void update(int l, int r, T val){
            update_(l, r, 0, size, 1, val);
        }

        void update_(int l, int r, int a, int b, int u, T val){
            if(l <= a && b <= r){
                hold[u] = true;
                arr[u] = up(arr[u], val);
                return;
            }
            if(b <= l || a >= r) return;
            int m = (a+b)/2;
            propagate(u);
            update_(l, r, a, m, u*2, val);
            update_(l, r, m, b, u*2+1, val);       
        }

        void propagate(int u){
            if(!hold[u]) return;
            hold[u*2] = true;
            arr[u*2] = up(arr[u*2], arr[u]);
            hold[u*2+1] = true;
            arr[u*2+1] = up(arr[u*2+1], arr[u]);
            hold[u] = false;
        }

        T query(int u){
            u += size;
            int pos = 31 - __builtin_clz(u);
            int cur = 1;
            while(pos > 0){
                propagate(cur);
                pos--;
                cur <<= 1;
                cur += (u >> pos) & 1;
            }
            return arr[cur];
        }
};


// Range-Range lazy segment tree
template <typename T, T (*up)(T&, T&), T (*op)(T&, T&), T (*e)()>
class RRSegtree{
    private:
        int size;
        std::vector<T> hold;
        std::vector<T> arr;
    public:
        RRSegtree(int size_, T initial){
            size = 1;
            while(size < size_){
                size *= 2;
            }
            arr = std::vector<T>(size*2);
            for(int i = 0; i < size; i++) arr[i+size] = initial;
            for(int i = size-1; i > 0; i--) arr[i] = op(arr[i*2], arr[i*2+1]);
            hold = std::vector<T>(size*2, e());
        }

        void update(int l, int r, T val){
            update_(l, r, 0, size, 1, val);
        }

        void update_(int l, int r, int a, int b, int u, T val){
            if(l <= a && b <= r){
                hold[u] = up(hold[u], val);
                arr[u] = up(arr[u], val);
                return;
            }
            if(b <= l || a >= r) return;
            int m = (a+b)/2;
            propagate(u);
            update_(l, r, a, m, u*2, val);
            update_(l, r, m, b, u*2+1, val);
            arr[u] = op(arr[u*2], arr[u*2+1]);     
        }

        void propagate(int u){
            if(hold[u] == e()) return;
            hold[u*2] = up(hold[u*2], hold[u]);
            arr[u*2] = up(arr[u*2], hold[u]);
            hold[u*2+1] = up(hold[2*u+1], hold[u]);
            arr[u*2+1] = up(arr[u*2+1], hold[u]);
            hold[u] = e();
        }

        T query(int l, int r){
            return query_(l, r, 0, size, 1);
        }

        T query_(int l, int r, int a, int b, int u){
            if(a >= l && b <= r) return arr[u];
            if(a >= r || b <= l) return e();
            int m = (a+b)/2;
            propagate(u);
            T valLeft = query_(l, r, a, m, u*2);
            T valRight = query_(l, r, m, b, u*2+1);
            return op(valLeft,valRight);
        }
};