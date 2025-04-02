#include <iostream>
#include <vector>
#include <string>

using namespace std;

class ITarea {
public:
    virtual void mostrarDetalles() const = 0;
    virtual ~ITarea() {} 
};

class TareaUsuario : public ITarea {
private:
    string descripcion;
public:
    TareaUsuario(const string& desc) : descripcion(desc) {}

    void mostrarDetalles() const override {
        cout << "Tarea: " << descripcion << endl;
    }
};


class GestorTareas {
private:
    vector<ITarea*> tareas;
public:
    ~GestorTareas() {
        for (ITarea* tarea : tareas) {
            delete tarea;
        }
    }

    void agregarTarea(const string& descripcion) {
        tareas.push_back(new TareaUsuario(descripcion));
    }

    const vector<ITarea*>& obtenerTareas() const {
        return tareas;
    }
};


class VistaTareas {
public:
    static void mostrarTareas(const GestorTareas& gestor) {
        const vector<ITarea*>& tareas = gestor.obtenerTareas();
        
        if (tareas.empty()) {
            cout << "No hay tareas registradas." << endl;
            return;
        }
        
        cout << "\nLista de tareas:" << endl;
        for (const auto& tarea : tareas) {
            tarea->mostrarDetalles();
            cout << "------------------------" << endl;
        }
    }
};


int main() {
    GestorTareas gestor;
    int opcionMenu;
    
    vector<string> lista = {
        "1. Agregar tarea",
        "2. Mostrar tareas",
        "3. Salir"
    };

    do {
        cout << "\nMenú de Opciones:" << endl;
        for (const string &opcion : lista) {
            cout << opcion << endl;
        }

        cout << "Seleccione una opción: ";
        cin >> opcionMenu;
        cin.ignore(); 

        switch (opcionMenu) {
            case 1: {
                string descripcion;
                cout << "Ingrese la descripción de la tarea: ";
                getline(cin, descripcion);
                gestor.agregarTarea(descripcion);
                cout << "Tarea agregada con éxito." << endl;
                break;
            }
            case 2: {
                VistaTareas::mostrarTareas(gestor); 
                break;
            }
            case 3: {
                cout << "Saliendo del menú..." << endl;
                break;
            }
            default: {
                cout << "Opción no válida. Intente de nuevo." << endl;
                break;
            }
        }
    } while (opcionMenu != 3);

    return 0;
}
