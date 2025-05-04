#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
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
    double getPromedio() const {
        return promedio;
    }
    
    bool operator < (const Alumno& otro) const {
        return promedio < otro.promedio;
    }    

    
};

class Grupo {
private:
    vector<Alumno> alumnos;
    int cantidad;

public:
    Grupo(int c)
        :cantidad(c) {
            alumnos.reserve(cantidad);
        }

    void mostrarAlumnos() {
     cout << "==Grupo de Alumnos==" << endl;
        for (const Alumno& a : alumnos)  {
            a.mostrar();  
        }
    }

    void agregarAlumno(const string& nombre, int edad, float promedio) {
        if (alumnos.size() < cantidad) {
            alumnos.push_back(Alumno(nombre, edad, promedio));
        } else {
            cout << "El grupo ya está lleno." << endl;
        }
    }
   void ordenarAlumnos() {
        sort(alumnos.begin(), alumnos.end());
    }

    float calcularPromedio() const {
        float suma = 0.0;
        for (const Alumno& a : alumnos) {
            suma += a.getPromedio();
        }
        return suma / alumnos.size();
    }

    Alumno obtenerMejorPromedio() const {
        Alumno mejor = alumnos[0];
        for (const Alumno& a : alumnos) {
            if (a.getPromedio() > mejor.getPromedio()) {
                mejor = a;
            }
        }
        return mejor;
    }

};

int main()
{
    Grupo grupo(5);
    
    grupo.agregarAlumno("Carlos", 20, 15.3);
    grupo.agregarAlumno("Lucia", 22, 18.7);
    grupo.agregarAlumno("Jose", 21, 17.5);
    grupo.agregarAlumno("Ana", 19, 16.8);
    grupo.agregarAlumno("Miguel", 23, 14.9);

    grupo.mostrarAlumnos();
    
    float promedio = grupo.calcularPromedio();
    cout << "Promedio de los promedios: " << promedio << endl;

    return 0;
}
