#include <iostream>
using namespace std;

class Animal {
public:
    virtual void hacerSonido() const {
        cout << "(sonido genérico)\n";
    }
    virtual ~Animal() {}
};

class Perro : public Animal {
public:
    void hacerSonido() const override {
        cout << "Guau guau!\n";
    }
};

class Gato : public Animal {
public:
    void hacerSonido() const override {
        cout << "Miau miau!\n";
    }
};

class Vaca : public Animal {
public:
    void hacerSonido() const override {
        cout << "Muuu muuu!\n";
    }
};

int main() {
    cout << "===========================\n";
    cout << "    SONIDOS DE ANIMALES    \n";
    cout << "===========================\n";

    Animal* a1 = new Perro();
    Animal* a2 = new Gato();
    Animal* a3 = new Vaca();

    cout << "\nPerro dice: ";
    a1->hacerSonido();

    cout << "Gato dice: ";
    a2->hacerSonido();

    cout << "Vaca dice: ";
    a3->hacerSonido();

    delete a1;
    delete a2;
    delete a3;

    return 0;
}
