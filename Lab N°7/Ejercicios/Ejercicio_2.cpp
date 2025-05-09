#include <iostream>
#include <string>
using namespace std;

class Persona {
protected:
    string nombre;
    int edad;
    double salario;
    string correo;

public:
    Persona() {
        nombre = "Sin nombre";
        edad = 0;
        salario = 0.0;
        correo = "Sin correo";
        cout << "Constructor sin parametros de Persona" << endl;
    }
    
    Persona(string n, int e, double s, string d)
     :nombre(n), edad(e), salario(s), correo(d) {
         cout << "Constructor con parametros de Persona" << endl;
     }
     
    string getNombre() {
        return nombre;
    }
    
    int getEdad() {
        return edad;
    }
    
    double getSalario() {
        return salario;
    }
    
    string getCorreo() {
        return correo;
    }
    
    void setNombre(string n) {
        nombre = n;
    }
    
    void setEdad(int e) {
        edad = e;
    }
    
    void setSalario(double s) {
        salario = s;
    }
    
    void setCorreo(string c) {
        correo = c;
    }
    
    ~Persona() {
        cout << "Destructor de la clase Persona" << endl;
    }
};

class Cliente: protected Persona {
private:
    string fono;
    string id;

public:
    Cliente() {
        fono = "Sin telefóno";
        id = "Sin ID";
        cout << "Constructor sin parametros Cliente" << endl;
    }
    
    Cliente(string nom, int ed, double sal, string mail, string f, string ident)
     :Persona(nom, ed, sal, mail), id(ident), fono(f) {
         cout << "Contructor con parametros Cliente" << endl;
     }
     
     string getFono() {
         return fono;
     }
     
     string getID() {
         return id;
     }
     
     void setFono(string f) {
         fono = f;
     }
     
     void setID(string ident) {
         id = ident;
     }
     
     void mostrarCliente() {
         cout << "\n====Detalles del cliente====\n" << endl;
         cout << "Nombre: " << nombre << endl;
         cout << "Edad: " << edad << endl;
         cout << "Salario: " << salario << endl;
         cout << "*Dirección de correo electrónico*: " << correo << endl;
         cout << "ID de Cliente: " << id << endl;
         cout << "telefóno de Cliente: " << fono << endl;
         cout << "\n============================\n" << endl;
     }
     
     ~Cliente() {
         cout << "Destructor de Cliente" << endl;
     }

};

class Empleado: protected Persona {
private:
    string idEmpleado;
    string cargo;

public:
    Empleado() {
        idEmpleado = "Sin id de Empleado";
        cargo = "Sin cargo";
        cout << "Constructor sin parametros de Empleado" << endl;

    }
    
    Empleado(string nom, int ed, double sal, string mail, string id, string c)
     :Persona(nom, ed, sal, mail), cargo(c), idEmpleado(id) {
         cout << "Constructor con parametros de Empleado" << endl;
     }

    string getCargo()  { 
        return cargo; 
    }
    string getIdEmpleado() { 
        return idEmpleado; 
    }
    
    void setCargo(string car) { 
        cargo = car; 
    }
    void setIdEmpleado(string id) { 
        idEmpleado = id; 
    }
    
         void mostrarEmpleado() {
         cout << "\n====Detalles del empleado====\n" << endl;
         cout << "Nombre: " << nombre << endl;
         cout << "Edad: " << edad << endl;
         cout << "Salario: " << salario << endl; 
         cout << "ID de Empleado: " << idEmpleado << endl;
         cout << "Cargo de Empleado: " << cargo << endl;
         cout << "\n============================\n" << endl;

     }
     
    ~Empleado() {
        cout << "Destructor de Empleado" << endl;
    }

    
};

int main()
{
    Cliente cliente1 ("Jose", 38, 180.90, "jose@gamil,com", "51-014356", "01317331");
    cliente1.mostrarCliente();
    
    Empleado empleado1("Carlos", 45, 1200.0, "carlos@gmail.com", "1205602", "Gerente");
    empleado1.mostrarEmpleado();
    
    return 0;
}
