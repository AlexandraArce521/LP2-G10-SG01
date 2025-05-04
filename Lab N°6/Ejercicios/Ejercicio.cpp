#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Alumno {
private:
    string nombre;
    int edad;
    double promedio;
    
public:
    Alumno(string n, int e, double p)
        :nombre(n), edad(e), promedio(p) {}
    
    void mostrar() const {
        cout << "==Datos del alumno==" << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Edad: " << edad << endl;
        cout << "Promedio: " << promedio << endl;
        cout << endl;
    }
    

    
};

class Grupo {
private:
    vector<Alumno> alumnos;
    int cantidad;

public:
    Grupo(vector<Alumno>& a, int c)
        : alumnos(a), cantidad(c) {}

    void mostrarAlumnos() {
        for (const Alumno& a : alumnos)  {
            a.mostrar();  
        }
    }
};

int main()
{
    vector<Alumno> lista;
    lista.push_back(Alumno("Carlos", 20, 15.3));
    lista.push_back(Alumno("Lucía", 22, 18.7));

    Grupo grupo(lista, lista.size());
    grupo.mostrarAlumnos();

    return 0;
}
