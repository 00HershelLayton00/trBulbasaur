// GRUNDY / SPRAUGE-GRUNDY.
// Juego imparcial sin ciclos: gana quien no puede mover pierde.
// El SG de una posicion es el mex de los SG de sus sucesoras.
// Varias componentes independientes se combinan con XOR de sus SG.
#include <bits/stdc++.h>
using namespace std;

// Menor entero no negativo que no esta en v.
int mex(const vector<int>& v) {
    vector<char> seen(v.size() + 1, 0);
    for (int x : v) {
        if (x >= 0 && x <= (int)v.size()) seen[x] = 1;
    }
    int g = 0;
    while (g < (int)seen.size() && seen[g]) ++g;
    return g;
}

// Grafo dirigido sin ciclos. g[v] = estados a los que se puede mover.
struct GrundyDAG {
    int n;
    vector<vector<int>> g;
    GrundyDAG(int n_) : n(n_), g(n_) {}
    void add_edge(int u, int v) { g[u].push_back(v); }

    // Devuelve sg[v] para cada estado. Si hay un ciclo, devuelve {}.
    vector<int> calc() const {
        vector<int> indeg(n, 0), order;
        for (int u = 0; u < n; ++u) {
            for (int v : g[u]) ++indeg[v];
        }
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (indeg[i] == 0) q.push(i);
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            order.push_back(u);
            for (int v : g[u]) {
                if (--indeg[v] == 0) q.push(v);
            }
        }
        if ((int)order.size() != n) return {};

        vector<int> sg(n, 0), mark(n + 1, 0);
        int stamp = 0;
        for (int i = n - 1; i >= 0; --i) {
            int u = order[i];
            ++stamp;
            for (int v : g[u]) {
                if (sg[v] <= n) mark[sg[v]] = stamp;
            }
            int x = 0;
            while (mark[x] == stamp) ++x;
            sg[u] = x;
        }
        return sg;
    }
};

// Juego de una pila: desde x se puede quitar cualquier move <= x.
vector<int> subtraction_grundy(int max_n, const vector<int>& moves) {
    vector<int> sg(max_n + 1, 0), mark(max_n + 1, 0);
    for (int x = 1; x <= max_n; ++x) {
        for (int mv : moves) {
            if (mv <= x) mark[sg[x - mv]] = x;
        }
        int g = 0;
        while (mark[g] == x) ++g;
        sg[x] = g;
    }
    return sg;
}

int main() {
    int n, m;
    cin >> n >> m;  // pila inicial y cantidad de movimientos
    vector<int> moves(m);
    for (int &x : moves) cin >> x;

    vector<int> sg = subtraction_grundy(n, moves);
    cout << "SG(" << n << ") = " << sg[n] << '\n';
    cout << (sg[n] ? "Gana el primero" : "Gana el segundo") << '\n';
    return 0;
}
