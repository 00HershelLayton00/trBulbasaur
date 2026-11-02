// BLOSSOM (Edmonds): matching maximo en grafo general no bipartito.
// add_edge agrega la arista en ambos sentidos. V ~ 500.
#include <bits/stdc++.h>
using namespace std;

struct Blossom {
    int n;
    vector<vector<int>> g;
    vector<int> match, p, base, q;
    vector<char> used, blossom;

    Blossom(int n_)
        : n(n_), g(n_), match(n_, -1), p(n_), base(n_), used(n_),
          blossom(n_) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int lca(int a, int b) {
        vector<char> seen(n, 0);
        while (true) {
            a = base[a];
            seen[a] = 1;
            if (match[a] == -1) break;
            a = p[match[a]];
        }
        while (true) {
            b = base[b];
            if (seen[b]) return b;
            b = p[match[b]];
        }
    }

    void mark_path(int v, int b, int child) {
        while (base[v] != b) {
            blossom[base[v]] = blossom[base[match[v]]] = 1;
            p[v] = child;
            child = match[v];
            v = p[match[v]];
        }
    }

    int find_path(int root) {
        used.assign(n, 0);
        p.assign(n, -1);
        for (int i = 0; i < n; ++i) base[i] = i;
        q.clear();
        q.push_back(root);
        used[root] = 1;

        for (int qi = 0; qi < (int)q.size(); ++qi) {
            int v = q[qi];
            for (int to : g[v]) {
                if (base[v] == base[to] || match[v] == to) continue;
                if (to == root ||
                    (match[to] != -1 && p[match[to]] != -1)) {
                    int cur = lca(v, to);
                    blossom.assign(n, 0);
                    mark_path(v, cur, to);
                    mark_path(to, cur, v);
                    for (int i = 0; i < n; ++i) {
                        if (blossom[base[i]]) {
                            base[i] = cur;
                            if (!used[i]) {
                                used[i] = 1;
                                q.push_back(i);
                            }
                        }
                    }
                } else if (p[to] == -1) {
                    p[to] = v;
                    if (match[to] == -1) return to;
                    to = match[to];
                    used[to] = 1;
                    q.push_back(to);
                }
            }
        }
        return -1;
    }

    int max_matching() {
        match.assign(n, -1);
        for (int i = 0; i < n; ++i) {
            if (match[i] != -1) continue;
            int v = find_path(i);
            while (v != -1) {
                int pv = p[v], ppv = match[pv];
                match[v] = pv;
                match[pv] = v;
                v = ppv;
            }
        }
        int ans = 0;
        for (int x : match) {
            if (x != -1) ++ans;
        }
        return ans / 2;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    Blossom bl(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        bl.add_edge(u, v);
    }

    cout << "Matching: " << bl.max_matching() << '\n';
    for (int i = 0; i < n; ++i) {
        if (i < bl.match[i]) cout << i << " - " << bl.match[i] << '\n';
    }
    return 0;
}
