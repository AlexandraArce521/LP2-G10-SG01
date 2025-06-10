#include <iostream>
#include <cmath>
using namespace std;
// Clase base abstracta que define el contrato
class FiguraGeometrica {
public:
    virtual double calcularArea() const = 0;       // método virtual puro
    virtual double calcularPerimetro() const = 0;  // método virtual puro
};

// Circulo implementa los métodos de FiguraGeometrica
class Circulo : public FiguraGeometrica {
    double radio;
public:
    Circulo(double r) : radio(r) {}
    double calcularArea() const override {
        return M_PI * radio * radio;
    }
    double calcularPerimetro() const override {
        return 2 * M_PI * radio;
    }
};

// Rectangulo implementa los métodos de FiguraGeometrica
class Rectangulo : public FiguraGeometrica {
    double ancho, alto;
public:
    Rectangulo(double a, double h) : ancho(a), alto(h) {}
    double calcularArea() const override {
        return ancho * alto;
    }
    double calcularPerimetro() const override {
        return 2 * (ancho + alto);
    }
};

// Triangulo implementa los métodos de FiguraGeometrica
class Triangulo : public FiguraGeometrica {
    double base, altura, lado1, lado2, lado3;
public:
    // Constructor para triángulo general
    Triangulo(double b, double h, double l1, double l2, double l3)
        : base(b), altura(h), lado1(l1), lado2(l2), lado3(l3) {}
    double calcularArea() const override {
        return (base * altura) / 2.0;
    }
    double calcularPerimetro() const override {
        return lado1 + lado2 + lado3;
    }
};

int main() {
    // Crear instancias de cada figura
    FiguraGeometrica* figuras[3];
    figuras[0] = new Circulo(1.0);
    figuras[1] = new Rectangulo(4.0, 6.0);
    figuras[2] = new Triangulo(3.0, 4.0, 3.0, 4.0, 5.0);
    
    // Llamada polimórfica a calcularArea() y calcularPerimetro()
    for (int i = 0; i < 3; ++i) {
        cout << "Figura " << i+1 << " — "
        << "Área: " << figuras[i]->calcularArea()
        << ", Perímetro: " << figuras[i]->calcularPerimetro()
        << "\n";
    }
    
    return 0;
}
