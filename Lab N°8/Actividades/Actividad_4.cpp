#include <iostream>
using namespace std;

class Vehiculo {
public:
    virtual void acelerar() {
        cout << "Acelerando el vehículo\n";
    }
    virtual ~Vehiculo() {}
};

class Coche : public Vehiculo {
public:
    // Reemplaza completamente el método de la clase base
    void acelerar() override {
        cout << "Acelerando el coche\n";
    }

    // Método exclusivo de Coche (refinamiento adicional)
    void encenderLuces() {
        cout << "Luces del coche encendidas\n";
    }
};

class Motocicleta : public Vehiculo {
public:
    // También reemplaza el método de la clase base
    void acelerar() override {
        cout << "Acelerando la motocicleta\n";
    }
};

int main() {
    cout << "=============================\n";
    cout << "     PRUEBA DE VEHÍCULOS     \n";
    cout << "=============================\n\n";

    // Instancia de Coche
    Coche* coche = new Coche();
    cout << "Coche:\n";
    coche->acelerar();       // → Acelerando el coche
    coche->encenderLuces();  // → Luces del coche encendidas

    cout << "\n";

    // Instancia de Motocicleta
    Motocicleta* moto = new Motocicleta();
    cout << "Motocicleta:\n";
    moto->acelerar();          // → Acelerando la motocicleta
    //moto->encenderLuces();  // Error: Motocicleta no tiene ese método

    cout << "\n";

    // Uso polimórfico
    Vehiculo* v1 = coche;
    Vehiculo* v2 = moto;

    cout << "Polimorfismo:\n";
    v1->acelerar();   // → Acelerando el coche
    v2->acelerar();   // → Acelerando la motocicleta

    delete coche;
    delete moto;
    return 0;
}
