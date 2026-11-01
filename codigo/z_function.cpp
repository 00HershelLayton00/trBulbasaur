// Z-FUNCTION: z[i] = largo del prefijo mas largo de s que
// coincide con s[i..]. Sirve para buscar patrones y para
// comparar prefijos/sufijos.
#include <bits/stdc++.h>
using namespace std;

vector<int> z_function(const string &s) {
    int n = (int)s.size();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) { l = i; r = i + z[i] - 1; }
    }
    return z;
}

int main() {
    string text, pat;
    cin >> text >> pat;
    if (pat.empty()) return 0;

    // '#' debe ser un caracter que NO aparezca en text ni en pat.
    string t = pat + "#" + text;
    vector<int> z = z_function(t);

    vector<int> pos;
    int start = (int)pat.size() + 1;
    for (int i = start; i < (int)t.size(); ++i) {
        if (z[i] == (int)pat.size()) pos.push_back(i - start);
    }

    cout << pos.size() << '\n';
    for (int i = 0; i < (int)pos.size(); ++i) {
        if (i) cout << ' ';
        cout << pos[i];
    }
    cout << '\n';
    return 0;
}
