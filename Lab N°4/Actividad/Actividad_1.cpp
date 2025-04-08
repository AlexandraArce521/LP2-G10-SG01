#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Clase Hijo
class Hijo 
{
    private:
        string nombre;
    public:
        // Constructor que recibe el nombre
        Hijo(string nombre) 
        {
            this->nombre = nombre;
        }
        // Métodos get y set
        string getNombre() { return nombre; }
        void setNombre(string nombre) { this->nombre = nombre; }
};

// Clase Padre, que mantiene un vector de punteros a objetos Hijo
class Padre 
{
    private:
        string nombre;
        vector<Hijo*> hijos; // Vector para almacenar los hijos sin límite fijo
    public:
        // Constructor que recibe el nombre del Padre
        Padre(string nombre) 
        {
            this->nombre = nombre;
        }
        
        // Destructor para liberar la memoria de los hijos
        ~Padre() 
        {
            for (Hijo* h : hijos) 
            {
                delete h;
            }
        }
        // Métodos get y set para el nombre
        string getNombre() { return nombre; }
        void setNombre(string nombre) { this->nombre = nombre; }
        
        // Método para agregar un objeto Hijo al vector
        void agregarHijo(Hijo* hijo) 
        {
            hijos.push_back(hijo);
        }
        
        // Método para imprimir la información del Padre y sus hijos
        void imprimirInfo() 
        {
            cout << "\nPadre: " << nombre << endl;
            cout << "Cantidad de hijos: " << hijos.size() << endl;
            for (size_t i = 0; i < hijos.size(); i++) {
                cout << "Hijo " << (i + 1) << ": " << hijos[i]->getNombre() << endl;
            }
        }
};

int main() 
{
    string nombrePadre;
    int cantidadHijos;
    
    // Solicitar el nombre del padre
    cout << "Ingrese el nombre del padre: ";
    getline(cin, nombrePadre);
    
    Padre padre(nombrePadre);
    
    // Solicitar la cantidad de hijos a ingresar
    cout << "Ingrese la cantidad de hijos: ";
    cin >> cantidadHijos;
    cin.ignore();  // Limpiar el buffer de entrada
    
    // Por cada hijo, pedir su nombre por teclado y agregarlo al objeto Padre
    for (int i = 0; i < cantidadHijos; i++) 
    {
        string nombreHijo;
        cout << "Ingrese el nombre del hijo " << (i + 1) << ": ";
        getline(cin, nombreHijo);
        Hijo* hijo = new Hijo(nombreHijo);
        padre.agregarHijo(hijo);
    }
    
    // Mostrar la información final del Padre y sus hijos
    padre.imprimirInfo();
    
    return 0;
}
