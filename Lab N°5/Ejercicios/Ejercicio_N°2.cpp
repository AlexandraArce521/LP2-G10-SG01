#include <iostream>
#include <string>
using namespace std;
class FechaRegistro {
private:
    int dia, mes, anio;

public:
    FechaRegistro(int d, int m, int a):
        dia(d), mes(m), anio(a) {
            cout << "Fecha de registro creada! ";
            mostrarFechaRegistro();
            cout << endl;
        }
    void mostrarFechaRegistro() const {
        cout << dia << "/" << mes << "/" << anio;
    }
};

class Cliente {
private:
    string nombre;
    FechaRegistro fecha;

public:
    Cliente(string nom, int d, int m, int a):
        nombre(nom), fecha(d,m,a) // lista de inicializacion
    {
        cout << "Cliente registrado! " << endl;
    }
    
    void mostrarCliente() const {
        cout << "Nombre de Cliente: " << nombre << "\nFecha de registro: ";
        fecha.mostrarFechaRegistro();
        cout << endl;
    }
    
};

class Direccion {
private:
    string direccion;
    Cliente cliente;

public:
    Direccion(string direc, string nom, int d, int m, int a):
        direccion(direc), cliente(nom, d, m, a)
    {
        cout << "Dirección del cliente registrada: " << direccion << endl;
    }
};


int main()
{
    Cliente cliente("Juan",11,12,2005);
    cliente.mostrarCliente();
    return 0;
}









