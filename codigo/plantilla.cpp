// PLANTILLA BASE. Copia este archivo y ejecutalo con:
// g++ -O2 -std=c++17 programa.cpp -o programa
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 1) LEER. cin >> s lee UNA palabra (se detiene en un espacio).
    string s;
    cin >> s;

    // 2) RESOLVER. Pega aqui el struct/funcion de la receta.
    //    Luego llamalo con los datos leidos.
    int largo = (int)s.size();

    // 3) IMPRIMIR. Cambia esto por lo que pida el problema.
    cout << largo << '\n';
    return 0;
}
