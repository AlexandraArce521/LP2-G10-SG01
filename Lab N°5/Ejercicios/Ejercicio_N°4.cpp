#include <iostream>
#include <string>
using namespace std;

class Direccion {
private:
    string calle;
    string numeroEdificio;
    string ciudad;
public:
    Direccion() {
        calle = "Sin calle";
        numeroEdificio = "Sin numero";
        ciudad = "Ciudad no asignada";
        cout << "Constructor SIN parametros de Direccion invocado " << endl;
    }
    
    Direccion(string cll, string num, string ciu)
        :calle(cll), numeroEdificio(num), ciudad(ciu) {
            cout << "Constructor CON parametros de Direccion invocado " << endl;
        }
    
    string getCalle() {
        return calle;
    }
    
    string getNumeroEdificio() {
        return numeroEdificio;
    }
    
    string getCiudad() {
        return ciudad;
    }
    
    void setCalle(string cll) {
        calle = cll;
    }
    
    void setNumeroEdificio(string num) {
        numeroEdificio = num;
    }
    
    void setCiudad(string ciu) {
        ciudad = ciu;
    }
    
    ~Direccion() {
        cout << "Destructor de Direccion invocado" << endl;
    }
        
};

class Gerente {
private:
    string nombre;
    string email;
    string cargo;
public:
    Gerente() {
        nombre = "Nombre no asignado";
        email = "sin email";
        cargo = "Cargo no asignado";
        cout << "Constructor SIN parametros de Gerente invocado " << endl;

    }
    
    Gerente(string n, string e, string c)
        :nombre(n), email(e), cargo(c) {
        cout << "Constructor CON parametros de Gerente invocado " << endl;
        }
    
    string getNombre() {
        return nombre;
    }    
    
    string getEmail() {
        return email;
    }
    
    string getCargo() {
        return cargo;
    }
    
    void setNombre(string n) {
        nombre = n;
    }
    
    void setEmail(string e) {
        email = e;
    }
    
    void setCargo(string c) {
        cargo = c;
    }
    
    ~Gerente()  {
        cout << "Destructor de Gerente invocado" << endl;
    }
};


class Empresa  {
private:
    Direccion direccion;    
    Gerente gerente;

public:    
    Empresa() {
        cout << "Constructor SIN parametros de Empresa invocado" << endl;
    }
    
    Empresa(string cll, string num, string ciu, string n, string e, string c )
     :direccion(cll, num, ciu), gerente(n, e, c) {
         cout << "Constructor CON parametros de Empresa invocado" << endl;
     }
     
    void mostrarEmpresa() {
        cout << "\n===Información de empresa===\n" << endl;
        cout <<"Calle: " << direccion.getCalle() << endl;
        cout << "Numero de Edificio: " << direccion.getNumeroEdificio() << endl;
        cout << "Ciudad: " << direccion.getCiudad() << endl;
        cout << "\n===Información de Gerente====\n" << endl;
        cout << "Nombre: " << gerente.getNombre() << endl;
        cout << "Email: " << gerente.getEmail() << endl;
        cout << "Cargo: " << gerente.getCargo() << endl;
        cout << endl;
        
    }
    
    ~Empresa() {
        cout << "Destructor de Empresa invocado" << endl;
    }
};

int main()
{
    Empresa empresa;
    empresa = Empresa("Calle San Jeronimo",
                    "A-128","Arequipa",
                    "Juan Carlos de las Vegas",
                    "Juan@Vegas.com",
                    "Director Ejecutivo");
    empresa.mostrarEmpresa();
    
    return 0;
}
