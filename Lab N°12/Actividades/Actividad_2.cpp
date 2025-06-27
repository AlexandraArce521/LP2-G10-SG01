#include <iostream>
#include <list>
#include <algorithm>  // count, transform
#include <string>
#include <cctype>     // toupper
using namespace std;

int main() {
    list<string> palabras;
    string palabra;

    // 1) Leer palabras hasta que el usuario ingrese una línea vacía
    cout << "Ingrese palabras (ENTER en blanco para terminar):\n";
    while (true) {
        getline(cin, palabra);
        if (palabra.empty()) break;
        palabras.push_back(palabra);    // almacena en la list
    }

    if (palabras.empty()) {
        cout << "No se ingresaron palabras.\n";
        return 0;
    }

    // 2) Ordenar alfabéticamente (utilizando el método sort de list)
    palabras.sort();  // lista de strings soporta sort() en orden lexicográfico

    // 3) Contar ocurrencias de una palabra dada
    cout << "¿Qué palabra desea contar? ";
    getline(cin, palabra);
    int apariciones = count(palabras.begin(), palabras.end(), palabra);
    cout << "La palabra \"" << palabra 
         << "\" aparece " << apariciones << " veces.\n";

    // 4) Convertir todas las palabras a mayúsculas
    for (auto& w : palabras) {
        transform(
            w.begin(), w.end(),   // rango de caracteres de la palabra
            w.begin(),            // destino: sobreescribe en la misma palabra
            [](char c){ return toupper(static_cast<unsigned char>(c)); }
        );
    }

    // 5) Mostrar la lista resultante
    cout << "Lista final en mayúsculas y ordenada:\n";
    for (const auto& w : palabras) {
        cout << w << "\n";
    }

    return 0;
}
