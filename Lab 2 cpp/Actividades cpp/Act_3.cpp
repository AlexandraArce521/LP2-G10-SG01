#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ====== CLASE PERSONA ======
class Persona {
private:
    string nombre;
    int edad;
public:
    Persona(string n, int e) : nombre(n), edad(e) {}

    // Getters y Setters
    string getNombre() const { return nombre; }
    void setNombre(const string &n) { nombre = n; }

    int getEdad() const { return edad; }
    void setEdad(int e) { 
        if (e >= 0) {
            edad = e;
        } else {
            cout << "Edad no válida." << endl;
        }
    }

    // Para mostrar la información de la persona
    void mostrarPersona() const {
        cout << "Persona: " << nombre << ", Edad: " << edad << endl;
    }
};

// ====== CLASE LIBRO ======
class Libro {
private:
    string titulo;
    string autor;
public:
    Libro(string t, string a) : titulo(t), autor(a) {}

    // Getters y Setters
    string getTitulo() const { return titulo; }
    void setTitulo(const string &t) { titulo = t; }

    string getAutor() const { return autor; }
    void setAutor(const string &a) { autor = a; }

    // Método auxiliar para mostrar info
    void mostrarInfoLibro() const {
        cout << "Libro: " << titulo << ", Autor: " << autor << endl;
    }

    // Método para comparar con otro libro
    bool esIgualA(const Libro &otro) const {
        return (titulo == otro.titulo && autor == otro.autor);
    }
};

// ====== Funciones de ayuda para manejo de vectores ======

// Agregar un objeto Persona al vector
void agregarPersona(vector<Persona> &personas, const Persona &p) {
    personas.push_back(p);
}

// Imprimir la lista de Personas
void listarPersonas(const vector<Persona> &personas) {
    cout << "== Listado de Personas ==" << endl;
    for (const auto &p : personas) {
        p.mostrarPersona();
    }
}

// Buscar Persona por nombre
int buscarPersonaPorNombre(const vector<Persona> &personas, const string &nombreBuscado) {
    for (size_t i = 0; i < personas.size(); i++) {
        if (personas[i].getNombre() == nombreBuscado) {
            return i; // Retorna el índice donde se encontró
        }
    }
    return -1; // No encontrado
}

// Eliminar Persona por nombre
bool eliminarPersona(vector<Persona> &personas, const string &nombreAEliminar) {
    int indice = buscarPersonaPorNombre(personas, nombreAEliminar);
    if (indice != -1) {
        personas.erase(personas.begin() + indice);
        return true;
    }
    return false;
}

// Actualizar la edad de una Persona por nombre
bool actualizarEdadPersona(vector<Persona> &personas, const string &nombreObjetivo, int nuevaEdad) {
    int indice = buscarPersonaPorNombre(personas, nombreObjetivo);
    if (indice != -1) {
        personas[indice].setEdad(nuevaEdad);
        return true;
    }
    return false;
}

// ====== Funciones de ayuda para manejo de vectores de Libro ======

// Agregar un objeto Libro al vector
void agregarLibro(vector<Libro> &libros, const Libro &l) {
    libros.push_back(l);
}

// Imprimir la lista de Libros
void listarLibros(const vector<Libro> &libros) {
    cout << "== Listado de Libros ==" << endl;
    for (const auto &l : libros) {
        l.mostrarInfoLibro();
    }
}

// Buscar Libro por título
int buscarLibroPorTitulo(const vector<Libro> &libros, const string &tituloBuscado) {
    for (size_t i = 0; i < libros.size(); i++) {
        if (libros[i].getTitulo() == tituloBuscado) {
            return i;
        }
    }
    return -1;
}

// Eliminar Libro por título
bool eliminarLibro(vector<Libro> &libros, const string &tituloAEliminar) {
    int indice = buscarLibroPorTitulo(libros, tituloAEliminar);
    if (indice != -1) {
        libros.erase(libros.begin() + indice);
        return true;
    }
    return false;
}

// Comparar dos libros en el vector
void compararDosLibros(const Libro &libroA, const Libro &libroB) {
    if (libroA.esIgualA(libroB)) {
        cout << "Los libros son iguales (título y autor coinciden)." << endl;
    } else {
        cout << "Los libros son distintos." << endl;
    }
}

// ====== FUNCIÓN PRINCIPAL ======
int main() {
    // e) Crear objetos de las clases creadas y usarlos con getters/setters
    vector<Persona> listaPersonas;
    Persona p1("Carlos", 25);
    Persona p2("Ana", 31);

    agregarPersona(listaPersonas, p1);
    agregarPersona(listaPersonas, p2);

    // Mostrar personas
    listarPersonas(listaPersonas);

    // Modificar la edad de Ana
    actualizarEdadPersona(listaPersonas, "Ana", 31);
    listarPersonas(listaPersonas);

    // Eliminar a Carlos
    if (eliminarPersona(listaPersonas, "Carlos")) {
        cout << "Carlos eliminado de la lista." << endl;
    }
    listarPersonas(listaPersonas);

    // f) Arreglos (vectores) de Libros
    vector<Libro> listaLibros;
    Libro l1("El Principito", "Antoine de Saint-Exupery");
    Libro l2("Cien Años de Soledad", "Gabriel Garcia Marquez");
    Libro l3("El Hobbit", "J.R.R. Tolkien");

    agregarLibro(listaLibros, l1);
    agregarLibro(listaLibros, l2);
    agregarLibro(listaLibros, l3);

    // Mostrar libros
    listarLibros(listaLibros);

    // g) Eliminar y actualizar
    // Eliminar un libro por título
    if (eliminarLibro(listaLibros, "Cien Años de Soledad")) {
        cout << "Libro eliminado exitosamente." << endl;
    }
    listarLibros(listaLibros);

    // Actualizar el autor de 'El Hobbit'
    int idxHobbit = buscarLibroPorTitulo(listaLibros, "El Hobbit");
    if (idxHobbit != -1) {
        listaLibros[idxHobbit].setAutor("John Ronald Reuel Tolkien");
    }
    listarLibros(listaLibros);

    // h) Comparación de objetos (Libro)
    Libro l4("El Hobbit", "J.R.R. Tolkien");
    cout << "\nComparando 'El Hobbit' con autor modificado vs uno nuevo:" << endl;
    compararDosLibros(listaLibros[idxHobbit], l4);

    return 0;
}
