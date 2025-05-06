#include <iostream>
using namespace std;

class Vector2D 
{
private:
    float x, y;

public:
    Vector2D(float x_, float y_) {
        x = x_;
        y = y_;
    }

    // Sobrecarga del operador +
    Vector2D operator+(const Vector2D& otro) {
        return Vector2D(x + otro.x, y + otro.y);
    }

    // Sobrecarga del operador -
    Vector2D operator-(const Vector2D& otro) {
        return Vector2D(x - otro.x, y - otro.y);
    }

    void mostrar() {
        cout << "(" << x << ", " << y << ")" << endl;
    }
};

int main() 
{
    Vector2D v1(3.0, 4.0);
    Vector2D v2(1.5, 2.5);

    Vector2D suma = v1 + v2;
    Vector2D resta = v1 - v2;

    cout << "Vector 1: "; v1.mostrar();
    cout << "Vector 2: "; v2.mostrar();
    cout << "Suma: "; suma.mostrar();
    cout << "Resta: "; resta.mostrar();

    return 0;
}
