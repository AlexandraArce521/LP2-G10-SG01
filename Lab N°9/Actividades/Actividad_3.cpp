#include <iostream>
#include <cmath>
using namespace std;
// Clase base abstracta con método virtual puro
class Figura {
public:
    virtual double calcularArea() const = 0;  // método virtual puro
};

// Clase derivada Circulo
class Circulo : public Figura {
    double radio;
public:
    Circulo(double r) : radio(r) {}
    double calcularArea() const override {
        return M_PI * radio * radio;
    }
};

// Clase derivada Rectangulo
class Rectangulo : public Figura {
    double ancho, alto;
public:
    Rectangulo(double a, double h) : ancho(a), alto(h) {}
    double calcularArea() const override {
        return ancho * alto;
    }
};

// Clase derivada Triangulo
class Triangulo : public Figura {
    double base, altura;
public:
    Triangulo(double b, double h) : base(b), altura(h) {}
    double calcularArea() const override {
        return (base * altura) / 2.0;
    }
};

int main() {
    // Array de punteros a Figura
    Figura* figuras[3];
    figuras[0] = new Circulo(1.0);
    figuras[1] = new Rectangulo(4.0, 6.0);
    figuras[2] = new Triangulo(3.0, 4.0);

    // Llamada polimórfica a calcularArea()
    for (int i = 0; i < 3; ++i) {
        cout << "Área figura " << i+1 << ": "
        << figuras[i]->calcularArea() << "\n";
    }

    // Liberar memoria
    for (int i = 0; i < 3; ++i) {
        delete figuras[i];
    }

    return 0;
}
