// NIM: varias pilas, se quita cualquier cantidad de una sola pila.
// Con una sola pila el que toma la ultima gana; con varias, gana
// quien deja XOR = 0.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Juego normal: el que no puede mover pierde.
bool nim_win(const vector<int>& piles) {
    int x = 0;
    for (int p : piles) x ^= p;
    return x != 0;
}

// Misere: el que toma la ultima piedra pierde.
bool misere_nim_win(const vector<int>& piles) {
    int x = 0;
    bool all_one = true;
    for (int p : piles) {
        x ^= p;
        if (p > 1) all_one = false;
    }
    if (all_one) return x == 0;
    return x != 0;
}

// Devuelve {indice, nuevo_tamano} para dejar XOR = 0.
// Si no hay jugada ganadora, devuelve {-1, -1}.
pair<int, int> nim_move(const vector<int>& piles) {
    int x = 0;
    for (int p : piles) x ^= p;
    if (x == 0) return {-1, -1};
    for (int i = 0; i < (int)piles.size(); ++i) {
        int target = piles[i] ^ x;
        if (target < piles[i]) return {i, target};
    }
    return {-1, -1};
}

int main() {
    int n;
    cin >> n;
    vector<int> piles(n);
    for (int &p : piles) cin >> p;

    cout << "Normal: " << (nim_win(piles) ? "gana 1" : "gana 2") << '\n';
    cout << "Misere: "
         << (misere_nim_win(piles) ? "gana 1" : "gana 2") << '\n';

    pair<int, int> mv = nim_move(piles);
    if (mv.first == -1) cout << "No hay jugada ganadora\n";
    else {
        cout << "Mueve pila " << mv.first
             << " a " << mv.second << '\n';
    }
    return 0;
}
