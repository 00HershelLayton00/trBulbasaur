// MANACHER: todos los palindromos en O(n).
// d1[i] = radio impar: s[i-k..i+k] es palindromo.
// d2[i] = radio par:   s[i-k..i+k-1] es palindromo.
#include <bits/stdc++.h>
using namespace std;

struct Manacher {
    vector<int> d1, d2;

    Manacher(const string &s) {
        int n = (int)s.size();
        d1.assign(n, 0);
        d2.assign(n, 0);

        // Palindromos de largo impar, centro en i.
        for (int i = 0, l = 0, r = -1; i < n; ++i) {
            int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
            while (i - k >= 0 && i + k < n &&
                   s[i - k] == s[i + k]) ++k;
            d1[i] = k--;
            if (i + k > r) { l = i - k; r = i + k; }
        }

        // Palindromos de largo par, centro entre i-1 e i.
        for (int i = 0, l = 0, r = -1; i < n; ++i) {
            int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
            while (i - k - 1 >= 0 && i + k < n &&
                   s[i - k - 1] == s[i + k]) ++k;
            d2[i] = k--;
            if (i + k > r) { l = i - k - 1; r = i + k; }
        }
    }

    // Cantidad de substrings palindromas (contando repetidas).
    long long count_all() const {
        long long ans = 0;
        for (int i = 0; i < (int)d1.size(); ++i) {
            ans += d1[i] + d2[i];
        }
        return ans;
    }

    // {inicio, largo} del palindromo mas largo.
    pair<int, int> longest() const {
        int best = 0, start = 0;
        for (int i = 0; i < (int)d1.size(); ++i) {
            int len = 2 * d1[i] - 1;
            if (len > best) { best = len; start = i - d1[i] + 1; }
            len = 2 * d2[i];
            if (len > best) { best = len; start = i - d2[i]; }
        }
        return {start, best};
    }
};

int main() {
    string s;
    cin >> s;

    Manacher m(s);
    pair<int, int> p = m.longest();
    cout << "Palindromo mas largo: "
         << s.substr(p.first, p.second) << '\n';
    cout << "Su largo: " << p.second << '\n';
    cout << "Palindromos contando repetidos: "
         << m.count_all() << '\n';
    return 0;
}
