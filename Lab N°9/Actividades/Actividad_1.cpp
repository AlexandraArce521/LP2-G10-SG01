#include <iostream>
#include <string>
using namespace std;

// Clase base con método ahora virtual
class Animal {
public:
    virtual void hacerSonido() {
        cout << "Sonido genérico de animal\n";
    }
};

// Clase derivada que “redefine” el método
class Perro : public Animal {
public:
    void hacerSonido() override { // se añade override
        cout << "Guau!\n";
    }
};

int main() {
    // Creamos un Perro pero lo asignamos a puntero de tipo Animal
    Animal* a = new Perro();
    
    // Enlace temprano: llama a Perro::hacerSonido()
    a->hacerSonido();  // Salida: "Guau!"
    delete a;
    return 0;
}
