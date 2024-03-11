#include<vector>
#include<stdint.h>



class RMQ{
    private:
        std::vector<int> arr;
    
    public:
        int size;

        RMQ(int _size){
            this->size = 1;
            while(this->size < _size){
                this->size *= 2;
            }
            this->arr = std::vector<int>(this->size * 2, INT32_MAX);
        }

        RMQ(int _size, std::vector<int> initial){
            this->size = 1;
            while(this->size < _size){
                this->size *= 2;
            }
            this->arr = std::vector<int>(this->size * 2, 0);
            for(int i = 0; i < initial.size(); i++) this->arr[this->size + i] = initial[i];
            for(int i = this->size-1; i >= 1; i--) this->arr[i] = std::min(this->arr[i*2], this->arr[i*2+1]);
        }

        void update(int pos, int val){
            pos = this->size + pos - 1;
            arr[pos] = val;
            pos /= 2;
            while(pos > 0){
                arr[pos] = std::min(arr[pos*2], arr[pos*2+1]);
                pos /= 2;
            }
        }

        int query(int l, int r, int a, int b, int u){
            if(r <= a || b <= l) return INT32_MAX;
            if(l <= a && b <= r) return arr[u];
            int m = (a + b)/2;
            int ansL = query(l, r, a, m, u*2);
            int ansR = query(l, r, m, b, u*2+1);
            return std::min(ansL, ansR);
        }

        int get(int pos){
            return arr[this->size + pos -1];
        }
};