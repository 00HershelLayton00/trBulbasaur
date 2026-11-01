// KMP: busca TODAS las apariciones de un patron dentro de un texto.
// Entrada: texto patron (palabras sin espacios).
// Salida: cantidad de apariciones y sus posiciones (0 = primero).
#include <bits/stdc++.h>
using namespace std;

// pi[i] = largo del prefijo mas largo de s que tambien es sufijo
// de s[0..i]. Ejemplo: "ababa" -> [0,0,1,2,3].
vector<int> prefix_function(const string &s) {
    int n = (int)s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

// Devuelve las posiciones donde empieza el patron dentro del texto.
vector<int> kmp_search(const string &text, const string &pat) {
    if (pat.empty()) return {};
    vector<int> pi = prefix_function(pat), pos;
    int j = 0; // cuantos caracteres del patron ya coinciden
    for (int i = 0; i < (int)text.size(); ++i) {
        while (j > 0 && text[i] != pat[j]) j = pi[j - 1];
        if (text[i] == pat[j]) ++j;
        if (j == (int)pat.size()) {
            pos.push_back(i - (int)pat.size() + 1);
            j = pi[j - 1]; // permite apariciones solapadas
        }
    }
    return pos;
}

int main() {
    string text, pat;
    cin >> text >> pat;

    vector<int> pos = kmp_search(text, pat);
    cout << pos.size() << '\n';
    for (int i = 0; i < (int)pos.size(); ++i) {
        if (i) cout << ' ';
        cout << pos[i];
    }
    cout << '\n';
    return 0;
}
