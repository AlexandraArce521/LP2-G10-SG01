#include <iostream>
using namespace std;

class Dispositivo {
private:
    string marca;
    string modelo;
    int anioFabricacion;

public:
    // Constructor predeterminado
    Dispositivo() {
        marca = "Sin marca";
        modelo = "Genérico";
        anioFabricacion = 0;
        cout << "Constructor predeterminado\n";
    }

    // Constructor parametrizado
    Dispositivo(string m, string mo, int a) {
        marca = m;
        modelo = mo;
        anioFabricacion = a;
        cout << "Constructor parametrizado: " << modelo << endl;
    }

    // Constructor de copia
    Dispositivo(const Dispositivo& otro) {
        marca = otro.marca;
        modelo = otro.modelo;
        anioFabricacion = otro.anioFabricacion;
        cout << "Constructor de copia: " << modelo << endl;
    }

    // Destructor
    ~Dispositivo() {
        cout << "Destructor llamado para: " << modelo << endl;
    }
};

int main() {
    Dispositivo arreglo[3] = {
        Dispositivo("HP", "Laptop", 2020),
        Dispositivo("Samsung", "Tablet", 2021),
        Dispositivo("Apple", "iPhone", 2022)
    };
    return 0;
}
