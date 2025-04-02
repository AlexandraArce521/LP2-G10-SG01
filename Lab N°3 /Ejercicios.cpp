#include <iostream>
#include <vector>
#include <string>

using namespace std;

class ITarea 
{
    public:
        virtual void mostrarDetalles() const = 0;
        virtual ~ITarea() {}
};

class IProyecto 
{
    public:
        virtual void mostrarDetalles() const = 0;
        virtual ~IProyecto() {}
};

class IComentario 
{
    public:
        virtual void mostrarComentario() const = 0;
        virtual ~IComentario() {}
};

class IArchivo 
{
    public:
        virtual void mostrarArchivo() const = 0;
        virtual ~IArchivo() {}
};

class TareaUsuario : public ITarea 
{
    private:
        string descripcion;
    public:
        TareaUsuario(const string& desc) : descripcion(desc) {}
        void mostrarDetalles() const override 
        {
            cout << "Tarea: " << descripcion << endl;
        }
        
        string getDescripcion() const
        {
            return descripcion;
        }
};

class ProyectoUsuario : public IProyecto 
{
    private:
        string nombreProyecto;
    public:
        ProyectoUsuario(const string& nombre) : nombreProyecto(nombre) {}
        void mostrarDetalles() const override 
        {
            cout << "Proyecto: " << nombreProyecto << endl;
        }
        
        string getNombre() const
        {
            return nombreProyecto;
        }
};

class Comentario : public IComentario 
{
    private:
        string TipoTP; // "Tarea" o "Proyecto"
        string NombreTP;
        string comentario;
   
    public:
        Comentario(const string& type, const string& name, const string& com)
            : TipoTP(type), NombreTP(name), comentario(com) {}
    
        void mostrarComentario() const 
        {
            cout << TipoTP << ": " << NombreTP << " - Comentario: " << comentario << endl;
        }
};

class Archivo : public IArchivo 
{
    private:
        string nombreArchivo;
    public:
        Archivo(const string& nombre) : nombreArchivo(nombre) {}
        void mostrarArchivo() const override 
        {
            cout << "Archivo: " << nombreArchivo << endl;
        }
};

class GestorTareas 
{
    private:
        vector<ITarea*> tareas;
    public:
        ~GestorTareas() 
        {
            for (ITarea* tarea : tareas) 
            {
                delete tarea;
            }
        }

        void agregarTarea(const string& descripcion) 
        {
            tareas.push_back(new TareaUsuario(descripcion));
        }
        
        const vector<ITarea*>& obtenerTareas() const 
        {
            return tareas;
        }
};

class VerifTarea 
{
    private:
        const GestorTareas& gestorTareas;
    
    public:
        VerifTarea(const GestorTareas& gestor) : gestorTareas(gestor) {}

        bool existeTarea(const string& nombre) const 
        {
            for (const auto& tarea : gestorTareas.obtenerTareas()) 
            {
                const TareaUsuario* tareaUsuario = dynamic_cast<const TareaUsuario*>(tarea);
                if (tareaUsuario && tareaUsuario->getDescripcion() == nombre) 
                {
                    return true;
                }
            }
            return false;
        }
};

class GestorProyectos 
{
    private:
        vector<IProyecto*> proyectos;
    public:
        ~GestorProyectos() 
        {
            for (IProyecto* proyecto : proyectos) 
            {
                delete proyecto;
            }
        }
        
        void agregarProyecto(const string& nombre) 
        {
            proyectos.push_back(new ProyectoUsuario(nombre));
        }
        
        const vector<IProyecto*>& obtenerProyectos() const 
        {
            return proyectos;
        }
};

class VerifProyecto 
{
    private:
        const GestorProyectos& gestorProyectos;
    public:
        VerifProyecto(const GestorProyectos& gestor) : gestorProyectos(gestor) {}

        bool existeProyecto(const string& nombre) const 
        {
            for (const auto& proyecto : gestorProyectos.obtenerProyectos()) 
            {
                const ProyectoUsuario* proyectoUsuario = dynamic_cast<const ProyectoUsuario*>(proyecto);
                if (proyectoUsuario && proyectoUsuario->getNombre() == nombre) 
                {
                    return true;
                }
            }
            return false;
        }
};

class GestorComentarios 
{
    private:
        vector<Comentario*> comentarios;
    public:
        ~GestorComentarios() 
        {
            for (auto c : comentarios)
            {
                delete c;
            }
        }
        
        void agregarComentario(const string& type, const string& name, const string& com) 
        {
            comentarios.push_back(new Comentario(type, name, com));
        }
        
        const vector<Comentario*>& obtenerComentarios() const 
        {
            return comentarios;
        }
    };

class VistaTareas 
{
    public:
        static void mostrarTareas(const GestorTareas& gestor) 
        {
            const vector<ITarea*>& tareas = gestor.obtenerTareas();
            if (tareas.empty()) 
            {
                cout << "No hay tareas registradas." << endl;
                return;
            }
            
            cout << "\nLista de tareas" << endl;
            cout << "------------------------" << endl;
            for (const auto& tarea : tareas) 
            {
                tarea->mostrarDetalles();
                cout << "------------------------" << endl;
            }
        }
};

class VistaProyectos 
{
    public:
        static void mostrarProyectos(const GestorProyectos& gestor) 
        {
            const vector<IProyecto*>& proyectos = gestor.obtenerProyectos();
            if (proyectos.empty()) 
            {
                cout << "No hay proyectos registrados." << endl;
                return;
            }
            
            cout << "\nLista de proyectos" << endl;
            cout << "------------------------" << endl;
            for (const auto& proyecto : proyectos) 
            {
                proyecto->mostrarDetalles();
                cout << "------------------------" << endl;
            }
        }
};

class VistaComentarios
{
    public:
        static void mostrarComentarios(const GestorComentarios& gestor) 
        {
            const vector<Comentario*>& comentarios = gestor.obtenerComentarios();
            if (comentarios.empty()) 
            {
                cout << "No hay comentarios registrados." << endl;
                return;
            }
            
            cout << "\nLista de comentarios" << endl;
            cout << "------------------------" << endl;
            for (const auto& com : comentarios) 
            {
                com->mostrarComentario();
                cout << "------------------------" << endl;
            }
        }
};

int main() 
{
    GestorTareas gestorTareas;
    GestorProyectos gestorProyectos;
    GestorComentarios gestorComentarios;
    
    int opcionMenu;
    vector<string> lista = 
    {
        "1. Agregar tarea",
        "2. Mostrar tareas",
        "3. Agregar proyecto",
        "4. Mostrar proyectos",
        "5. Agregar comentario",
        "6. Mostrar comentarios",
        "7. Salir"
    };
    do 
    {
        cout << "\nMenú de Opciones:" << endl;
        for (const string &opcion : lista) 
        {
            cout << opcion << endl;
        }

        cout << "\nSeleccione una opción: ";
        cin >> opcionMenu;
        cin.ignore();

        switch (opcionMenu) 
        {
            case 1: 
            {
                string descripcion;
                cout << "Ingrese la descripción de la tarea: ";
                getline(cin, descripcion);
                gestorTareas.agregarTarea(descripcion);
                cout << "Tarea agregada con éxito." << endl << endl;
                break;
            }
            
            case 2: 
            {
                VistaTareas::mostrarTareas(gestorTareas);
                break;
            }
            
            case 3: 
            {
                string nombreProyecto;
                cout << "Ingrese el nombre del proyecto: ";
                getline(cin, nombreProyecto);
                gestorProyectos.agregarProyecto(nombreProyecto);
                cout << "Proyecto agregado con éxito." << endl << endl;
                break;
            }
            
            case 4: 
            {
                VistaProyectos::mostrarProyectos(gestorProyectos);
                break;
            }
            
            case 5: 
            {
                string tipo;
                int opcionTipo;
                cout << "Seleccione el tipo de comentario" << endl;
                cout << "(1 = Tarea, 2 = Proyecto): ";
                cin >> opcionTipo;
                
                cin.ignore();
                if (opcionTipo == 1)
                    tipo = "Tarea";
                else if (opcionTipo == 2)
                    tipo = "Proyecto";
                else 
                {
                    cout << "Tipo inválido." << endl;
                    break;
                }
                
                string nombre;
                cout << "Ingrese el nombre de la " << tipo << ": ";
                getline(cin, nombre);
                
                VerifTarea verificadorTarea(gestorTareas);
                VerifProyecto verificadorProyecto(gestorProyectos);
            
                if ((tipo == "Tarea" && !verificadorTarea.existeTarea(nombre)) ||
                    (tipo == "Proyecto" && !verificadorProyecto.existeProyecto(nombre))) 
                {
                    cout << "Error: No existe " << tipo << " con ese nombre." << endl;
                    break;
                }
                
                string comentario;
                cout << "Ingrese el comentario: ";
                getline(cin, comentario);
                gestorComentarios.agregarComentario(tipo, nombre, comentario);
                
                cout << "Comentario agregado con éxito." << endl;
                break;
            }
            
            case 6: 
            {
                VistaComentarios::mostrarComentarios(gestorComentarios);
                break;
            }
            
            case 7: 
            {
                cout << "Saliendo del menú..." << endl;
                break;
            }
            
            default: 
            {
                cout << "Opción no válida. Intente de nuevo." << endl;
                break;
            }
        }
    } while (opcionMenu != 7);

    return 0;
}
