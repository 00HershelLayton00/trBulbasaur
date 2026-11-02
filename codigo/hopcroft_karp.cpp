// HOPCROFT-KARP: matching maximo en grafo bipartito.
// Izquierda: 0..n-1. Derecha: 0..m-1 (se guardan como n+v si hace falta).
#include <bits/stdc++.h>
using namespace std;

struct HopcroftKarp {
    int n, m;
    vector<vector<int>> adj;
    vector<int> pairU, pairV, dist;

    HopcroftKarp(int n_, int m_)
        : n(n_), m(m_), adj(n_), pairU(n_, -1), pairV(m_, -1),
          dist(n_) {}

    void add_edge(int u, int v) { adj[u].push_back(v); }

    bool bfs() {
        queue<int> q;
        for (int u = 0; u < n; ++u) {
            if (pairU[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = -1;
            }
        }
        bool found = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                int u2 = pairV[v];
                if (u2 == -1) {
                    found = true;
                } else if (dist[u2] == -1) {
                    dist[u2] = dist[u] + 1;
                    q.push(u2);
                }
            }
        }
        return found;
    }

    bool dfs(int u) {
        for (int v : adj[u]) {
            int u2 = pairV[v];
            if (u2 == -1 || (dist[u2] == dist[u] + 1 && dfs(u2))) {
                pairU[u] = v;
                pairV[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }

    int max_matching() {
        int matching = 0;
        while (bfs()) {
            for (int u = 0; u < n; ++u) {
                if (pairU[u] == -1 && dfs(u)) ++matching;
            }
        }
        return matching;
    }

    // Vertices 0..n-1 = izquierda; n..n+m-1 = derecha.
    vector<int> min_vertex_cover() const {
        vector<char> visU(n, 0), visV(m, 0);
        queue<int> q;
        for (int u = 0; u < n; ++u) {
            if (pairU[u] == -1) {
                visU[u] = 1;
                q.push(u);
            }
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (pairU[u] == v) continue;  // solo aristas no matching
                if (visV[v]) continue;
                visV[v] = 1;
                if (pairV[v] != -1 && !visU[pairV[v]]) {
                    visU[pairV[v]] = 1;
                    q.push(pairV[v]);
                }
            }
        }
        vector<int> cover;
        for (int u = 0; u < n; ++u) {
            if (!visU[u]) cover.push_back(u);
        }
        for (int v = 0; v < m; ++v) {
            if (visV[v]) cover.push_back(n + v);
        }
        return cover;
    }

    vector<int> max_independent_set() const {
        vector<int> cover = min_vertex_cover();
        vector<char> used(n + m, 0);
        for (int x : cover) used[x] = 1;
        vector<int> ans;
        for (int i = 0; i < n + m; ++i) {
            if (!used[i]) ans.push_back(i);
        }
        return ans;
    }
};

// Cobertura minima de caminos en un DAG: n - matching.
int min_path_cover_dag(int n, const vector<pair<int, int>>& edges) {
    HopcroftKarp hk(n, n);
    for (auto [u, v] : edges) hk.add_edge(u, v);
    return n - hk.max_matching();
}

int main() {
    int n, m, e;
    cin >> n >> m >> e;
    HopcroftKarp hk(n, m);
    while (e--) {
        int u, v;
        cin >> u >> v;
        hk.add_edge(u, v);
    }

    cout << "Matching: " << hk.max_matching() << '\n';
    vector<int> cover = hk.min_vertex_cover();
    cout << "Vertices del cover: " << cover.size() << '\n';
    for (int x : cover) cout << x << ' ';
    cout << '\n';

    vector<int> indep = hk.max_independent_set();
    cout << "Independiente: " << indep.size() << '\n';
    return 0;
}
