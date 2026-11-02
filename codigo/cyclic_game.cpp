// JUEGOS CON CICLOS: analisis retrogrado.
// Los estados sin movimientos son perdedores. Un estado es ganador
// si puede mover a uno perdedor; es perdedor si todos sus movimientos
// llevan a estados ganadores. Lo que queda es empate.
#include <bits/stdc++.h>
using namespace std;

// Devuelve 1 = gana, -1 = pierde, 0 = empate.
vector<int> solve_cyclic_game(int n, const vector<vector<int>>& g) {
    vector<int> out(n, 0), state(n, 0);
    vector<vector<int>> rev(n);
    for (int u = 0; u < n; ++u) {
        for (int v : g[u]) {
            ++out[u];
            rev[v].push_back(u);
        }
    }

    queue<int> q;
    for (int v = 0; v < n; ++v) {
        if (out[v] == 0) {
            state[v] = -1;  // sin movimientos: pierde
            q.push(v);
        }
    }

    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int u : rev[v]) {
            if (state[u] != 0) continue;
            if (state[v] == -1) {
                state[u] = 1;  // puede mover a un perdedor
                q.push(u);
            } else {
                if (--out[u] == 0) {
                    state[u] = -1;  // todos sus movimientos ganan
                    q.push(u);
                }
            }
        }
    }
    return state;  // los 0 que quedan son empates
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }

    vector<int> st = solve_cyclic_game(n, g);
    for (int i = 0; i < n; ++i) {
        cout << i << ": ";
        if (st[i] == 1) cout << "GANA\n";
        else if (st[i] == -1) cout << "PIERDE\n";
        else cout << "EMPATE\n";
    }
    return 0;
}
