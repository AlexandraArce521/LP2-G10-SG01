#include <iostream>
using namespace std;
// Clase Calculadora con métodos sumar sobrecargados
class Calculadora {
public:
    // Suma dos enteros
    int sumar(int a, int b) {
        return a + b;
    }

    // Suma dos números de punto flotante
    double sumar(double a, double b) {
        return a + b;
    }

    // Suma tres enteros
    int sumar(int a, int b, int c) {
        return a + b + c;
    }
};

int main() {
    Calculadora calc;

    cout << "sumar(2, 3) = " << calc.sumar(2, 3) << "\n";
    cout << "sumar(2.5, 3.7) = " << calc.sumar(2.5, 3.7) << "\n";
    cout << "sumar(1, 2, 3) = " << calc.sumar(1, 2, 3) << "\n";

    return 0;
}
