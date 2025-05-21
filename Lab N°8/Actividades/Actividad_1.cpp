#include <iostream>
#include <cmath>
using namespace std;

class Figura {
public:
    virtual double calcularArea() const = 0;
    virtual ~Figura() {}
};

class Circulo : public Figura {
    double r;
public:
    Circulo(double radio) : r(radio) {}
    double calcularArea() const override {
        return M_PI * r * r;
    }
};

class Rectangulo : public Figura {
    double b, h;
public:
    Rectangulo(double base, double altura) : b(base), h(altura) {}
    double calcularArea() const override {
        return b * h;
    }
};

class Triangulo : public Figura {
    double b, h;
public:
    Triangulo(double base, double altura) : b(base), h(altura) {}
    double calcularArea() const override {
        return b * h / 2.0;
    }
};

class Cuadrado : public Figura {
    double lado;
public:
    Cuadrado(double l) : lado(l) {}
    double calcularArea() const override {
        return lado * lado;
    }
};

class Pentagono : public Figura {
    double lado, ap;
public:
    Pentagono(double l, double apotema) : lado(l), ap(apotema) {}
    double calcularArea() const override {
        return 5 * lado * ap / 2.0;
    }
};

int main() {
    cout << "==============================\n";
    cout << "     CALCULAR ÁREA FIGURAS    \n";
    cout << "==============================\n";
    cout << "1) Círculo\n"
            "2) Rectángulo\n"
            "3) Triángulo\n"
            "4) Cuadrado\n"
            "5) Pentágono\n";
    cout << "Selecciona una figura (1-5): ";
    int op;
    cin >> op;

    Figura* f = nullptr;
    switch (op) {
        case 1: {
            double r;
            cout << "\n-- Datos para CÍRCULO --\n";
            cout << "Radio: "; cin >> r;
            f = new Circulo(r);
            break;
        }
        case 2: {
            double b, h;
            cout << "\n-- Datos para RECTÁNGULO --\n";
            cout << "Base: ";   cin >> b;
            cout << "Altura: "; cin >> h;
            f = new Rectangulo(b, h);
            break;
        }
        case 3: {
            double b, h;
            cout << "\n-- Datos para TRIÁNGULO --\n";
            cout << "Base: ";   cin >> b;
            cout << "Altura: "; cin >> h;
            f = new Triangulo(b, h);
            break;
        }
        case 4: {
            double l;
            cout << "\n-- Datos para CUADRADO --\n";
            cout << "Lado: "; cin >> l;
            f = new Cuadrado(l);
            break;
        }
        case 5: {
            double l, ap;
            cout << "\n-- Datos para PENTÁGONO --\n";
            cout << "Lado: ";   cin >> l;
            cout << "Apotema: "; cin >> ap;
            f = new Pentagono(l, ap);
            break;
        }
        default:
            cout << "\n¡Opción inválida!\n";
            return 0;
    }

    cout << "\n>> El área de la figura seleccionada es: " 
         << f->calcularArea() << "\n";

    delete f;
    return 0;
}
