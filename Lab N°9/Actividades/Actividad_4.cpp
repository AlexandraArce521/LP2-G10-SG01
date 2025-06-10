#include <iostream>
using namespace std;
// Clase base con método virtual
class Animal {
public:
    virtual void hacerSonido() const {
        cout << "Sonido genérico de animal\n";
    }
};

// Clases derivadas que sobrescriben hacerSonido()
class Perro : public Animal {
public:
    void hacerSonido() const override {
        cout << "Guau!\n";
    }
};

class Gato : public Animal {
public:
    void hacerSonido() const override {
        cout << "Miau!\n";
    }
};

class Vaca : public Animal {
public:
    void hacerSonido() const override {
        cout << "Muu!\n";
    }
};

int main() {
    // Arreglo de punteros a Animal
    Animal* animales[3];
    animales[0] = new Perro();
    animales[1] = new Gato();
    animales[2] = new Vaca();

    // Llamada polimórfica a hacerSonido()
    for (int i = 0; i<3; i++) {
        animales[i]->hacerSonido();
    }

    return 0;
}
