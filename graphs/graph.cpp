#include<vector>
#include<algorithm>
#include<cstdint>
#include<queue>

#define i64 int64_t
#define i32 int32_t


namespace bortikLib{

/// @brief Edge struct for graphs
/// @tparam T weight type
template<typename T>
struct Edge {
    int src;
    int to;
    T weight;

    Edge(int _src, int _to, T _weight): to(_to), src(_src), weight(_weight) {};
};

/// @brief Graph struct
/// @tparam T weight type
template<typename T>
struct Graph {
    int N;
    int E;
    bool is_directed;
    std::vector<std::vector<Edge<T>>> edges;

    Graph(int _N, bool _is_directed = true): N(_N), E(0), is_directed(_is_directed) {
        edges = std::vector<std::vector<Edge<T>>>(_N);
    };

    void add_edge(int from, int to, int weight = 1){
        edges[from].push_back(Edge{from, to, weight});
        if(!is_directed) edges[to].push_back(Edge{to, from, weight});
        E++;
    }

    std::vector<Edge<T>> get_edges(){
        std::vector<Edge<T>> result;
        result.reserve(E);
        for(int i = 0; i < N; i++){
            result.insert(result.end(), edges[i].begin(), edges[i].end());
        }
        return result;
    }

};

/// @brief Breadth-first search
/// @tparam T type of weight
/// @param G graph
/// @param s starting node number
/// @return distance from s, parent vector
template<typename T>
std::pair<std::vector<i32>, std::vector<i32>> bfs(const Graph<T> &G, int s){
    std::vector<i32> dist(G.N, -1);
    std::vector<i32> parent(G.N, -1);
    dist[s] = 0;
    std::queue<i32> q;
    bool seen[G.N] = {};
    seen[s] = true;
    q.push(s);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(const auto& e: G.edges[u]){
            int v = e.to;
            if(!seen[v]){
                q.push(v);
                dist[v] = dist[u]+1;
                seen[v] = true;
                parent[v] = u;
            }
        }
    }

    return std::make_pair(dist, parent);
}

// Disjoint Set Union, aka UnionFind
class UnionFind{
    private:
        std::vector<int> parent;
        std::vector<int> siz;
    
    public:
        UnionFind(const int &size){
            parent = std::vector<int>(size+1, -1);
            siz = std::vector<int>(size+1, 0);
        }

        // employs path compression speedup
        int root(int u){
            int v = u;
            while(parent[v] != -1){
                v = parent[v];
            }
            int nxt = u;
            while(parent[u] != -1){
                nxt = parent[u];
                parent[u] = v;
                u = nxt;
            }
            return u;
        }

        void unite(const int &u, const int &v){
            int RootU = root(u);
            int RootV = root(v);
            if(RootU == RootV) return;
            if(siz[RootU] < siz[RootV]){
                parent[RootU] = RootV;
                siz[RootV] += siz[RootU] + 1;
            } else {
                parent[RootV] = RootU;
                siz[RootU] += siz[RootV] + 1;
            }
        }

        bool same(const int &u, const int &v){
            return root(u) == root(v);
        }
};


// Total length of edges in MST
template<typename T>
long long MST_length(std::vector<Edge<T>> Edges, int N){
    std::sort(Edges.begin(), Edges.end(), [](const Edge<T>& lhs, const Edge<T>& rhs){ return lhs.weight < rhs.weight; });
    long long result = 0;
    UnionFind uf(N);
    for(const auto&[u, v, w]: Edges){
        if(!uf.same(u, v)){
            result += w;
            uf.unite(u ,v);
        }
    }

    return result;
}

template<typename T>
i64 MST_length(Graph<T> &G){
    return MST_length(G.get_edges(), G.N);
}

// MST as a graph
// std::vector<std::vector<int>> MST_graph(std::vector<edge> Edges, int N){
//     std::sort(Edges.begin(), Edges.end(), [](const edge& lhs, const edge& rhs){ return lhs.weight < rhs.weight; });
//     std::vector<std::vector<int>> result(N+1);
//     UnionFind uf(N);
//     for(const auto&[w, u, v]: Edges){
//         if(!uf.same(u, v)){
//             result[u].push_back(v);
//             result[v].push_back(u);
//             uf.unite(u ,v);
//         }
//     }

//     return result;
// }





class WeightedUnionFind{
    private:
        std::vector<int> parent;
        std::vector<int> siz;
        std::vector<int> weightdiff;
    
    public:
        WeightedUnionFind(const int &size){
            parent = std::vector<int>(size+1, -1);
            siz = std::vector<int>(size+1, 0);
            weightdiff = std::vector<int>(size+1, 0);
        }

        int root(int u){
            while(parent[u] != -1){
                u = parent[u];
            }
            return u;
        }

        int toroot(int u){
            int res = 0;
            while(parent[u] != -1){
                res += weightdiff[u];
                u = parent[u];
            }
            return res;        
        }

        void relate(const int &u, const int &v, const int &d){
            int RootU = root(u);
            int RootV = root(v);
            if(RootU == RootV) return;
            if(siz[RootU] < siz[RootV]){
                parent[RootU] = RootV;
                weightdiff[RootU] = (toroot(v) - toroot(u)) - d;
                siz[RootV] += siz[RootU] + 1;
            } else {
                parent[RootV] = RootU;
                weightdiff[RootV] = (toroot(u) - toroot(v)) + d;
                siz[RootU] += siz[RootV] + 1;
            }
        }

        bool same(const int &u, const int &v){
            return root(u)==root(v);
        }

        int diff(const int &u, const int &v){
            return toroot(u)-toroot(v);
        }
};

std::vector<i64> dijkstra(const std::vector<std::vector<std::pair<i32, i64>>> &G, int source){
    int n = G.size();
    std::vector<i64> dist(n, INT64_MAX);
    dist[source] = 0;
    std::priority_queue<std::pair<i64, i32>,std::vector<std::pair<i64, i32>>, std::greater<std::pair<i64, i32>>> q;
    q.push(std::make_pair(0, source));
    std::vector<bool> seen(n, false);
    while(!q.empty()){
        int u = q.top().second;
        q.pop();
        if(seen[u]) continue;
        seen[u] = true;
        for(auto const& [v, w]: G[u]){
            if(!seen[v] && dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                q.push(std::make_pair(dist[v], v));
            }
        }
    }

    return dist;
}

std::pair<std::vector<i64>, std::vector<i32>> dijkstra_parent(const std::vector<std::vector<std::pair<i32, i64>>> &G, int source){
    int n = G.size();
    std::vector<i64> dist(n, INT64_MAX);
    std::vector<i32> parent(n, -1);
    dist[source] = 0;
    std::priority_queue<std::pair<i64, i32>,std::vector<std::pair<i64, i32>>, std::greater<std::pair<i64, i32>>> q;
    q.push(std::make_pair(0, source));
    std::vector<bool> seen(n, false);
    while(!q.empty()){
        int u = q.top().second;
        q.pop();
        if(seen[u]) continue;
        seen[u] = true;
        for(auto const& [v, w]: G[u]){
            if(!seen[v] && dist[v] > dist[u] + w){
                parent[v] = u;
                dist[v] = dist[u] + w;
                q.push(std::make_pair(dist[v], v));
            }
        }
    }

    return make_pair(dist, parent);
}


i64 tree_diameter(const std::vector<std::vector<std::pair<i32, i64>>> &G){
    i32 N = G.size();
    std::vector<i64> d1 = dijkstra(G, 0);
    i32 node1 = std::distance(d1.begin(), std::max_element(d1.begin(), d1.end()));
    d1 = dijkstra(G, node1);
    i64 result = *std::max_element(d1.begin(), d1.end());
    return result;
}

std::pair<i64, std::vector<i32>> tree_diameter_path(const std::vector<std::vector<std::pair<i32, i64>>> &G){
    i32 N = G.size();
    std::vector<i64> d1 = dijkstra(G, 0);
    i32 node1 = std::distance(d1.begin(), std::max_element(d1.begin(), d1.end()));
    auto [dist, p] = dijkstra_parent(G, node1);
    auto diameter = std::max_element(dist.begin(), dist.end());
    i32 node2 = std::distance(dist.begin(), diameter);
    std::vector<i32> path;
    path.push_back(node2);
    while(p[node2] != -1){
        path.push_back(p[node2]);
        node2 = p[node2];
    }

    return make_pair(*diameter, path);
}

}
