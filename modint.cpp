

#include<utility>
#include<cassert>

namespace bortikLib{

    // @param m `1 <= m`
    // @return x mod m
    constexpr long long safe_mod(long long x, long long m) {
        x %= m;
        if (x < 0) x += m;
        return x;
    }

    // @param b `1 <= b`
    // @return pair(g, x) s.t. g = gcd(a, b), xa = g (mod b), 0 <= x < b/g
    constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
        a = safe_mod(a, b);
        if (a == 0) return {b, 0};
        long long s = b, t = a;
        long long m0 = 0, m1 = 1;
        while (t) {
            long long u = s / t;
            s -= t * u;
            m0 -= m1 * u;  // |m1 * u| <= |m1| * s <= b
            auto tmp = s;
            s = t;
            t = tmp;
            tmp = m0;
            m0 = m1;
            m1 = tmp;
        }
        if (m0 < 0) m0 += b / s;
        return {s, m0};
    }
    constexpr long long pow_mod_constexpr(long long x, long long n, int m) {
        if (m == 1) return 0;
        unsigned int _m = (unsigned int)(m);
        unsigned long long r = 1;
        unsigned long long y = safe_mod(x, m);
        while (n) {
            if (n & 1) r = (r * y) % _m;
            y = (y * y) % _m;
            n >>= 1;
        }
        return r;
    }
    constexpr bool is_prime_constexpr(int n) {
        if (n <= 1) return false;
        if (n == 2 || n == 7 || n == 61) return true;
        if (n % 2 == 0) return false;
        long long d = n - 1;
        while (d % 2 == 0) d /= 2;
        constexpr long long bases[3] = {2, 7, 61};
        for (long long a : bases) {
            long long t = d;
            long long y = pow_mod_constexpr(a, t, n);
            while (t != n - 1 && y != 1 && y != n - 1) {
                y = y * y % n;
                t <<= 1;
            }
            if (y != n - 1 && t % 2 == 0) {
                return false;
            }
        }
        return true;
    }
    template <int n> constexpr bool is_prime = is_prime_constexpr(n);

    template <int m>
    struct modint{

        using mint  = modint;

        public:

            static constexpr int mod() { return m; }
            static mint raw(int v) {
                mint x;
                x._v = v;
                return x;
            }

            modint() : _v(0) {}
            template<class T>
            modint(T v) {
                long long x = (long long)(v % (long long)(umod()));
                if(x < 0) x += umod();
                _v = (unsigned int)(x);
            }

            unsigned int val() const { return _v; }

            mint& operator--(){
                if(_v == 0) _v = umod();
                _v--;
                return *this;
            }
            mint& operator++(){
                _v++;
                if(_v == umod()) _v = 0;
                return *this;
            }
            mint& operator++(int) {
                mint result = *this;
                ++*this;
                return result;
            }
            mint& operator--(int){
                mint result = *this;
                --*this;
                return result;
            }
            mint& operator+=(const mint& rhs){
                _v += rhs._v;
                if(_v >= umod()) _v -= umod();
                return *this;
            }
            mint& operator-=(const mint& rhs){
                _v -= rhs._v;
                if(_v >= umod()) _v += umod();
                return *this;
            }
            mint& operator*=(const mint& rhs){
                unsigned long long z = _v;
                z *= rhs._v;
                _v = (unsigned int)(z % umod());
                return *this;
            }

            mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }

            mint operator+() const { return *this; }
            mint operator-() const { return mint() - *this; }

            mint pow(long long n) const {
                assert(0 <= n);
                mint x = *this, r = 1;
                while (n) {
                    if (n & 1) r *= x;
                    x *= x;
                    n >>= 1;
                }
                return r;
            }
            mint inv() const {
                if (prime) {
                    assert(_v);
                    return pow(umod() - 2);
                } else {
                    auto eg = inv_gcd(_v, m);
                    assert(eg.first == 1);
                    return eg.second;
                }
            }

        friend mint operator+(const mint& lhs, const mint& rhs) {
            return mint(lhs) += rhs;
        }
        friend mint operator-(const mint& lhs, const mint& rhs) {
            return mint(lhs) -= rhs;
        }
        friend mint operator*(const mint& lhs, const mint& rhs) {
            return mint(lhs) *= rhs;
        }
        friend mint operator/(const mint& lhs, const mint& rhs) {
            return mint(lhs) /= rhs;
        }
        friend bool operator==(const mint& lhs, const mint& rhs) {
            return lhs._v == rhs._v;
        }
        friend bool operator!=(const mint& lhs, const mint& rhs) {
            return lhs._v != rhs._v;
        }


        private:

            unsigned int _v;
            static constexpr unsigned int umod() { return m; }      
            static constexpr bool prime = is_prime<m>;
    };
    using modint998244353 = modint<998244353>;
    using modint1000000007 = modint<1000000007>;


}
