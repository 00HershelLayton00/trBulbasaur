// WYTHOFF: dos pilas. Se puede quitar cualquier cantidad de una pila
// o la misma cantidad de ambas. Las posiciones perdedoras son
// (floor(k*phi), floor(k*phi) + k), con phi = (1 + sqrt(5)) / 2.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// floor(d * phi), calculado sin errores de punto flotante.
ll floor_phi(ll d) {
    ll low = 0, high = 2 * d + 1;  // phi < 2
    while (low + 1 < high) {
        ll mid = (low + high) / 2;
        __int128 a = (__int128)2 * mid - d;
        bool le = ((__int128)2 * mid <= d) ||
                  (a * a <= (__int128)5 * d * d);
        if (le) low = mid;
        else high = mid;
    }
    return low;
}

// true si el primero gana desde (a, b).
bool wythoff_win(ll a, ll b) {
    if (a > b) swap(a, b);
    ll d = b - a;
    return a != floor_phi(d);
}

int main() {
    ll a, b;
    cin >> a >> b;
    cout << (wythoff_win(a, b) ? "Gana el primero" : "Gana el segundo");
    cout << '\n';
    return 0;
}
