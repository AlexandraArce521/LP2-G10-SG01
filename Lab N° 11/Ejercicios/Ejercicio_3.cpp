#include <fstream>  
#include <iostream>  
#include <stdexcept>  
#include <vector>
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
    vector <Persona*> personas;
    
    personas.push_back(new Persona("Juan", 2, "Av. Villa Hermosa"));
    personas.push_back(new Persona("Matias", 12, "Av. Arequipa"));
    personas.push_back(new Persona("Marta", 20, "Urb Misti"));
    personas.push_back(new Persona("Oscar", 45, "Urb. Rivera"));
    personas.push_back(new Persona("María", 70, "Av. Lima"));

    

    fstream archivo;
    archivo.open("Registro.txt", ios::out);

     for (int i = 0; i < personas.size(); ++i) {
        archivo << personas[i] << endl;
    }   
    
    archivo.close();

    return 0;
}
