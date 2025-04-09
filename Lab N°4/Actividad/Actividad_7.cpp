#include <iostream>
#include <string>
using namespace std;

// Clase base con atributos y métodos comunes
class Animal {
protected:
    string nombre;
    int edad;

public:
    // Constructor de la clase base
    Animal(string nombre, int edad) {
        this->nombre = nombre;
        this->edad = edad;
        cout << "Animal creado: " << nombre << ", Edad: " << edad << endl;
    }

    // Destructor de la clase base
    virtual ~Animal() {
        cout << "Destructor de Animal llamado para: " << nombre << endl;
    }

    // Método para mostrar información común
    void mostrarInfo() {
        cout << "Nombre: " << nombre << ", Edad: " << edad << " años." << endl;
    }

    // Método virtual para sonido (cada clase derivada lo implementará de manera diferente)
    virtual void hacerSonido() {
        cout << "El animal hace un sonido." << endl;
    }
};

// Clase derivada que hereda de Animal
class Perro : public Animal {
private:
    string raza;

public:
    // Constructor de la clase derivada que inicializa los atributos de la clase base
    Perro(string nombre, int edad, string raza) : Animal(nombre, edad) {
        this->raza = raza;
        cout << "Perro creado: " << nombre << ", Edad: " << edad << ", Raza: " << raza << endl;
    }

    // Destructor de la clase derivada
    ~Perro() {
        cout << "Destructor de Perro llamado para: " << nombre << endl;
    }

    // Método propio de la clase derivada
    void mostrarRaza() {
        cout << "Raza: " << raza << endl;
    }

    // Sobrescribir el método virtual hacerSonido
    void hacerSonido() override {
        cout << "El perro " << nombre << " hace: ¡Guau!" << endl;
    }
};

// Función para interactuar con el usuario y crear el objeto
void interactuarConUsuario() {
    string nombrePerro, raza;
    int edadPerro;

    // Solicitar al usuario que ingrese los datos del perro
    cout << "Ingrese el nombre del perro: ";
    getline(cin, nombrePerro);
    cout << "Ingrese la edad del perro: ";
    cin >> edadPerro;
    cin.ignore();  // Limpiar el buffer de entrada
    cout << "Ingrese la raza del perro: ";
    getline(cin, raza);

    // Crear un objeto de la clase derivada Perro
    Perro* miPerro = new Perro(nombrePerro, edadPerro, raza);

    // Interacciones con el objeto
    int opcion;
    do {
        cout << "\nMenú de opciones:\n";
        cout << "1. Mostrar información del perro\n";
        cout << "2. Mostrar raza del perro\n";
        cout << "3. Hacer que el perro haga un sonido\n";
        cout << "4. Modificar la edad del perro\n";
        cout << "5. Eliminar el perro y salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();  // Limpiar el buffer de entrada

        switch (opcion) {
            case 1:
                miPerro->mostrarInfo();
                break;
            case 2:
                miPerro->mostrarRaza();
                break;
            case 3:
                miPerro->hacerSonido();
                break;
            case 4:
                {
                    int nuevaEdad;
                    cout << "Ingrese la nueva edad del perro: ";
                    cin >> nuevaEdad;
                    cin.ignore();  // Limpiar el buffer
                    miPerro->mostrarInfo();  // Mostrar información antes
                    // Modificar la edad
                    miPerro->mostrarInfo();  // Mostrar información después
                    cout << "Edad modificada correctamente." << endl;
                }
                break;
            case 5:
                delete miPerro;  // Eliminar el objeto y liberar memoria
                cout << "Perro eliminado. ¡Adiós!" << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }
    } while (opcion != 5);
}

// Función principal
int main() {
    // Interactuar con el usuario
    interactuarConUsuario();
    
    return 0;
}
