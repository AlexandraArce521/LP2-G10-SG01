#include <iostream>
#include <deque>
#include <string>
#include <cctype>   // for tolower
using namespace std;

bool esVocal(char c) {
    c = tolower(static_cast<unsigned char>(c));
    return c=='a' || c=='e' || c=='i' || c=='o' || c=='u';
}

int main() {
    deque<char> d;
    string linea;

    // 1) Leer la cadena completa del usuario
    cout << "Ingrese una cadena: ";
    getline(cin, linea);

    // Almacenar cada carácter en el deque
    for (char c : linea) {
        d.push_back(c);  // añade al final
    }

    // 2) Recorrer el deque con un iterador y mostrar caracteres uno por uno
    cout << "\nContenido original:\n";
    for (auto it = d.begin(); it != d.end(); ++it) {
        cout << *it;    // imprime el carácter apuntado
    }
    cout << "\n";

    // 3) Reemplazar todas las vocales con '*'
    for (auto it = d.begin(); it != d.end(); ++it) {
        if (esVocal(*it)) {
            *it = '*';   // modifica el carácter en el deque
        }
    }

    // 4) Mostrar con iterador inverso los caracteres en orden inverso
    cout << "\nContenido invertido tras reemplazo de vocales:\n";
    for (auto rit = d.rbegin(); rit != d.rend(); ++rit) {
        cout << *rit;   // imprime desde el último al primero
    }
    cout << "\n";

    // 5) Mostrar la cadena resultante (deque convertido a string)
    cout << "\nCadena resultante:\n";
    for (char c : d) {
        cout << c;
    }
    cout << "\n";
    return 0;
}
