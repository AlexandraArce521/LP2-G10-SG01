#include <iostream>
#include <string>
using namespace std;

const int MAX_OBJETOS = 5; // Tamaño máximo de la colección

// Clase que representa los objetos que se agregarán a la colección
class Objeto {
private:
    string nombre;
    int id;

public:
    // Constructor para inicializar los atributos
    Objeto(string nombre, int id) {
        this->nombre = nombre;
        this->id = id;
    }

    // Métodos para obtener los atributos
    string getNombre() {
        return nombre;
    }

    int getId() {
        return id;
    }

    // Métodos para mostrar la información del objeto
    void mostrarInfo() {
        cout << "ID: " << id << ", Nombre: " << nombre << endl;
    }
};

// Clase base que representa la colección de objetos
class Coleccion {
private:
    Objeto* objetos[MAX_OBJETOS]; // Colección de objetos
    int numObjetos; // Número de objetos actualmente en la colección

public:
    // Constructor para inicializar la colección
    Coleccion() {
        numObjetos = 0;
    }

    // Método para agregar un objeto a la colección
    void agregarObjeto(Objeto* obj) {
        if (numObjetos < MAX_OBJETOS) {
            objetos[numObjetos] = obj;
            numObjetos++;
            cout << "Objeto agregado: " << obj->getNombre() << endl;
        } else {
            cout << "No se puede agregar más objetos, la colección está llena." << endl;
        }
    }

    // Método para eliminar un objeto de la colección
    void eliminarObjeto(int id) {
        bool encontrado = false;
        for (int i = 0; i < numObjetos; i++) {
            if (objetos[i]->getId() == id) {
                // Eliminar el objeto desplazando los demás hacia la izquierda
                for (int j = i; j < numObjetos - 1; j++) {
                    objetos[j] = objetos[j + 1];
                }
                numObjetos--;
                encontrado = true;
                cout << "Objeto con ID " << id << " eliminado." << endl;
                break;
            }
        }
        if (!encontrado) {
            cout << "Objeto con ID " << id << " no encontrado." << endl;
        }
    }

    // Método para obtener un objeto específico de la colección
    Objeto* obtenerObjeto(int id) {
        for (int i = 0; i < numObjetos; i++) {
            if (objetos[i]->getId() == id) {
                return objetos[i];
            }
        }
        return nullptr; // Retorna nullptr si no se encuentra el objeto
    }

    // Método para mostrar todos los objetos en la colección
    void mostrarColeccion() {
        if (numObjetos == 0) {
            cout << "La colección está vacía." << endl;
        } else {
            cout << "Objetos en la colección:" << endl;
            for (int i = 0; i < numObjetos; i++) {
                objetos[i]->mostrarInfo();
            }
        }
    }
};

// Función para mostrar el menú de opciones
void mostrarMenu() {
    cout << "\n----- Menú -----\n";
    cout << "1. Agregar un objeto a la colección\n";
    cout << "2. Eliminar un objeto de la colección\n";
    cout << "3. Mostrar todos los objetos de la colección\n";
    cout << "4. Buscar un objeto por ID\n";
    cout << "5. Salir\n";
    cout << "Seleccione una opción: ";
}

// Función principal
int main() {
    Coleccion coleccion;  // Crear instancia de la clase base Coleccion
    int opcion;
    int id;
    string nombre;
    
    // Bucle para mostrar el menú de opciones y permitir interacción con el usuario
    while (true) {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1: {
                // Agregar un objeto
                cout << "Ingrese el nombre del objeto: ";
                cin >> nombre;
                cout << "Ingrese el ID del objeto: ";
                cin >> id;

                Objeto* nuevoObjeto = new Objeto(nombre, id);
                coleccion.agregarObjeto(nuevoObjeto);
                break;
            }

            case 2: {
                // Eliminar un objeto
                cout << "Ingrese el ID del objeto a eliminar: ";
                cin >> id;

                coleccion.eliminarObjeto(id);
                break;
            }

            case 3: {
                // Mostrar todos los objetos
                coleccion.mostrarColeccion();
                break;
            }

            case 4: {
                // Buscar un objeto por ID
                cout << "Ingrese el ID del objeto a buscar: ";
                cin >> id;

                Objeto* objEncontrado = coleccion.obtenerObjeto(id);
                if (objEncontrado != nullptr) {
                    cout << "Objeto encontrado:" << endl;
                    objEncontrado->mostrarInfo();
                } else {
                    cout << "Objeto no encontrado." << endl;
                }
                break;
            }

            case 5: {
                // Salir
                cout << "Saliendo del programa." << endl;
                return 0;
            }

            default: {
                cout << "Opción inválida. Intente nuevamente." << endl;
                break;
            }
        }
    }

    return 0;
}
