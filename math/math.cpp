#pragma once
#include <bits/stdc++.h>

namespace bortikLib {

    template<typename T>
    std::vector<T> divisors(T n){
        assert(std::is_integral_v<T>);
        std::vector<T> small;
        std::vector<T> big;
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

    // https://cp-algorithms.com/algebra/prime-sieve-linear.html
    // Linear prime sieve
#if __cplusplus >= 202002L
    template<std::integral T>
#else 
    template<typename T>
#endif
    std::vector<T> get_primes(int N){
        assert(N >= 0);
        assert(std::is_integral_v<T>);
        std::vector<T> lp(N+1);
        std::vector<T> pr;

        for (T i=2; i <= N; ++i) {
            if (lp[i] == 0) {
                lp[i] = i;
                pr.push_back(i);
            }
            for (T j = 0; i * pr[j] <= N; ++j) {
                lp[i * pr[j]] = pr[j];
                if (pr[j] == lp[i]) {
                    break;
                }
            }
        }

        return pr;
    }

    template<typename T> 
    unsigned long long inversion_merge_sort(std::vector<T> &arr, int l, int r){
        unsigned long long ans = 0;
        if(r - l < 2) return 0;

        int mid = (r + l)/2;
        ans += inversion_merge_sort(arr, l, mid);
        ans += inversion_merge_sort(arr, mid, r);

        int n = r-l;
        std::vector<T> sorted(n);
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
    unsigned long long num_inv(std::vector<T> a){
        return inversion_merge_sort<T>(a, 0, a.size());
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
        std::vector<T> fact;

        Combinatorics(int n) {
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


    // returns a vector [a0; a1, ...] of repeated infinite fraction of sqrt(D)
    template<typename T>
    std::vector<T> continued_fraction(T D){
        std::vector<T> a, p, q, P, Q;
        a.push_back(T(sqrt(D)));
        p.push_back(a[0]);
        q.push_back(0);
        P.push_back(0);
        Q.push_back(1);
        while(a.back() != a[0]*2){
            P.push_back(a.back()*Q.back()-P.back());
            Q.push_back((D-P.back()*P.back())/Q.back());
            a.push_back((a[0]+P.back())/Q.back());
        }
        return a;
    }

    // the solution to Pell`s Equation in smallest integers
    template<typename T>
    std::pair<T,T> pell_smallest(T D){
        auto a = continued_fraction(D);
        int r = a.size()-2;
        if(r%2==1){
            std::vector<T> p, q;
            p.push_back(a[0]);
            p.push_back(a[0]*a[1]+1);
            q.push_back(1);
            q.push_back(a[1]);
            for(int n = 2; n <= r; n++) p.push_back(a[n] * p[n-1] + p[n-2]);
            for(int n = 2; n <= r; n++) q.push_back(a[n] * q[n-1] + q[n-2]);
            return std::make_pair(p[r], q[r]);
        } else {
            std::vector<T> p, q;
            p.push_back(a[0]);
            p.push_back(a[0]*a[1]+1);
            q.push_back(1);
            q.push_back(a[1]);
            for(int n = 2; n <= 2*r+1; n++){
                if(n <= r+1) p.push_back(a[n] * p[n-1] + p[n-2]);
                else p.push_back(a[n-r-1]*p[n-1] + p[n-2]);
            }
            for(int n = 2; n <= 2*r+1; n++){
                if(n <= r+1) q.push_back(a[n] * q[n-1] + q[n-2]);
                else q.push_back(a[n-r-1]*q[n-1] + q[n-2]);
            }
            return std::make_pair(p[2*r+1], q[2*r+1]);
        }

    }

    template<typename T>
    std::vector<T> z_tranform(const std::vector<T> &A, int n){
        std::vector<T> F(1<<n, 0);
        for(int i = 0; i < (1<<n); i++) F[i] = A[i];
        for(int i = 0; i < n; i++)
            for(int mask = 0; mask < (1<<n); mask++){
                if(mask & (1<<i)) F[mask] += F[mask^(1<<i)];
            }
        
        return F;
    }

    template<typename T>
    void apply_z_tranform(std::vector<T> &F, int n){
        for(int i = 0; i < n; i++)
            for(int mask = 0; mask < (1<<n); mask++){
                if(mask & (1<<i)) F[mask] += F[mask^(1<<i)];
            }
    }

    template<typename T>
    void apply_odd_negation(std::vector<T> &F, int n){
        for(int mask = 0; mask < (1<<n); mask++)
            if(__builtin_popcount(mask)%2==1) F[mask] *= 1;
    }

    template<typename T> 
    void inv_z_transform(std::vector<T> &F, int n){
        for(int i = 0; i < n; i++) {
            for(int mask = 0; mask < (1 << n); mask++) {
                if((mask & (1 << i)) != 0) {
                    F[mask] -= F[mask ^ (1 << i)];
                }
            }
        }
    }

    template<typename T>
    std::vector<T> moebius_transform(std::vector<T> F, int n){
        apply_odd_negation(F, n);
        apply_z_tranform(F, n);
        apply_odd_negation(F, n);
        return F;
    }

    template<typename T>
    void apply_moebius_transform(std::vector<T> &F, int n){
        apply_odd_negation(F, n);
        apply_z_tranform(F, n);
        apply_odd_negation(F, n);
    }

}
