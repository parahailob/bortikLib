#include <bits/stdc++.h>

namespace bortikLib {

    std::vector<long long> divisors(long long n){
        std::vector<long long> small;
        std::vector<long long> big;
        int i = 1;
        for(i = 1; i < sqrt(n); i++){
            if(n % i == 0){
                small.push_back(i);
                big.push_back(n / i);
            }
        }
        if(i * i == n) small.push_back(i);
        small.insert(small.end(), big.rbegin(), big.rend());
        return small;
    }

    bool is_prime(long long a){
        if(a == 2) return true;
        if(a < 2 || a % 2 == 0) return false;
        for(int i = 3; i <= sqrt(a); i += 2){
            if(a % i == 0) return false;
        }
        return true;
    }


    void Extend (uint32_t w[], uint32_t &w_end, uint32_t &length, uint32_t n, bool d[], uint32_t &w_end_max) {
        /* Rolls full wheel W up to n, and sets length=n */
        uint32_t i, j, x;
        i = 0; j = w_end;
        x = length + 1; /* length+w[0] */
        while (x <= n) {
            w[++j] = x; /* Append x to the ordered set W */
            d[x] = false;
            x = length + w[++i];
        }
        length = n; w_end = j;
        if (w_end > w_end_max) w_end_max = w_end;
    }

    void Delete (uint32_t w[], uint32_t length, uint32_t p, bool d[], uint32_t &imaxf) {
        /* Deletes multiples p*w[i] of p from W, and sets imaxf to last i for deletion */
        uint32_t i, x;
        i = 0;
        x = p; /* p*w[0]=p*1 */
        while (x <= length) {
            d[x] = true; /* Remove x from W; */
            x = p*w[++i];
        }
        imaxf = i-1;
    }

    void Compress(uint32_t w[], bool d[], uint32_t to, uint32_t &w_end) {
        /* Removes deleted values in w[0..to], and if to=w_end, updates w_end, otherwise pads with zeros on right */
        uint32_t i, j;
        j = 0;
        for (i=1; i <= to; i++) {
            if (!d[w[i]]) {
                w[++j] = w[i];
            }
        }
        if (to == w_end) {
            w_end = j;
        } else {
            for (uint32_t k=j+1; k <= to; k++) w[k] = 0;
        }
    }

    std::vector<uint32_t> Pritchard(uint32_t N) {
        /* finds the nrPrimes primes up to N, printing them if printPrimes */
        std::vector<uint32_t> result;
        uint32_t *w = new uint32_t[N/4+5];
        bool *d = new bool[N+1];
        uint32_t w_end, length;
        /* representation invariant (for the main loop): */
        /* if length < N (so W is a complete wheel), w[0..w_end] is the ordered set W; */
        /* otherwise, w[0..w_end], omitting zeros and values w with d[w] true, is the ordered set W, */
        /* and no values <= N/p are omitted */
        uint32_t w_end_max, p, imaxf;
        /* W,k,length = {1},1,2: */
        w_end = 0; w[0] = 1;
        w_end_max = 0;
        length = 2;
        /* Pr = {2}: */
        result.push_back(2);
        p = 3;
        /* invariant: p = p_(k+1) and W = W_k inter {1,...,N} and length = min(P_k,N) and Pr = the first k primes */
        /* (where p_i denotes the i'th prime, W_i denotes the i'th wheel, P_i denotes the product of the first i primes) */
        while (p*p <= N) {
            /* Append p to Pr: */
            result.push_back(p);
            if (length < N) {
                /* Extend W with length to minimum of p*length and N: */
                Extend (w, w_end, length, std::min(p*length,N), d, w_end_max);
            }
            Delete(w, length, p, d, imaxf);
            Compress(w, d, (length < N ? w_end : imaxf), w_end);
            /* p = next(W, 1): */
            p = w[1];
            if (p == 0) break; /* next p is after zeroed section so is too big */
            /* k++ */
        }
        if (length < N) {
            /* Extend full wheel W,length to N: */
            Extend (w, w_end, length, N, d, w_end_max);
        }
        /* gather remaining primes: */
        for (uint32_t i=1; i <= w_end; i++) {
            if (w[i] == 0 || d[w[i]]) continue;
            result.push_back(w[i]);
        }

        return result;
    }

    /*  prime_factor(n)
        入力：整数 n
        出力：nの素因数分解
        計算量：O(√n)前後
    */
    template <typename T>
    std::vector<std::pair<T, T>> prime_factor(T n) {
        std::vector<std::pair<T, T>> ret;
        for (T i = 2; i * i <= n; i++) {
            if (n % i != 0) continue;
            T tmp = 0;
            while (n % i == 0) {
                tmp++;
                n /= i;
            }
            ret.push_back(std::make_pair(i, tmp));
        }
        if (n != 1) ret.push_back(std::make_pair(n, 1));
        return ret;
    }

    /*  PrimeFact
        init(N): 初期化。O(N log log N)
        get(n): クエリ。素因数分解を求める。O(log n)
    */
    template <typename T>
    struct PrimeFact {
        std::vector<T> spf;
        PrimeFact(T N) { init(N); }
        void init(T N) { // 前処理。spf を求める
            spf.assign(N + 1, 0);
            for (T i = 0; i <= N; i++) spf[i] = i;
            for (T i = 2; i * i <= N; i++) {
                if (spf[i] == i) {
                    for (T j = i * i; j <= N; j += i) {
                        if (spf[j] == j) {
                            spf[j] = i;
                        }
                    }
                }
            }
        }
        std::map<T, T> get(T n) { // nの素因数分解を求める
            std::map<T, T> m;
            while (n != 1) {
                m[spf[n]]++;
                n /= spf[n];
            }
            return m;
        }
    };

}

template<typename T> 
unsigned long long inversion_merge_sort(vector<T> &arr, int l, int r){
    unsigned long long ans = 0;
    if(r - l < 2) return 0;

    int mid = (r + l)/2;
    ans += inversion_merge_sort(arr, l, mid);
    ans += inversion_merge_sort(arr, mid, r);

    int n = r-l;
    vector<T> sorted(n);
    int k1 = l;
    int k2 = mid;
    int idx = 0;
    while(k1 < mid && k2 < r){
        if(arr[k2] < arr[k1]){
            ans += mid - k1;
            sorted[idx] = arr[k2];
            k2++;
        } else {
            sorted[idx] = arr[k1];
            k1++;
        }
        idx++;
    }
    if(k1 < mid){
        for(int i = k1; i < mid; i++){
            sorted[idx] = arr[i];
            idx++;
        }
    } else {
        for(int i = k2; i < r; i++){
            sorted[idx] = arr[i];
            idx++;
        }
    }
    for(int i = 0; i < n; i++){
        arr[l+i] = sorted[i];
    }
    return ans;
}

template<typename T>
unsigned long long num_inv(vector<T> a){
    return inversion_merge_sort(a, 0, a.size());
}


long long grey_code(long long pos, int n){
    long long ans = 0;
    for(int j = n-1; j >= 0; j--) if(pos & (1 << j)) ans |= (1 << j), pos = (1 << (j+1))-1 - pos;
    return ans;
}

long long grey_reverse(long long val){
    long long k = 0;
    long long order = 0;
    for(int j = 61; j >= 0; j--) {k |= (val & (1 << j)) ^ (order << j); order ^= (val >> j) & 1;}
    return k;
}

template<typename T>
struct Combinatorics {
    vector<T> fact;

    Comb(int n) {
        fact.assign(n+1);
        fact[0] = T{1};
        fact[1] = T{1};
        for(int i = 2; i <= n; i++){
            fact[i] = fact[i-1] * T{i};
        }
    }

    T comb(int n, int r){
        return fact[n] / (fact[r] * fact[n-r]);
    }

    T perm(int n){
        return fact[n];
    }
};