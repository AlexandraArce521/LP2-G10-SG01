#include <iostream>
#include <string>
using namespace std;

class ICliente {
public:
    virtual string getNombre() const = 0;
    virtual string getDireccion() const = 0;
    virtual void mostrarCliente() const = 0;
    virtual ~ICliente() = default;  
};

class Cliente : public ICliente {
private:
    string nombre;
    string direccion;

public:
    Cliente(string nombre, string direccion):
        nombre(nombre), direccion(direccion) {}

    string getNombre() const override {
        return nombre;
    }

    string getDireccion() const override {
        return direccion;
    }

    void mostrarCliente() const override {
        cout << "=====Datos del cliente=====\n";
        cout << "Nombre: " << nombre << endl;
        cout << "Direccion: " << direccion << endl;
    }
};

class Factura {
private:
    int num;
    double monto;
    ICliente* cliente; 
public:
    Factura(int num, double monto, ICliente* cliente):
    num(num), monto(monto), cliente(cliente) {}

    int getNum() const {
        return num;
    }

    double getMonto() const {
        return monto;
    }

    void mostrarFactura() const {
        cliente->mostrarCliente();  
        cout << "Numero de pedido: " << num << endl;
        cout << "Monto: " << monto << endl;
    }
};

int main() {
    Cliente cliente1("Jose Vargas", "Alto selva alegre");  
    Factura factura1(123456, 290.90, &cliente1);  
    factura1.mostrarFactura();  
    
    return 0;
}
