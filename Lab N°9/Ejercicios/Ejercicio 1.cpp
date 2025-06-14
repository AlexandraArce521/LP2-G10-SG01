#include<vector>
#include <iostream>

using namespace std;

class Figura{
    public:
    virtual double area() = 0;
    virtual double perimetro() = 0;
    virtual void mostrar() = 0;
    virtual ~Figura() = default;
};

class Circulo : public Figura {
private:
    double radio;

public:
    Circulo(double r) {
        radio = r;
    }
    
    double area() override {
        return 3.1416*radio*radio;
    }
    
    double perimetro () override {
        return 2*3.1416*radio;
    }
    
    void mostrar() override {
        cout << "Circulo"<< endl;
        cout << "Radio: " << radio << endl;
        cout << "Perímetro: " << perimetro() <<endl;
        cout << "Área: " << area() << endl;
    }
};

class Rectangulo : public Figura {
private:
    double lado;
    double base;

public:
    Rectangulo(double l, double b) {
        lado = l;
        base = b;
    }
    
    double area() override {
        return lado*base;
    }
    
    double perimetro () override {
        return 2*lado + 2*base;
    }
    
    void mostrar() override {
        cout << "Rectangulo"<< endl;
        cout << "Lado: " << lado << endl;
        cout << "Base: " <<  base <<endl;
        cout << "Perimetro: " << perimetro() << endl;
        cout << "Área: " << area() << endl;
    }
};

class Triangulo : public Figura {
private:
    double base, altura;
    vector<double> lados;
    
public:
    Triangulo(double b, double a, vector<double> l) 
        : base(b), altura(a), lados(l) {}
    
    double area() override {
        return 0.5 * base * altura;
    }
    
    double perimetro() override {
        double perimetro = 0;
        for (double lado : lados) {
            perimetro += lado;
        }
        return perimetro;
    }
    
    void mostrar() override {
        cout << "Triangulo" << endl;
        cout << "Lados: " << endl;
        for (int i = 0; i < lados.size(); ++i) {
            cout << "-|  "<<lados[i] << endl;
        }
        
        cout << "Base: " << base << endl;
        cout << "Altura: " << altura << endl;
        cout << "Perímetro: " << perimetro() << endl;
        cout << "Área: " << area() << endl;
    }
};


int main() {
    vector<Figura*> figuras;

    vector<double> lados = {5.0, 4.0, 3.0};
    figuras.push_back(new Circulo(5.0));
    figuras.push_back(new Rectangulo(4.0, 6.0));
    figuras.push_back(new Triangulo(3.0, 4.0, lados));
    
    cout << "=====Información de las figuras=====" << endl;

    for (int i = 0; i < figuras.size(); ++i) {
        cout << "==================================== \n" << i + 1 << ":" << endl;
        figuras[i]->mostrar();
        cout << endl;
    }

    for (Figura* figura : figuras) {
        delete figura;
    }

    return 0;
}
