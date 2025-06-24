#include <fstream>  
#include <iostream>  
#include <stdexcept>  
using namespace std;  


class Persona{
private:
    string nombre;
    int edad;
    string direccion;

public:
    Persona(string n, int e, string d)
     : nombre(n), edad(e), direccion(d) {}
    
    string getNombre() {return nombre;}
    int getEdad() {return edad;}
    string getDireccion() {return direccion;}
    
    void setNombre(string n) {
        if(n.length() > 0) {
            nombre = n;
        }
        else {
            cout << "(!)Sin nombre. Ingrese un nombre\n";
            exit(1);
        }
    }
    
    void setEdad(int e) {
        if(edad > 0) {
            edad = e;
        }
        else {
            cout << "(!)Edad no valida. Ingresar edad valida\n";
            exit(1);
        }
    }
    
    void setDireccion(string d) {
        if(d.length() > 0) {
            direccion = d;
        }
        else {
            cout << "(!)Sin nombre. Ingrese un nombre\n";
            exit(1);
        }
    }
};

int main()
{
    Persona p1("Juan", -3, "UCSM");

    return 0;
}
