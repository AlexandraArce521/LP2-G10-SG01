#include <iostream>
#include <vector>
#include <string>
using namespace std;

template <typename T>
class Recipiente {
private:
    vector<T> datos;

public:

    void agregar(const T& valor) {
        datos.push_back(valor);
    }

    void mostrar() const {
        for (const T& val : datos)
            cout << val << " ";
        cout << endl;
    }

    int cantidad() const {
        return datos.size();
    }
};

class SistemaRutas {
private:
    Recipiente<string> rutas;
    Recipiente<string> vehiculos;
    Recipiente<int> entregasPorRuta;

public:
    void agregarRuta(const string& nombre) {
        rutas.agregar(nombre);
    }

    void agregarVehiculo(const string& placa) {
        vehiculos.agregar(placa);
    }

    void registrarEntregas(int cantidad) {
        entregasPorRuta.agregar(cantidad);
    }

    void mostrarInforme() {
        cout << "====Rutas registradas====\n";
        rutas.mostrar();

        cout << "====Vehículos asignados====\n";
        vehiculos.mostrar();

        cout << "====Entregas por ruta====\n";
        entregasPorRuta.mostrar();
    }
};
int main() {
    SistemaRutas sistema;

    sistema.agregarRuta("Ruta A");
    sistema.agregarRuta("Ruta B");

    sistema.agregarVehiculo("VHG-123");
    sistema.agregarVehiculo("VRK-456");

    sistema.registrarEntregas(25);
    sistema.registrarEntregas(40);

    sistema.mostrarInforme();

    return 0;
}

