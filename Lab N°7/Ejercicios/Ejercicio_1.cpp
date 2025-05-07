#include <iostream>
using namespace std;

class Vehiculo {
protected:
    string marca;
    string modelo;
    int anyoFabricacion;
public: 
Vehiculo() {
    marca = "Sin marca";
    modelo = "Sin modelo";
    anyoFabricacion = 0;
}
};

class Automovil: public Vehiculo {
    int numPuertas:
    string tipoCombustible;
    
};

class Automovil: public Motocicleta {
    string tipoCombustible;
    
};


int main()
{

    return 0;
}
