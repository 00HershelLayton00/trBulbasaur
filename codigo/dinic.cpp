// DINIC: flujo maximo y corte minimo en un grafo dirigido.
// Las capacidades son long long. Para flujo con capacidades unitarias
// en redes bipartitas, Hopcroft-Karp suele ser mas simple y rapido.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Dinic {
    struct Edge {
        int to, rev;
        ll cap;
    };
    struct Raw {
        int u, v;
        ll cap;
    };

    int n;
    vector<vector<Edge>> g;
    vector<Raw> raw;
    vector<int> level, it;

    Dinic(int n_) : n(n_), g(n_), level(n_), it(n_) {}

    void add_edge(int u, int v, ll cap) {
        raw.push_back({u, v, cap});
        Edge a{v, (int)g[v].size(), cap};
        Edge b{u, (int)g[u].size(), 0};
        g[u].push_back(a);
        g[v].push_back(b);
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (const Edge &e : g[v]) {
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    ll dfs(int v, int t, ll pushed) {
        if (v == t) return pushed;
        for (int &i = it[v]; i < (int)g[v].size(); ++i) {
            Edge &e = g[v][i];
            if (e.cap == 0 || level[e.to] != level[v] + 1) continue;
            ll got = dfs(e.to, t, min(pushed, e.cap));
            if (got == 0) continue;
            e.cap -= got;
            g[e.to][e.rev].cap += got;
            return got;
        }
        return 0;
    }

    ll max_flow(int s, int t) {
        ll flow = 0;
        const ll INF = (1LL << 60);
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            while (ll got = dfs(s, t, INF)) flow += got;
        }
        return flow;
    }

    // Lado S del corte minimo despues de calcular max_flow.
    vector<char> min_cut(int s) const {
        vector<char> vis(n, 0);
        queue<int> q;
        vis[s] = 1;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (const Edge &e : g[v]) {
                if (e.cap > 0 && !vis[e.to]) {
                    vis[e.to] = 1;
                    q.push(e.to);
                }
            }
        }
        return vis;
    }

    // Aristas originales que cruzan el corte S -> T.
    vector<pair<int, int>> cut_edges(int s) const {
        vector<char> side = min_cut(s);
        vector<pair<int, int>> ans;
        for (const Raw &e : raw) {
            if (side[e.u] && !side[e.v]) ans.push_back({e.u, e.v});
        }
        return ans;
    }
};

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    Dinic din(n);
    while (m--) {
        int u, v;
        ll c;
        cin >> u >> v >> c;
        din.add_edge(u, v, c);
    }

    cout << "Flujo maximo: " << din.max_flow(s, t) << '\n';
    vector<pair<int, int>> cut = din.cut_edges(s);
    cout << "Aristas del corte: " << cut.size() << '\n';
    for (auto [u, v] : cut) cout << u << " -> " << v << '\n';
    return 0;
}
