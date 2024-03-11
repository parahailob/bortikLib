#include<algorithm>
#include<string>
#include<vector>
#include<iostream>
#include<array>



void count_sort(std::vector<int> &p, std::vector<int> &c){
    int n = p.size();
    std::vector<int> cnt(n, 0);
    for(auto &e: c) {
        cnt[e]++;
    }
    std::vector<int> pos(n);
    pos[0] = 0;
    for(int i = 1;i < n; i++) pos[i] = pos[i-1]+cnt[i-1];
    std::vector<int> p_new(n);
    for(auto &val: p){
        p_new[pos[c[val]]] = val;
        pos[c[val]]++;
    }
    p = p_new;
}

std::vector<int> suffix_array(const std::string &s){
    int n = s.size() + 1;
    std::vector<int> pos(n), equivalence(n);
    std::vector<std::pair<int,int>> a(n);
    for(int i = 0; i < n-1; i++) a[i] = {s[i], i};
    a[n-1] = {-1, n-1};
    sort(a.begin(), a.end());
    equivalence[0] = 0;
    pos[0] = a[0].second;
    for(int i = 1;i < n; i++){
        pos[i] = a[i].second;
        if(a[i].first == a[i-1].first){
            equivalence[a[i].second] = equivalence[a[i-1].second];
        } else {
            equivalence[a[i].second] = equivalence[a[i-1].second]+1;
        }
    }
    for(int k = 1; k < n; k *= 2){
        for(int &v: pos) v = (v+n-k)%n;
        count_sort(pos, equivalence);

        std::vector<int> new_eq(n);
        new_eq[pos[0]] = 0;
        for(int i = 1; i < n; i++){
            std::pair<int,int> prev = {equivalence[pos[i-1]], equivalence[(pos[i-1] + k)%n]};
            std::pair<int,int> cur = {equivalence[pos[i]], equivalence[(pos[i] + k)%n]};
            if(prev == cur){
                new_eq[pos[i]] = new_eq[pos[i-1]];
            } else {
                new_eq[pos[i]] = new_eq[pos[i-1]]+1;
            }
        }
        equivalence = new_eq;
    }

    return pos;
}

/// @brief determine whether target is a substring of src
/// @param src 
/// @param sufarr suffix array of src
/// @param target 
/// @return true if substring
bool findstr(const std::string &src, const std::vector<int> &sufarr, const std::string &target){
    int n = target.size();
    auto ele = std::lower_bound(sufarr.begin(), sufarr.end(), target,
        [&](const int &p, const std::string &t){
            return src.substr(p, n) < t;
        });
    if(*ele < src.size() && src.substr(*ele, n) == target){
        return true;
    } else {
        return false;
    }
}

int count_substr(const std::string &src, const std::vector<int> &sufarr, const std::string &target){
    int n = target.size();
    auto start = std::lower_bound(sufarr.begin(), sufarr.end(), target,
        [&](const int &p, const std::string &t){
            return src.substr(p, n) < t;
        });
    auto end = std::lower_bound(sufarr.begin(), sufarr.end(), target,
        [&](const int &p, const std::string &t){
            return src.substr(p, n) <= t;
        });
    return end - start;
}

/// @brief longest commong prefix array
/// @param s 
/// @return 
std::vector<int> lcp_build(std::string &s){
    int n = s.size() + 1;
    std::vector<int> pos(n), equivalence(n);
    std::vector<std::pair<int,int>> a(n);
    for(int i = 0; i < n-1; i++) a[i] = {s[i], i};
    a[n-1] = {-1, n-1};
    sort(a.begin(), a.end());
    equivalence[0] = 0;
    pos[0] = a[0].second;
    for(int i = 1;i < n; i++){
        pos[i] = a[i].second;
        if(a[i].first == a[i-1].first){
            equivalence[a[i].second] = equivalence[a[i-1].second];
        } else {
            equivalence[a[i].second] = equivalence[a[i-1].second]+1;
        }
    }
    for(int k = 1; k < n; k *= 2){
        for(int &v: pos) v = (v+n-k)%n;
        count_sort(pos, equivalence);

        std::vector<int> new_eq(n);
        new_eq[pos[0]] = 0;
        for(int i = 1; i < n; i++){
            std::pair<int,int> prev = {equivalence[pos[i-1]], equivalence[(pos[i-1] + k)%n]};
            std::pair<int,int> cur = {equivalence[pos[i]], equivalence[(pos[i] + k)%n]};
            if(prev == cur){
                new_eq[pos[i]] = new_eq[pos[i-1]];
            } else {
                new_eq[pos[i]] = new_eq[pos[i-1]]+1;
            }
        }
        equivalence = new_eq;
    }

    std::vector<int> lcp(n);
    int k = 0;
    for(int i = 0; i < n-1; i++){
        int pi = equivalence[i];
        int j = pos[pi-1];
        while(s[i + k] == s[j + k]) k++;
        lcp[pi] = k;
        k = std::max(k-1, 0);
    }

    return lcp;

}

// number of unique substrings in s
long long diff_substr(std::string &s){
    int n = s.size() + 1;
    std::vector<int> pos(n), equivalence(n);
    std::vector<std::pair<int,int>> a(n);
    for(int i = 0; i < n-1; i++) a[i] = {s[i], i};
    a[n-1] = {-1, n-1};
    sort(a.begin(), a.end());
    equivalence[0] = 0;
    pos[0] = a[0].second;
    for(int i = 1;i < n; i++){
        pos[i] = a[i].second;
        if(a[i].first == a[i-1].first){
            equivalence[a[i].second] = equivalence[a[i-1].second];
        } else {
            equivalence[a[i].second] = equivalence[a[i-1].second]+1;
        }
    }
    for(int k = 1; k < n; k *= 2){
        for(int &v: pos) v = (v+n-k)%n;
        count_sort(pos, equivalence);

        std::vector<int> new_eq(n);
        new_eq[pos[0]] = 0;
        for(int i = 1; i < n; i++){
            std::pair<int,int> prev = {equivalence[pos[i-1]], equivalence[(pos[i-1] + k)%n]};
            std::pair<int,int> cur = {equivalence[pos[i]], equivalence[(pos[i] + k)%n]};
            if(prev == cur){
                new_eq[pos[i]] = new_eq[pos[i-1]];
            } else {
                new_eq[pos[i]] = new_eq[pos[i-1]]+1;
            }
        }
        equivalence = new_eq;
    }

    std::vector<int> lcp(n);
    int k = 0;
    for(int i = 0; i < n-1; i++){
        int pi = equivalence[i];
        int j = pos[pi-1];
        while(s[i + k] == s[j + k]) k++;
        lcp[pi] = k;
        k = std::max(k-1, 0);
    }

    long long ans = 0;
    for(int i = 1; i < n; i++){
        ans += (n - pos[i] - 1) - lcp[i];
    }

    return ans;

}

std::string longest_common_substr(std::string &str1, std::string &str2){
    std::string s = str1 + '$' + str2;
    int n = s.size() + 1;
    std::vector<int> pos(n), equivalence(n);
    std::vector<std::pair<int,int>> a(n);
    for(int i = 0; i < n-1; i++) a[i] = {s[i], i};
    a[n-1] = {-1, n-1};
    sort(a.begin(), a.end());
    equivalence[0] = 0;
    pos[0] = a[0].second;
    for(int i = 1;i < n; i++){
        pos[i] = a[i].second;
        if(a[i].first == a[i-1].first){
            equivalence[a[i].second] = equivalence[a[i-1].second];
        } else {
            equivalence[a[i].second] = equivalence[a[i-1].second]+1;
        }
    }
    for(int k = 1; k < n; k *= 2){
        for(int &v: pos) v = (v+n-k)%n;
        count_sort(pos, equivalence);

        std::vector<int> new_eq(n);
        new_eq[pos[0]] = 0;
        for(int i = 1; i < n; i++){
            std::pair<int,int> prev = {equivalence[pos[i-1]], equivalence[(pos[i-1] + k)%n]};
            std::pair<int,int> cur = {equivalence[pos[i]], equivalence[(pos[i] + k)%n]};
            if(prev == cur){
                new_eq[pos[i]] = new_eq[pos[i-1]];
            } else {
                new_eq[pos[i]] = new_eq[pos[i-1]]+1;
            }
        }
        equivalence = new_eq;
    }

    std::vector<int> lcp(n);
    int k = 0;
    for(int i = 0; i < n-1; i++){
        int pi = equivalence[i];
        int j = pos[pi-1];
        while(s[i + k] == s[j + k]) k++;
        lcp[pi] = k;
        k = std::max(k-1, 0);
    }

    int l = str1.size();
    int m = 0;
    int ind = 0;
    for(int i = 1; i < n; i++){
        if((pos[i] > l && pos[i-1] < l) || (pos[i] < l && pos[i-1] > l)){
            if(m < lcp[i]){
                m = lcp[i];
                ind = pos[i];
            }
        }
    }
    std::string result = s.substr(ind, m);
    return result;
}


std::vector<int> kmp_table(const std::string &w){
    std::vector<int> T(w.size()+1, 0);
    int pos = 1, cnd = 0;
    T[0] = -1;
    while(pos < w.size()){
        if(w[pos] == w[cnd]){
            T[pos] = T[cnd];
        } else {
            T[pos] = cnd;
            while(cnd >= 0 and w[pos] != w[cnd]){
                cnd = T[cnd];
            }
        }
        pos++;
        cnd++;
    }
    T[pos] = cnd;
    return T;
}

std::vector<int> kmp_search(const std::string &text, const std::string &w){
    std::vector<int> result;
    std::vector<int> T = kmp_table(w);
    int k = 0;
    int j = 0;

    while(j < text.size()){
        if(w[k] == text[j]){
            j++;
            k++;
            if(k == w.size()){
                result.push_back(j-k);
                k = T[k];
            }
        } else {
            k = T[k];
            if(k < 0){
                j++;
                k++;
            }
        }
    }

    return result;
}

int main(){
    std::string s, t;
    std::cin >> s >> t;
    std::cout << longest_common_substr(s, t);
}
