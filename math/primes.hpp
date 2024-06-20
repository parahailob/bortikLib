#pragma once
#include <cstdint>
#include <random>
#include <chrono>

bool naive_prime(uint64_t n){
    if(n < 2) return false;
    if(n == 2) return true;
    if(n%2==0) return false;
    for(uint64_t i = 3; i*i <= n; i+=2){
        if(n % i == 0) return false;
    }

    return true;
}

uint64_t binpower(uint64_t base, uint64_t e, uint64_t mod) {
    uint64_t result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (__uint128_t)result * base % mod;
        base = (__uint128_t)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(uint64_t n, uint64_t a, uint64_t d, int s) {
    uint64_t x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (__uint128_t)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

// https://cp-algorithms.com/algebra/primality_tests.html
bool MillerRabin(uint64_t n) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;

    int r = 0;
    uint64_t d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

// Finds a random prime in range [low, high]
uint64_t random_prime(uint64_t low, uint64_t high){
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

    uint64_t range = high-low+1;
    uint64_t number = low + rng()%range;
    while(!MillerRabin(number))
        number = low + rng()%range;
    
    return number;
}