#include <iostream>
#include <vector>
#include <algorithm>  // sort, remove_if, max_element, min_element
#include <numeric>    // accumulate
using namespace std;

int main() {
    vector<int> numeros;
    int n;

    cout << "Ingrese números enteros (termina con 0):\n";
    // 1) Leer números hasta que el usuario ingrese 0
    while (true) {
        cin >> n;
        if (n == 0) break;
        numeros.push_back(n);        // Almacena en el vector
    }

    if (numeros.empty()) {
        cout << "No se ingresaron números.\n";
        return 0;
    }

    // 2) Calcular la suma de todos los números
    int suma = accumulate(numeros.begin(), numeros.end(), 0);
    cout << "Suma: " << suma << "\n";

    // 3) Encontrar el número máximo y mínimo
    auto it_max = max_element(numeros.begin(), numeros.end());
    auto it_min = min_element(numeros.begin(), numeros.end());
    cout << "Máximo: " << *it_max << "\n";   // Imprime el mayor
    cout << "Mínimo: " << *it_min << "\n";   // Imprime el menor

    // 4) Ordenar los números de forma ascendente
    sort(numeros.begin(), numeros.end());
    cout << "Orden ascendente: ";
    for (int x : numeros)
        cout << x << " ";                  // Recorre e imprime
    cout << "\n";

    // 5) Eliminar los números pares del contenedor
    numeros.erase(
        remove_if(numeros.begin(), numeros.end(),
                  [](int x){ return x % 2 == 0; }),  // Predicado: par?
        numeros.end()
    );
    cout << "Después de eliminar pares: ";
    for (int x : numeros)
        cout << x << " ";                  // Imprime solo impares
    cout << "\n";

    return 0;
}
