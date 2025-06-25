#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

struct Producto {
    char nombre[30];
    double precio;
    int cantidad;
};

map<string, int> indice; // nombre → posición

void guardarProductoBinario(const Producto& p, int pos) {
    fstream archivo("inventario.dat", ios::in | ios::out | ios::binary);
    if (!archivo) archivo.open("inventario.dat", ios::out | ios::binary);
    archivo.seekp(pos * sizeof(Producto));
    archivo.write(reinterpret_cast<const char*>(&p), sizeof(Producto));
    archivo.close();
}

void crearIndice() {
    ifstream archivo("inventario.dat", ios::binary);
    if (!archivo) {
        cerr << "Archivo no encontrado.\n";
        return;
    }
    Producto p;
    int pos = 0;
    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        indice[p.nombre] = pos++;
    }
    archivo.close();
}

void buscarProductoPorIndice(const string& nombre) {
    if (indice.find(nombre) == indice.end()) {
        cout << "Producto no encontrado en el índice.\n";
        return;
    }
    int pos = indice[nombre];
    ifstream archivo("inventario.dat", ios::binary);
    archivo.seekg(pos * sizeof(Producto));
    Producto p;
    archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto));
    archivo.close();

    cout << "\nProducto encontrado:\n";
    cout << "Nombre: " << p.nombre << ", Precio: " << p.precio << ", Cantidad: " << p.cantidad << endl;
}

int main() {
    // Registro de productos (solo una vez)
    Producto p1 = {"Televisor", 500.0, 10};
    Producto p2 = {"Laptop", 800.0, 5};
    guardarProductoBinario(p1, 0);
    guardarProductoBinario(p2, 1);

    // Crear índice en memoria
    crearIndice();

    // Buscar directamente por índice (acceso aleatorio)
    buscarProductoPorIndice("Laptop");

    return 0;
}
