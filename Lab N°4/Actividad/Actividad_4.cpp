#include <iostream>
#include <string>
using namespace std;

const int MAX_TRABAJADORES = 5; // Máximo número de compañeros o trabajadores

// Clase Trabajador
class Trabajador {
private:
    string nombre;
    string cargo;
    Trabajador* companeros[MAX_TRABAJADORES]; // Compañeros de trabajo
    int numCompaneros; // Número de compañeros actuales

public:
    Trabajador(string nombre, string cargo) {
        this->nombre = nombre;
        this->cargo = cargo;
        numCompaneros = 0;
    }

    string getNombre() {
        return nombre;
    }

    void agregarCompanero(Trabajador* companero) {
        if (numCompaneros < MAX_TRABAJADORES) {
            companeros[numCompaneros] = companero;
            numCompaneros++;
        } else {
            cout << "No puedes agregar más compañeros, ya alcanzaste el máximo permitido." << endl;
        }
    }

    void mostrarCompaneros() {
        cout << "Compañeros de " << nombre << " (" << cargo << "):" << endl;
        if (numCompaneros == 0) {
            cout << " - No tiene compañeros asignados." << endl;
        } else {
            for (int i = 0; i < numCompaneros; i++) {
                cout << " - " << companeros[i]->getNombre() << endl;
            }
        }
    }
};

// Clase Gerente (hereda de Trabajador)
class Gerente : public Trabajador {
private:
    Trabajador* trabajadoresACargo[MAX_TRABAJADORES]; // Trabajadores a cargo del gerente
    int numTrabajadores; // Número de trabajadores a cargo

public:
    Gerente(string nombre, string cargo) : Trabajador(nombre, cargo) {
        numTrabajadores = 0;
    }

    void agregarTrabajador(Trabajador* t) {
        if (numTrabajadores < MAX_TRABAJADORES) {
            trabajadoresACargo[numTrabajadores] = t;
            numTrabajadores++;
        } else {
            cout << "No puedes agregar más trabajadores a cargo, ya alcanzaste el máximo permitido." << endl;
        }
    }

    void mostrarTrabajadoresACargo() {
        cout << "Trabajadores a cargo del gerente " << getNombre() << ":" << endl;
        if (numTrabajadores == 0) {
            cout << " - No tiene trabajadores a cargo." << endl;
        } else {
            for (int i = 0; i < numTrabajadores; i++) {
                cout << " - " << trabajadoresACargo[i]->getNombre() << endl;
            }
        }
    }
};

// Función para crear un trabajador
Trabajador* crearTrabajador() {
    string nombre, cargo;
    cout << "Ingrese el nombre del trabajador: ";
    cin.ignore(); // Limpiar el buffer
    getline(cin, nombre);
    cout << "Ingrese el cargo del trabajador: ";
    getline(cin, cargo);
    return new Trabajador(nombre, cargo);
}

// Función para crear un gerente
Gerente* crearGerente() {
    string nombre, cargo;
    cout << "Ingrese el nombre del gerente: ";
    cin.ignore(); // Limpiar el buffer
    getline(cin, nombre);
    cout << "Ingrese el cargo del gerente: ";
    getline(cin, cargo);
    return new Gerente(nombre, cargo);
}

// Función principal
int main() {
    int opcion;
    Trabajador* trabajadores[MAX_TRABAJADORES];
    Gerente* gerente = nullptr;
    int numTrabajadores = 0;

    do {
        cout << "\nMenu de opciones:" << endl;
        cout << "1. Crear un trabajador" << endl;
        cout << "2. Crear un gerente" << endl;
        cout << "3. Asignar trabajadores a un gerente" << endl;
        cout << "4. Establecer compañeros entre trabajadores" << endl;
        cout << "5. Mostrar trabajadores a cargo del gerente" << endl;
        cout << "6. Mostrar compañeros de un trabajador" << endl;
        cout << "7. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                if (numTrabajadores < MAX_TRABAJADORES) {
                    trabajadores[numTrabajadores] = crearTrabajador();
                    numTrabajadores++;
                } else {
                    cout << "No se pueden crear más trabajadores." << endl;
                }
                break;

            case 2:
                if (gerente == nullptr) {
                    gerente = crearGerente();
                } else {
                    cout << "Ya existe un gerente." << endl;
                }
                break;

            case 3:
                if (gerente != nullptr) {
                    cout << "Asignar trabajadores al gerente " << gerente->getNombre() << ":" << endl;
                    for (int i = 0; i < numTrabajadores; i++) {
                        cout << i + 1 << ". " << trabajadores[i]->getNombre() << endl;
                    }
                    cout << "Seleccione el número del trabajador a asignar al gerente: ";
                    int seleccionado;
                    cin >> seleccionado;
                    if (seleccionado >= 1 && seleccionado <= numTrabajadores) {
                        gerente->agregarTrabajador(trabajadores[seleccionado - 1]);
                    } else {
                        cout << "Selección inválida." << endl;
                    }
                } else {
                    cout << "No hay gerente creado." << endl;
                }
                break;

            case 4:
                cout << "Establecer compañeros entre trabajadores:" << endl;
                for (int i = 0; i < numTrabajadores; i++) {
                    for (int j = i + 1; j < numTrabajadores; j++) {
                        trabajadores[i]->agregarCompanero(trabajadores[j]);
                        trabajadores[j]->agregarCompanero(trabajadores[i]);
                    }
                }
                break;

            case 5:
                if (gerente != nullptr) {
                    gerente->mostrarTrabajadoresACargo();
                } else {
                    cout << "No hay gerente creado." << endl;
                }
                break;

            case 6:
                cout << "Mostrar compañeros de un trabajador:" << endl;
                for (int i = 0; i < numTrabajadores; i++) {
                    cout << i + 1 << ". " << trabajadores[i]->getNombre() << endl;
                }
                cout << "Seleccione el número del trabajador: ";
                int trabajadorSeleccionado;
                cin >> trabajadorSeleccionado;
                if (trabajadorSeleccionado >= 1 && trabajadorSeleccionado <= numTrabajadores) {
                    trabajadores[trabajadorSeleccionado - 1]->mostrarCompaneros();
                } else {
                    cout << "Selección inválida." << endl;
                }
                break;

            case 7:
                cout << "Saliendo del programa..." << endl;
                break;

            default:
                cout << "Opción no válida." << endl;
        }
    } while (opcion != 7);

    // Liberar memoria
    for (int i = 0; i < numTrabajadores; i++) {
        delete trabajadores[i];
    }
    delete gerente;

    return 0;
}
