#include <iostream>
#include <cmath>
using namespace std;

class Circulo 
{
private:
    float radio;
    float diametro;

public:
    Circulo(float r) {
        radio = r;
        diametro = 2 * r;
    }

    void mostrarDatos() {
        cout << "Radio: " << radio << ", Diámetro: " << diametro << endl;
    }

    // Declaración de función amiga
    friend float calcularArea(Circulo c);
};

// Definición de función amiga
float calcularArea(Circulo c) 
{
    return M_PI * c.radio * c.radio; // M_PI es una constante para π
}

int main() 
{
    Circulo c1(5.0);
    c1.mostrarDatos();
    cout << "Área del círculo: " << calcularArea(c1) << endl;

    Circulo c2(3.2);
    c2.mostrarDatos();
    cout << "Área del círculo: " << calcularArea(c2) << endl;

    return 0;
}
