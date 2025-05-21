#include <iostream>
using namespace std;

class Forma {
public:
  virtual double calcularPerimetro() const = 0;
  virtual ~Forma() {}
};

class Circulo : public Forma {
  double r;
public:
  Circulo(double radio): r(radio) {}
  double calcularPerimetro() const override {
    return 2 * 3.1416 * r;
  }
};

class Rectangulo : public Forma {
  double b, h;
public:
  Rectangulo(double base, double altura): b(base), h(altura) {}
  double calcularPerimetro() const override {
    return 2 * (b + h);
  }
};

class Triangulo : public Forma {
  double a, b, c;
public:
  Triangulo(double a_, double b_, double c_): a(a_), b(b_), c(c_) {}
  double calcularPerimetro() const override {
    return a + b + c;
  }
};

int main() {
  cout << "==============================\n";
  cout << "  CALCULAR PERÍMETRO DE FORMAS\n";
  cout << "==============================\n";
  cout << "1) Círculo\n"
          "2) Rectángulo\n"
          "3) Triángulo\n";
  cout << "Selecciona una forma (1-3): ";
  int op; 
  cin >> op;

  Forma* f = nullptr;
  switch(op) {
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
      double a, b, c;
      cout << "\n-- Datos para TRIÁNGULO --\n";
      cout << "Lado A: "; cin >> a;
      cout << "Lado B: "; cin >> b;
      cout << "Lado C: "; cin >> c;
      f = new Triangulo(a, b, c);
      break;
    }
    default:
      cout << "\n¡Opción inválida!\n";
      return 0;
  }

  cout << "\n>> El perímetro es: " << f->calcularPerimetro() << "\n";
  delete f;
  return 0;
}
