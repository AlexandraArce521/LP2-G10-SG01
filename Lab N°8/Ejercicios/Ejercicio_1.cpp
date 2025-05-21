#include <iostream>
using namespace std;

class Figura {
public:
    virtual void dibujar () = 0;
    virtual double area () = 0;
};

class Circulo: public Figura {
private:
    double radio;
    const double pi = 3.14;
    
public:
    Circulo(double r)
        :radio(r) {}
    
    void dibujar() override {
        cout << "Estoy dibujando un Círculo\n";
    }
    
    double area() override {
        return pi*radio*radio;
    }
};

class Rectangulo: public Figura {
private:
    double base;
    double altura;

public:
    Rectangulo(double b, double a)
    : base(b), altura(a) {}
    
    void dibujar() override {
        cout << "Estoy dibujando un Rectangulo\n";
    }
    
    double area() override {
        return base*altura;
    }
};

class Triangulo: public Figura {
private:
    double base;
    double altura;    
public:
    Triangulo(double b, double a)
    : base(b), altura(a) {}
    
    void dibujar() override {
        cout << "Estoy dibujando un Triángulo\n";
    }
    
    double area() override {
        return (base*altura)/2;
    }
};

int main()
{
    Figura* circulo1 = new Circulo(2);
    Figura* rectangulo1 = new Rectangulo(5,2);    
    Figura* triangulo1 = new Triangulo(3,4);

    
    circulo1 ->dibujar();
    cout << "Área del círculo: " << circulo1 ->area() << endl;
    cout << endl;
    
    triangulo1 ->dibujar();
    cout << "Área del triangulo: " << triangulo1 ->area() << endl;
    cout << endl;

    
    rectangulo1 ->dibujar();
    cout<< "Área del rectángulo: " << rectangulo1 ->area() << endl;    
    cout << endl;

    
    delete circulo1;
    delete rectangulo1;
    delete triangulo1;

    return 0;
}
