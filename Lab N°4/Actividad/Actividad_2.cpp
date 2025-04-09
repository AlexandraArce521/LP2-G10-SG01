#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Estudiante; // Declaración anticipada

// Clase Curso
class Curso 
{
    private:
        string nombre;
        string codigo;
        string descripcion;
        string fechaInicio;
        string fechaFin;
        vector<Estudiante*> estudiantes;
    
    public:
        Curso(string nom, string cod, string desc, string inicio, string fin) 
        {
            nombre = nom;
            codigo = cod;
            descripcion = desc;
            fechaInicio = inicio;
            fechaFin = fin;
        }
    
        void agregarEstudiante(Estudiante* estudiante)
        {
            estudiantes.push_back(estudiante);
        }
    
        void eliminarEstudiante(Estudiante* estudiante) 
        {
            for (int i = 0; i < estudiantes.size(); i++) 
            {
                if (estudiantes[i] == estudiante) 
                {
                    estudiantes.erase(estudiantes.begin() + i);
                    break;
                }
            }
        }
    
        void imprimirEstudiantes();
    
        string getNombre() { return nombre; }
};

// Clase Estudiante
class Estudiante {
    private:
        string nombre;
        string apellido;
        int id;
        string correo;
        vector<Curso*> cursos;
    
    public:
        Estudiante(string nom, string ape, int identificador, string email) 
        {
            nombre = nom;
            apellido = ape;
            id = identificador;
            correo = email;
        }
    
        void agregarCurso(Curso* curso) 
        {
            cursos.push_back(curso);
        }
    
        void eliminarCurso(Curso* curso) 
        {
            for (int i = 0; i < cursos.size(); i++) 
            {
                if (cursos[i] == curso) 
                {
                    cursos.erase(cursos.begin() + i);
                    break;
                }
            }
        }
    
        void imprimirCursos() 
        {
            cout << "Cursos de " << nombre << " " << apellido << ":" << endl;
            for (int i = 0; i < cursos.size(); i++) 
            {
                cout << "- " << cursos[i]->getNombre() << endl;
            }
        }
    
        string getNombreCompleto() 
        {
            return nombre + " " + apellido;
        }
    
        int getId() { return id; }
};

// Implementación de método fuera de la clase Curso
void Curso::imprimirEstudiantes() 
{
    cout << "Estudiantes en el curso " << nombre << ":" << endl;
    for (int i = 0; i < estudiantes.size(); i++) 
    {
        cout << "- " << estudiantes[i]->getNombreCompleto() << endl;
    }
}

// Función principal
int main() 
{
    vector<Estudiante*> estudiantes;
    vector<Curso*> cursos;
    int opcion;

    do 
    {
        cout << "\n========== MENÚ PRINCIPAL ==========\n";
        cout << "1. Registrar nuevo estudiante\n";
        cout << "2. Registrar nuevo curso\n";
        cout << "3. Asociar estudiante a curso\n";
        cout << "4. Eliminar estudiante de curso\n";
        cout << "5. Ver estudiantes por curso\n";
        cout << "6. Ver cursos por estudiante\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) 
        {
            case 1: 
            {
                string nombre, apellido, correo;
                int id;
                cout << "Nombre: "; getline(cin, nombre);
                cout << "Apellido: "; getline(cin, apellido);
                cout << "ID: "; cin >> id; cin.ignore();
                cout << "Correo: "; getline(cin, correo);

                estudiantes.push_back(new Estudiante(nombre, apellido, id, correo));
                cout << "Estudiante registrado con éxito.\n";
                break;
            }

            case 2: 
            {
                string nombre, codigo, desc, inicio, fin;
                cout << "Nombre del curso: "; getline(cin, nombre);
                cout << "Código: "; getline(cin, codigo);
                cout << "Descripción: "; getline(cin, desc);
                cout << "Fecha de inicio: "; getline(cin, inicio);
                cout << "Fecha de fin: "; getline(cin, fin);

                cursos.push_back(new Curso(nombre, codigo, desc, inicio, fin));
                cout << "Curso registrado con éxito.\n";
                break;
            }

            case 3: {
                if (estudiantes.empty() || cursos.empty()) 
                {
                    cout << "Debe haber al menos un estudiante y un curso registrados.\n";
                    break;
                }

                cout << "\nEstudiantes disponibles:\n";
                for (int i = 0; i < estudiantes.size(); i++)
                    cout << i << ". " << estudiantes[i]->getNombreCompleto() << endl;

                cout << "Seleccione estudiante: ";
                int idxEst; cin >> idxEst;

                cout << "\nCursos disponibles:\n";
                for (int i = 0; i < cursos.size(); i++)
                    cout << i << ". " << cursos[i]->getNombre() << endl;

                cout << "Seleccione curso: ";
                int idxCurso; cin >> idxCurso;

                cursos[idxCurso]->agregarEstudiante(estudiantes[idxEst]);
                estudiantes[idxEst]->agregarCurso(cursos[idxCurso]);

                cout << "Asociación realizada correctamente.\n";
                break;
            }

            case 4: 
            {
                if (estudiantes.empty() || cursos.empty()) 
                {
                    cout << "Debe haber al menos un estudiante y un curso registrados.\n";
                    break;
                }

                cout << "\nEstudiantes disponibles:\n";
                for (int i = 0; i < estudiantes.size(); i++)
                    cout << i << ". " << estudiantes[i]->getNombreCompleto() << endl;

                cout << "Seleccione estudiante: ";
                int idxEst; cin >> idxEst;

                cout << "\nCursos disponibles:\n";
                for (int i = 0; i < cursos.size(); i++)
                    cout << i << ". " << cursos[i]->getNombre() << endl;

                cout << "Seleccione curso: ";
                int idxCurso; cin >> idxCurso;

                cursos[idxCurso]->eliminarEstudiante(estudiantes[idxEst]);
                estudiantes[idxEst]->eliminarCurso(cursos[idxCurso]);

                cout << "Asociación eliminada correctamente.\n";
                break;
            }

            case 5: 
            {
                for (int i = 0; i < cursos.size(); i++) 
                {
                    cursos[i]->imprimirEstudiantes();
                    cout << endl;
                }
                break;
            }

            case 6: 
            {
                for (int i = 0; i < estudiantes.size(); i++) 
                {
                    estudiantes[i]->imprimirCursos();
                    cout << endl;
                }
                break;
            }

            case 0:
                cout << "Fin del programa.\n";
                break;

            default:
                cout << "Opción inválida.\n";
        }

    } while (opcion != 0);

    // Liberar memoria
    for (int i = 0; i < estudiantes.size(); i++) delete estudiantes[i];
    for (int i = 0; i < cursos.size(); i++) delete cursos[i];

    return 0;
}
