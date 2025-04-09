#include <iostream>
#include <string>
using namespace std;

// Clase del objeto que se compone
class Componente {
private:
    string nombre;

public:
    // Constructor
    Componente(string nombre) {
        this->nombre = nombre;
    }

    // Método para obtener el nombre del componente
    string getNombre() {
        return nombre;
    }

    // Método para modificar el nombre del componente
    void setNombre(string nombre) {
        this->nombre = nombre;
    }

    // Método para mostrar la información del componente
    void mostrarInfo() {
        cout << "Componente: " << nombre << endl;
    }
};

// Clase base que representa la entidad principal de la relación de composición
class Compositor {
private:
    Componente* componente; // Objeto compuesto

public:
    // Constructor que inicializa el objeto compuesto
    Compositor(string nombreComponente) {
        componente = new Componente(nombreComponente);
        cout << "Compositor creado con el componente: " << componente->getNombre() << endl;
    }

    // Destructor que elimina el objeto compuesto
    ~Compositor() {
        delete componente;
        cout << "Componente destruido." << endl;
    }

    // Método para acceder al objeto compuesto
    Componente* obtenerComponente() {
        return componente;
    }

    // Método para modificar el objeto compuesto
    void modificarComponente(string nuevoNombre) {
        componente->setNombre(nuevoNombre);
    }
};

// Función para mostrar el menú y gestionar las acciones
void mostrarMenu() {
    cout << "\nMenú de opciones:\n";
    cout << "1. Crear Compositor con Componente\n";
    cout << "2. Ver Componente\n";
    cout << "3. Modificar Componente\n";
    cout << "4. Eliminar Componente y salir\n";
    cout << "Ingrese una opción: ";
}

int main() {
    Compositor* compositor = nullptr;  // Puntero al compositor
    int opcion;
    string nombreComponente, nuevoNombre;

    while (true) {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:  // Crear Compositor con Componente
                if (compositor != nullptr) {
                    cout << "Ya existe un compositor creado. ¿Desea eliminarlo antes de crear uno nuevo? (s/n): ";
                    char respuesta;
                    cin >> respuesta;
                    if (respuesta == 's' || respuesta == 'S') {
                        delete compositor;
                        compositor = nullptr;
                    } else {
                        continue;
                    }
                }

                cout << "Ingrese el nombre del componente: ";
                cin.ignore();  // Limpiar el buffer de entrada
                getline(cin, nombreComponente);

                compositor = new Compositor(nombreComponente);
                break;

            case 2:  // Ver Componente
                if (compositor != nullptr) {
                    compositor->obtenerComponente()->mostrarInfo();
                } else {
                    cout << "No hay un compositor creado. Cree uno primero." << endl;
                }
                break;

            case 3:  // Modificar Componente
                if (compositor != nullptr) {
                    cout << "Ingrese el nuevo nombre para el componente: ";
                    cin.ignore();  // Limpiar el buffer de entrada
                    getline(cin, nuevoNombre);
                    compositor->modificarComponente(nuevoNombre);
                } else {
                    cout << "No hay un compositor creado. Cree uno primero." << endl;
                }
                break;

            case 4:  // Eliminar Componente y salir
                if (compositor != nullptr) {
                    delete compositor;
                    compositor = nullptr;
                    cout << "Componente eliminado. Programa terminado." << endl;
                } else {
                    cout << "No hay un compositor creado para eliminar." << endl;
                }
                return 0;

            default:
                cout << "Opción no válida. Intente nuevamente." << endl;
        }
    }

    return 0;
}
