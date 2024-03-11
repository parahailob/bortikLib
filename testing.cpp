#include<bits/stdc++.h>
#include<graphs/graph.cpp>

using namespace std;
using namespace bortikLib;

#define i64 int64_t
#define i32 int32_t


int main(){
    i32 n, e; cin >> n >> e;
    Graph<i32> G(n, false);
    for(int i = 0; i < e; i++){
        int s,t,w; cin >> s >>t >> w;
        G.add_edge(s, t, w);
    }
    cout << MST_length(G);
}