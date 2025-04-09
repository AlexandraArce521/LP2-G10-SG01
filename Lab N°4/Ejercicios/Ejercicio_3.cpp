#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Estudiante;
class Profesor;
class Asisgnatura;
class Notas;


class Estudiante    {

private:
    string nombre;
    string direccion;
    int numMatricula;
    vector <Asisgnatura*> asignaturasMatriculadas;
public:
    
    Estudiante(string nombre, string direccion, int numMatricula):
    nombre(nombre), direccion(direccion), numMatricula(numMatricula) {}
    
    string getNombre()  {
        return nombre;
    }
    
    string getDireccion()   {
        return direccion;
    }
    
    int getNumMatricula()   {
        return numMatricula;
    }
    
    void AgregarAsignaturaEstu(Asignatura* asignatura)  {
        asignaturasMatriculadas.push_back(asignatura)
    }
    
    void mostrarAsignaturaEstu() const{
        cout << "Lista de asignatura del Estudiante" << endl;
        cout << "Nombre: " << nombre 
            << ", Número de matricula: " << numMatricula << endl;
        
        for (Asignatura* a: asignaturas)    {
            cout << "- " << a->getNombre() << endl;
        }
    }
    
};

class Profesor  {
 
private:
    string nombreP;
    string direccionP;
    vector <Asignatura*> asignaturasImpartidas;
    
public:
  
};

class Asignatura   {
 
private:
    int codigo;
    string nombreC;
    string descripcion;
    vector <Profesor*> profesores;
public:  
};


class Notas {
    
};
