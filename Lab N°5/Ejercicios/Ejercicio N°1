#include <iostream>
#include <string>
using namespace std;

class Producto {
private:
    string nombre;
    double precio;
    double descuento;
    double nuevo_precio;

public:
    Producto& setNombre(const string& nombre) {
        this->nombre = nombre;
        return *this;
    }
    
    Producto& setPrecio(double precio) {
        this->precio = precio;
        return *this;

    }
    
    Producto& setDescuento(double descuento) {
        this->descuento = descuento;
        return *this;

    }
    
    double calcularPrecioFinal() {
        nuevo_precio = precio * (1 - descuento / 100.0);
        cout << "Nuevo precio: " << nuevo_precio << "$ "<< endl;
        return nuevo_precio;

    }
    
    void mostrarProducto() const {
        cout << "Producto: " << nombre << endl;
        cout << "Precio: " << precio << endl;
        cout << "Descuento aplicado: " << descuento <<"% "<<endl;
    }

};

int main()
{
    Producto producto;
    producto.setNombre("Audífonos").setPrecio(156.90).setDescuento(30);
    producto.mostrarProducto();
    producto.calcularPrecioFinal();
    return 0;
}



