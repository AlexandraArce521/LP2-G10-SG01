#include <iostream>
#include <string>
#include <vector>
using namespace std;


// Clase Estudiante
class Estudiante 
{
    private:
        string nombre;
        int id;
    public:
        Estudiante(string nombre, int id) {
            this->nombre = nombre;
            this->id = id;
        }
    
        string getNombre() { return nombre; }
        int getId() { return id; }
};

// Clase Docente
class Docente 
{
    private:
        string nombre;
        string especialidad;
    public:
        Docente(string nombre, string especialidad) 
        {
            this->nombre = nombre;
            this->especialidad = especialidad;
        }
    
        string getNombre() { return nombre; }
        string getEspecialidad() { return especialidad; }
};

// Clase Curso
class Curso 
{
    private:
        string nombre;
        string codigo;
    public:
        Curso(string nombre, string codigo) 
        {
            this->nombre = nombre;
            this->codigo = codigo;
        }
    
        string getNombre() { return nombre; }
        string getCodigo() { return codigo; }
};

// Clase Asociacion (Asociación ternaria)
class Asociacion 
{
    private:
        Estudiante* estudiante;
        Docente* docente;
        Curso* curso;
    public:
        Asociacion(Estudiante* est, Docente* doc, Curso* cur) 
        {
            estudiante = est;
            docente = doc;
            curso = cur;
        }
    
        void mostrarRelacion() 
        {
            cout << "Estudiante: " << estudiante->getNombre()
                 << " | Docente: " << docente->getNombre()
                 << " (" << docente->getEspecialidad() << ")"
                 << " | Curso: " << curso->getNombre()
                 << " [" << curso->getCodigo() << "]" << endl;
        }
};

// Función para liberar memoria de los objetos
void liberarMemoria(vector<Estudiante*>& estudiantes, vector<Docente*>& docentes, vector<Curso*>& cursos, vector<Asociacion*>& asociaciones) 
{
    for (auto est : estudiantes) delete est;
    for (auto doc : docentes) delete doc;
    for (auto cur : cursos) delete cur;
    for (auto asoc : asociaciones) delete asoc;
}

// Función principal (con menú interactivo)
int main() 
{
    vector<Estudiante*> estudiantes;
    vector<Docente*> docentes;
    vector<Curso*> cursos;
    vector<Asociacion*> asociaciones;

    int opcion;
    do 
    {
     cout << "\n=== Menu ===\n";
        cout << "1. Crear Estudiante\n";
        cout << "2. Crear Docente\n";
        cout << "3. Crear Curso\n";
        cout << "4. Crear Asociacion\n";
        cout << "5. Mostrar Relaciones\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) 
        {
            case 1: 
            {
                string nombre;
                int id;
                cout << "Ingrese el nombre del estudiante: ";
                cin.ignore();  // Limpiar el buffer
                getline(cin, nombre);
                cout << "Ingrese el ID del estudiante: ";
                cin >> id;
                estudiantes.push_back(new Estudiante(nombre, id));
                cout << "Estudiante creado exitosamente.\n";
                break;
            }
            case 2: 
            {
                string nombre, especialidad;
                cout << "Ingrese el nombre del docente: ";
                cin.ignore();  // Limpiar el buffer
                getline(cin, nombre);
                cout << "Ingrese la especialidad del docente: ";
                getline(cin, especialidad);
                docentes.push_back(new Docente(nombre, especialidad));
                cout << "Docente creado exitosamente.\n";
                break;
            }
            case 3: 
            {
                string nombre, codigo;
                cout << "Ingrese el nombre del curso: ";
                cin.ignore();  // Limpiar el buffer
                getline(cin, nombre);
                cout << "Ingrese el código del curso: ";
                getline(cin, codigo);
                cursos.push_back(new Curso(nombre, codigo));
                cout << "Curso creado exitosamente.\n";
                break;
            }
            case 4: 
            {
                if (estudiantes.empty() || docentes.empty() || cursos.empty()) 
                {
                    cout << "Debe haber al menos un estudiante, docente y curso creados antes de asociar.\n";
                } 
                else 
                {
                    cout << "\n=== Lista de Estudiantes ===\n";
                    for (int i = 0; i < estudiantes.size(); i++) 
                    {
                        cout << i + 1 << ". " << estudiantes[i]->getNombre() << endl;
                    }

                    cout << "\n=== Lista de Docentes ===\n";
                    for (int i = 0; i < docentes.size(); i++) 
                    {
                        cout << i + 1 << ". " << docentes[i]->getNombre() << " (" << docentes[i]->getEspecialidad() << ")\n";
                    }

                    cout << "\n=== Lista de Cursos ===\n";
                    for (int i = 0; i < cursos.size(); i++) 
                    {
                        cout << i + 1 << ". " << cursos[i]->getNombre() << " [" << cursos[i]->getCodigo() << "]\n";
                    }

                    int estIndex, docIndex, curIndex;
                    cout << "Seleccione el estudiante (1 a " << estudiantes.size() << "): ";
                    cin >> estIndex;
                    cout << "Seleccione el docente (1 a " << docentes.size() << "): ";
                    cin >> docIndex;
                    cout << "Seleccione el curso (1 a " << cursos.size() << "): ";
                    cin >> curIndex;

                    // Ajustar índices para que comiencen desde 0
                    estIndex--;
                    docIndex--;
                    curIndex--;

                    if (estIndex >= 0 && estIndex < estudiantes.size() &&
                        docIndex >= 0 && docIndex < docentes.size() &&
                        curIndex >= 0 && curIndex < cursos.size()) 
                    {
                        asociaciones.push_back(new Asociacion(estudiantes[estIndex], docentes[docIndex], cursos[curIndex]));
                        cout << "Asociación creada exitosamente.\n";
                    } 
                    else 
                    {
                        cout << "Índices inválidos, intente nuevamente.\n";
                    }
                }
                break;
            }
            case 5: 
            {
                if (asociaciones.empty()) 
                {
                    cout << "No hay asociaciones para mostrar.\n";
                } 
                else 
                {
                    cout << "\n=== Relaciones Estudiante - Docente - Curso ===\n";
                    for (auto asoc : asociaciones) 
                    {
                        asoc->mostrarRelacion();
                    }
                }
                break;
            }
            case 6:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción inválida, intente nuevamente.\n";
                break;
        }
    } while (opcion != 6);

    liberarMemoria(estudiantes, docentes, cursos, asociaciones);

    return 0;
}
