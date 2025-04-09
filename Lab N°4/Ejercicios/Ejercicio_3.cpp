#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// Declaraciones anticipadas
class Asignatura;
class Profesor;

// Clase Estudiante
class Estudiante 
{
    private:
        string nombre;
        string direccion;
        string matricula;
        vector<Asignatura*> asignaturas;
        map<Asignatura*, float> notas;
        map<Asignatura*, int> faltas;
    
    public:
        Estudiante(string nom, string dir, string mat) 
        {
            nombre = nom;
            direccion = dir;
            matricula = mat;
        }
    
        string getNombre() { return nombre; }
        string getMatricula() { return matricula; }
    
        void matricular(Asignatura* asignatura);
        void asignarNota(Asignatura* asignatura, float nota);
        void registrarFalta(Asignatura* asignatura);
        void mostrarAsignaturas();
        void mostrarNotasYFaltas();
};

// Clase Profesor
class Profesor 
{
    private:
        string nombre;
        string direccion;
        string telefono;
        vector<Asignatura*> asignaturas;
    
    public:
        Profesor(string nom, string dir, string tel) 
        {
            nombre = nom;
            direccion = dir;
            telefono = tel;
        }
    
        string getNombre() { return nombre; }
    
        void agregarAsignatura(Asignatura* asignatura);
        void mostrarAsignaturas();
};

// Clase Asignatura
class Asignatura 
{
    private:
        string codigo;
        string nombre;
        string descripcion;
        Profesor* profesor;
    
    public:
        Asignatura(string cod, string nom, string desc) 
        {
            codigo = cod;
            nombre = nom;
            descripcion = desc;
            profesor = nullptr;
        }
    
        string getNombre() { return nombre; }
        string getCodigo() { return codigo; }
    
        void asignarProfesor(Profesor* prof) { profesor = prof; }
        Profesor* getProfesor() { return profesor; }
};

// IMPLEMENTACIONES DE MÉTODOS DE ESTUDIANTE
void Estudiante::matricular(Asignatura* asignatura) 
{
    asignaturas.push_back(asignatura);
    notas[asignatura] = 0.0;
    faltas[asignatura] = 0;
}

void Estudiante::asignarNota(Asignatura* asignatura, float nota) 
{
    notas[asignatura] = nota;
}

void Estudiante::registrarFalta(Asignatura* asignatura) 
{
    faltas[asignatura]++;
}

void Estudiante::mostrarAsignaturas() 
{
    cout << "Asignaturas de " << nombre << ":\n";
    for (auto a : asignaturas) {
        cout << "- " << a->getNombre() << endl;
    }
}

void Estudiante::mostrarNotasYFaltas() 
{
    cout << "Notas y faltas de " << nombre << ":\n";
    for (auto a : asignaturas) {
        cout << "- " << a->getNombre()
             << " | Nota: " << notas[a]
             << " | Faltas: " << faltas[a] << endl;
    }
}

// IMPLEMENTACIÓN DE MÉTODOS DE PROFESOR
void Profesor::agregarAsignatura(Asignatura* asignatura) 
{
    asignaturas.push_back(asignatura);
}

void Profesor::mostrarAsignaturas() 
{
    cout << "Asignaturas impartidas por " << nombre << ":\n";
    for (auto a : asignaturas) {
        cout << "- " << a->getNombre() << " (" << a->getCodigo() << ")\n";
    }
}


int main() 
{
    vector<Estudiante*> estudiantes;
    vector<Profesor*> profesores;
    vector<Asignatura*> asignaturas;

    int opcion;

    do 
    {
        cout << "\n========== MENÚ UNIVERSIDAD ==========\n";
        cout << "1. Registrar estudiante\n";
        cout << "2. Registrar profesor\n";
        cout << "3. Registrar asignatura\n";
        cout << "4. Asignar profesor a asignatura\n";
        cout << "5. Matricular estudiante en asignatura\n";
        cout << "6. Asignar nota a estudiante\n";
        cout << "7. Registrar falta a estudiante\n";
        cout << "8. Mostrar asignaturas de estudiante\n";
        cout << "9. Mostrar notas y faltas de estudiante\n";
        cout << "10. Mostrar asignaturas de profesor\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) 
        {
            case 1: 
            {
                string nombre, direccion, matricula;
                cout << "Nombre: "; getline(cin, nombre);
                cout << "Dirección: "; getline(cin, direccion);
                cout << "Matrícula: "; getline(cin, matricula);
                estudiantes.push_back(new Estudiante(nombre, direccion, matricula));
                cout << "Estudiante registrado.\n";
                break;
            }
            case 2: 
            {
                string nombre, direccion, telefono;
                cout << "Nombre: "; getline(cin, nombre);
                cout << "Dirección: "; getline(cin, direccion);
                cout << "Teléfono: "; getline(cin, telefono);
                profesores.push_back(new Profesor(nombre, direccion, telefono));
                cout << "Profesor registrado.\n";
                break;
            }
            case 3: 
            {
                string codigo, nombre, descripcion;
                cout << "Código: "; getline(cin, codigo);
                cout << "Nombre: "; getline(cin, nombre);
                cout << "Descripción: "; getline(cin, descripcion);
                asignaturas.push_back(new Asignatura(codigo, nombre, descripcion));
                cout << "Asignatura registrada.\n";
                break;
            }
            case 4: 
            {
                if (profesores.empty() || asignaturas.empty()) 
                {
                    cout << "Debe haber profesores y asignaturas registradas.\n";
                    break;
                }

                cout << "Profesores disponibles:\n";
                for (int i = 0; i < profesores.size(); i++)
                    cout << i << ". " << profesores[i]->getNombre() << endl;

                cout << "Seleccione profesor: ";
                int idxProf; cin >> idxProf;

                cout << "Asignaturas disponibles:\n";
                for (int i = 0; i < asignaturas.size(); i++)
                    cout << i << ". " << asignaturas[i]->getNombre() << endl;

                cout << "Seleccione asignatura: ";
                int idxAsig; cin >> idxAsig;

                asignaturas[idxAsig]->asignarProfesor(profesores[idxProf]);
                profesores[idxProf]->agregarAsignatura(asignaturas[idxAsig]);
                cout << "Profesor asignado a la asignatura.\n";
                break;
            }
            case 5: 
            {
                if (estudiantes.empty() || asignaturas.empty()) 
                {
                    cout << "Debe haber estudiantes y asignaturas registradas.\n";
                    break;
                }

                cout << "Estudiantes disponibles:\n";
                for (int i = 0; i < estudiantes.size(); i++)
                    cout << i << ". " << estudiantes[i]->getNombre() << endl;

                cout << "Seleccione estudiante: ";
                int idxEst; cin >> idxEst;

                cout << "Asignaturas disponibles:\n";
                for (int i = 0; i < asignaturas.size(); i++)
                    cout << i << ". " << asignaturas[i]->getNombre() << endl;

                cout << "Seleccione asignatura: ";
                int idxAsig; cin >> idxAsig;

                estudiantes[idxEst]->matricular(asignaturas[idxAsig]);
                cout << "Estudiante matriculado en la asignatura.\n";
                break;
            }
            case 6: 
            {
                if (estudiantes.empty()) 
                {
                    cout << "No hay estudiantes registrados.\n";
                    break;
                }

                cout << "Estudiantes disponibles:\n";
                for (int i = 0; i < estudiantes.size(); i++)
                    cout << i << ". " << estudiantes[i]->getNombre() << endl;

                cout << "Seleccione estudiante: ";
                int idxEst; cin >> idxEst;

                cout << "Asignaturas del estudiante:\n";
                estudiantes[idxEst]->mostrarAsignaturas();

                cout << "Ingrese el índice de la asignatura (según orden mostrado): ";
                int idxAsig; cin >> idxAsig;

                cout << "Ingrese la nota: ";
                float nota; cin >> nota;

                estudiantes[idxEst]->asignarNota(asignaturas[idxAsig], nota);
                cout << "Nota asignada.\n";
                break;
            }
            case 7: 
            {
                if (estudiantes.empty()) 
                {
                    cout << "No hay estudiantes registrados.\n";
                    break;
                }

                cout << "Estudiantes disponibles:\n";
                for (int i = 0; i < estudiantes.size(); i++)
                    cout << i << ". " << estudiantes[i]->getNombre() << endl;

                cout << "Seleccione estudiante: ";
                int idxEst; cin >> idxEst;

                cout << "Asignaturas del estudiante:\n";
                estudiantes[idxEst]->mostrarAsignaturas();

                cout << "Ingrese el índice de la asignatura (según orden mostrado): ";
                int idxAsig; cin >> idxAsig;

                estudiantes[idxEst]->registrarFalta(asignaturas[idxAsig]);
                cout << "Falta registrada.\n";
                break;
            }
            case 8: 
            {
                for (int i = 0; i < estudiantes.size(); i++) 
                {
                    estudiantes[i]->mostrarAsignaturas();
                    cout << endl;
                }
                break;
            }
            case 9: 
            {
                for (int i = 0; i < estudiantes.size(); i++) 
                {
                    estudiantes[i]->mostrarNotasYFaltas();
                    cout << endl;
                }
                break;
            }
            case 10: 
            {
                for (int i = 0; i < profesores.size(); i++) 
                {
                    profesores[i]->mostrarAsignaturas();
                    cout << endl;
                }
                break;
            }
            case 0:
                cout << "Finalizando programa...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }

    } while (opcion != 0);

    return 0;
}
