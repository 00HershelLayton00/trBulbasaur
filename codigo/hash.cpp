// HASH DOBLE: compara substrings en O(1) y calcula LCP en O(log n).
// Es probabilistico: con dos modulos, el riesgo de colision
// es minimo. Entrada: s, q consultas l1 r1 l2 r2.
// Los rangos son [l, r), con 0 <= l < r <= n.
// Salida: SI si las dos substrings son iguales, NO si no.
#include <bits/stdc++.h>
using namespace std;

struct StringHash {
    static const long long M1 = 1000000007LL;
    static const long long M2 = 1000000009LL;
    static const long long B  = 911382323LL;

    int n;
    vector<long long> p1, p2, h1, h2;

    StringHash(const string &s)
        : n((int)s.size()), p1(n + 1, 1), p2(n + 1, 1),
          h1(n + 1, 0), h2(n + 1, 0) {
        for (int i = 0; i < n; ++i) {
            long long c = (unsigned char)s[i] + 1;
            p1[i + 1] = p1[i] * B % M1;
            p2[i + 1] = p2[i] * B % M2;
            h1[i + 1] = (h1[i] * B + c) % M1;
            h2[i + 1] = (h2[i] * B + c) % M2;
        }
    }

    // Hash de s[l..r). El rango incluye l y NO incluye r.
    pair<long long, long long> get(int l, int r) const {
        long long a = (h1[r] - h1[l] * p1[r - l]) % M1;
        long long b = (h2[r] - h2[l] * p2[r - l]) % M2;
        if (a < 0) a += M1;
        if (b < 0) b += M2;
        return {a, b};
    }

    bool equal(int l1, int r1, int l2, int r2) const {
        if (r1 - l1 != r2 - l2) return false;
        return get(l1, r1) == get(l2, r2);
    }

    // Largo del prefijo comun mas largo de los sufijos i y j.
    int lcp(int i, int j) const {
        int low = 0, high = min(n - i, n - j);
        while (low < high) {
            int mid = (low + high + 1) / 2;
            if (get(i, i + mid) == get(j, j + mid)) low = mid;
            else high = mid - 1;
        }
        return low;
    }
};

int main() {
    string s;
    cin >> s;
    StringHash h(s);

    int q;
    cin >> q;
    while (q--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        cout << (h.equal(l1, r1, l2, r2) ? "SI" : "NO") << '\n';
    }
    return 0;
}
