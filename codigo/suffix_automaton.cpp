// SUFFIX AUTOMATON (AUTOMATA DE SUFIJOS).
// Construye en O(n) una maquina que reconoce todos los substrings.
// Usa letras 'a'..'z'; las mayusculas se pasan a minusculas.
// Entrada: s p k (k <= 10^18). Salida: varias respuestas de prueba.
#include <bits/stdc++.h>
using namespace std;

struct SuffixAutomaton {
    static const int ALPHA = 26;
    static const long long LIMIT = 4000000000000000000LL;

    struct State {
        int len, link;
        int next[ALPHA];
        State(int l = 0, int link_ = -1) : len(l), link(link_) {
            fill(next, next + ALPHA, -1);
        }
    };

    vector<State> st;       // estados del automata
    vector<int> occ;        // occ[v] = ocurrencias de sus substrings
    vector<long long> ways; // ways[v] = substrings distintos desde v
    int last;

    // Convierte 'a'..'z' y 'A'..'Z' a 0..25. Otro caracter -> -1.
    static int id(char ch) {
        if ('A' <= ch && ch <= 'Z') ch = char(ch - 'A' + 'a');
        if (ch < 'a' || ch > 'z') return -1;
        return ch - 'a';
    }

    SuffixAutomaton(const string &s = "") {
        st.reserve(2 * max(1, (int)s.size()));
        st.push_back(State()); // estado inicial
        // el estado inicial no cuenta ocurrencias
        occ.push_back(0);
        last = 0;
        for (char ch : s) extend(ch);
        compute_occurrences();
        compute_ways();
    }

    // Agrega un caracter al final del string.
    void extend(char ch) {
        int c = id(ch);
        if (c == -1) return; // ignora caracteres fuera de a-z
        int cur = (int)st.size();
        st.push_back(State(st[last].len + 1));
        occ.push_back(1); // este estado representa un prefijo real

        int p = last;
        while (p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = (int)st.size();
                st.push_back(st[q]); // copia transiciones y link
                st[clone].len = st[p].len + 1;
                occ.push_back(0); // un clon no es un prefijo real
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    // Ordena los estados por len de menor a mayor.
    vector<int> order_by_len() const {
        int n = (int)st.size();
        int max_len = st[last].len;
        vector<int> cnt(max_len + 1, 0), order(n);
        for (int i = 0; i < n; ++i) ++cnt[st[i].len];
        for (int i = 1; i <= max_len; ++i) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; --i) {
            order[--cnt[st[i].len]] = i;
        }
        return order;
    }

    // Propaga las ocurrencias por los suffix links.
    void compute_occurrences() {
        vector<int> order = order_by_len();
        for (int i = (int)order.size() - 1; i > 0; --i) {
            int v = order[i];
            if (st[v].link != -1) occ[st[v].link] += occ[v];
        }
    }

    // Cuenta los caminos (substrings distintos) desde cada estado.
    void compute_ways() {
        int n = (int)st.size();
        ways.assign(n, 0);
        vector<int> order = order_by_len();
        for (int i = n - 1; i >= 0; --i) {
            int v = order[i];
            long long total = 0;
            for (int c = 0; c < ALPHA; ++c) {
                int u = st[v].next[c];
                if (u == -1) continue;
                // la arista sola + todas sus extensiones
                total += 1 + ways[u];
                if (total > LIMIT) { total = LIMIT; break; }
            }
            ways[v] = total;
        }
    }

    // Cantidad de substrings distintos (sin contar el string vacio).
    long long distinct_substrings() const {
        long long ans = 0;
        for (int v = 1; v < (int)st.size(); ++v) {
            ans += st[v].len - st[st[v].link].len;
        }
        return ans;
    }

    // Cuantas veces aparece p en s. Devuelve 0 si no aparece.
    int count_occurrences(const string &p) const {
        if (p.empty()) return 0;
        int v = 0;
        for (char ch : p) {
            int c = id(ch);
            if (c == -1 || st[v].next[c] == -1) return 0;
            v = st[v].next[c];
        }
        return occ[v];
    }

    // Largo del substring comun mas largo entre s y t.
    int longest_common_substring(const string &t) const {
        int v = 0, len = 0, best = 0;
        for (char ch : t) {
            int c = id(ch);
            if (c == -1) { v = 0; len = 0; continue; }
            while (v != -1 && st[v].next[c] == -1) v = st[v].link;
            if (v == -1) { v = 0; len = 0; continue; }
            len = min(len, st[v].len) + 1;
            v = st[v].next[c];
            best = max(best, len);
        }
        return best;
    }

    // k-esima substring distinta en orden lexicografico
    // (k empieza en 1).
    // Si no existe, devuelve "".
    string kth_distinct(long long k) const {
        if (k <= 0 || k > ways[0]) return "";
        string ans;
        int v = 0;
        while (true) {
            for (int c = 0; c < ALPHA; ++c) {
                int u = st[v].next[c];
                if (u == -1) continue;
                // substrings que empiezan con esta letra
                long long cnt = 1 + ways[u];
                if (k > cnt) { k -= cnt; continue; }
                ans.push_back(char('a' + c));
                --k;
                if (k == 0) return ans;
                v = u;
                break;
            }
        }
    }

    // Cantidad de substrings distintos que aparecen al menos k veces.
    long long distinct_with_min_occ(int k) const {
        if (k <= 0) return distinct_substrings();
        long long ans = 0;
        for (int v = 1; v < (int)st.size(); ++v) {
            if (occ[v] >= k) ans += st[v].len - st[st[v].link].len;
        }
        return ans;
    }
};

int main() {
    string s, p;
    long long k;
    cin >> s >> p >> k;

    SuffixAutomaton sam(s);
    cout << "Distintas: " << sam.distinct_substrings() << '\n';
    cout << "Ocurrencias de p: " << sam.count_occurrences(p) << '\n';
    cout << "LCS con p: " << sam.longest_common_substring(p) << '\n';
    cout << "k-esima: " << sam.kth_distinct(k) << '\n';
    cout << "Con >=2 ocurrencias: "
         << sam.distinct_with_min_occ(2) << '\n';
    return 0;
}
