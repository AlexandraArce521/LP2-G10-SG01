#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace  std;

class Estudiante {
private:
    string nombre;
    string dni;
    vector <double> notas;

public:
    Estudiante (string n, string d, vector <double> nNotas)
        : nombre(n), dni(d), notas(nNotas) {}
    
    void promedioNotas() {
        double suma = 0;

        for (size_t i = 0; i < notas.size(); ++i) {
            suma += notas[i];
            double promedio = suma/notas.size();
        }
        
        double promedio = suma / notas.size();  
        cout << "El promedio es: "<< promedio << endl; 
    }
    
    void mostrarDatos() {
        cout << "== Mostrar datos de Estudiante ==\n"<< endl;
        cout << "Nombre: " << nombre
             << "\nDNI: " << dni << endl;
             
        sort(notas.begin(), notas.end(), greater<double>());
        cout <<"Sus Notas son\n";
        for (size_t i = 0; i < notas.size(); ++i) {
            cout << i+1 << ". " <<notas[i] << endl;
        }
        
        promedioNotas();
    cout << "\n===================================\n" << endl;
    }
    
        
    ~Estudiante() {
        cout << endl;
    }
}; 

int main()
{
    vector<double> notas1 = {12.7, 18.9, 15.4};

    Estudiante estudiante1("Juan", "013173331", notas1);

    estudiante1.mostrarDatos();
    
//=========================================

    vector<double> notas2 = {10.8, 11.9, 12.4};

    Estudiante estudiante2("Carlos", "0158756", notas2);

    estudiante2.mostrarDatos();

    return 0;
}
