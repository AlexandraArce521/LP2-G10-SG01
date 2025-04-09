#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Autor;
class Libro;
class Prestamo;
class Fecha;

class Autor {
private:
    string nombre, nacionalidad;
    vector<Libro*> libros;

public:
    Autor(string nombre, string nacionalidad)
    : nombre(nombre), nacionalidad(nacionalidad) {}

    string getNombre() const {
        return nombre;
    }

    void agregarLibro(Libro* libro);
};

class Libro {
private:
    int ISBN;
    string titulo;
    int anioPublic;
    int cantEjempleares;
    vector<Autor*> autores;

public:
    Libro(string titulo, int anioPublic, int cantEjempleares, int ISBN)
    : titulo(titulo), anioPublic(anioPublic), cantEjempleares(cantEjempleares), ISBN(ISBN) {}

    string getTitulo() {
        return titulo;
    }

    int getCantidadEjemplares() {
        return cantEjempleares;
    }

    int getAnioPublic() {
        return anioPublic;
    }

    int getISBN() {
        return ISBN;
    }

    void agregarAutor(Autor* autor) {
        autores.push_back(autor);
    }

    void mostrarLibro() {
        cout << "---LISTA DE LIBROS---" << endl;
        cout << "Libro: " << titulo << endl;
        cout << "Año de Publicación: " << anioPublic << endl;
        for (Autor* a : autores) {
            cout << "- " << a->getNombre() << endl;
        }
        cout << "Cantidad de ejemplares disponibles: " << cantEjempleares << endl;
    }

    bool prestarLibro(int cantidad) {
        if (cantEjempleares >= cantidad) {
            cantEjempleares -= cantidad;  // Decrementa la cantidad de ejemplares disponibles
            return true;
        }
        return false;  // No hay suficientes ejemplares
    }
};

void Autor::agregarLibro(Libro* libro) {
    libros.push_back(libro);
    libro->agregarAutor(this);
}

class Usuario {
private:
    string nombre;
    string direccion;
    int telefono;
    vector<Libro*> librosPrestados;

public:
    Usuario(string nombre, string direccion, int telefono)
    : nombre(nombre), direccion(direccion), telefono(telefono) {}

    void prestarLibro(Libro* libro, int cantidad) {
        if (libro->prestarLibro(cantidad)) {
            librosPrestados.push_back(libro);
            cout << "Libro '" << libro->getTitulo() << "' prestado exitosamente. Cantidad: " << cantidad << endl;
        } else {
            cout << "No hay suficientes ejemplares disponibles de '" << libro->getTitulo() << "'." << endl;
        }
    }

    string getNombre() const {
        return nombre;
    }

    void mostrarLibrosPrestados() {
        cout << "Libros prestados a " << nombre << endl;
        for (Libro* libro : librosPrestados) {
            cout << "- " << libro->getTitulo() << endl;
        }
    }
};

class Fecha {
private:
    int dia;
    int mes;
    int anio;

public:
    void ingresarFecha(const string& tipo) {
        cout << "Ingrese la fecha de " << tipo << " (DD MM AAAA): ";
        cin >> dia >> mes >> anio;
    }

    void mostrarFecha() const {
        cout << dia << "/" << mes << "/" << anio << endl;
    }
};

class Prestamo {
private:
    Usuario* usuario;
    Libro* libro;
    Fecha fechaPrestamo;
    Fecha fechaDevolucion;

public:
    Prestamo(Usuario* usuario, Libro* libro, Fecha fechaPrestamo, Fecha fechaDevolucion)
    : usuario(usuario), libro(libro), fechaPrestamo(fechaPrestamo), fechaDevolucion(fechaDevolucion) {}

    void mostrarDetalle() {
        cout << "Prestamo de: " << libro->getTitulo() << endl;
        cout << "Usuario: " << usuario->getNombre() << endl;
        cout << "Fecha de Prestamo: "; fechaPrestamo.mostrarFecha();
        cout << "Fecha de Devolucion: "; fechaDevolucion.mostrarFecha();
    }
};

int main() {
    vector<string> menuPrincipal = {
        "1. Registrar Usuario",
        "2. Agregar libro a biblioteca",
        "3. Prestar Libro a Usuario",
        "4. Mostrar Libros Prestados",
        "5. Mostrar Libros en la biblioteca",
        "6. Salir"
    };

    int opcion;
    string nombreUsuario, direccionUsuario, tituloLibro, autor;
    int telefonoUsuario, ISBN, anioPublic, ejemplares;
    string fechaPrestamo, fechaDevolucion;
    Usuario* usuario = nullptr;
    vector<Libro*> biblioteca;  // Vector para almacenar los libros de la biblioteca

    do {
        cout << "\nBienvenido al menú principal!" << endl;

        for (const string& opcionMenu : menuPrincipal) {
            cout << opcionMenu << endl;
        }

        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                cout << "Agregar nuevo Usuario." << endl;
                cout << "\nIngrese su nombre: ";
                cin >> nombreUsuario;
                cout << "Ingrese su dirección: ";
                cin >> direccionUsuario;
                cout << "Ingrese el teléfono: ";
                cin >> telefonoUsuario;
                usuario = new Usuario(nombreUsuario, direccionUsuario, telefonoUsuario);
                break;
            }

            case 2: {
                cout << "Ingrese el titulo del libro: ";
                cin.ignore();
                getline(cin, tituloLibro);

                cout << "Ingrese el ISBN del libro: ";
                cin >> ISBN;

                cout << "Ingrese el año de publicación: ";
                cin >> anioPublic;

                cout << "Ingrese la cantidad de ejemplares del libro: ";
                cin >> ejemplares;

                cout << "Ingrese el nombre del autor: ";
                cin.ignore();
                getline(cin, autor);

                // Crear autor y libro
                Autor* nuevoAutor = new Autor(autor, "Desconocida"); // Cambiar si tienes más datos del autor
                Libro* libro = new Libro(tituloLibro, anioPublic, ejemplares, ISBN);
                libro->agregarAutor(nuevoAutor);
                biblioteca.push_back(libro);  // Agregar libro a la biblioteca
                nuevoAutor->agregarLibro(libro); // Asocia el libro con el autor
                break;
            }

            case 3: {
                cout << "Prestar Libro\nIngrese el nombre del usuario: ";
                cin.ignore();
                getline(cin, nombreUsuario);

                cout << "Ingrese el titulo del libro: ";
                getline(cin, tituloLibro);

                cout << "Ingrese la cantidad de ejemplares a prestar: ";
                int cantidad;
                cin >> cantidad;

                Libro* libro = nullptr;
                for (Libro* l : biblioteca) {
                    if (l->getTitulo() == tituloLibro) {
                        libro = l;
                        break;
                    }
                }

                if (libro && libro->getCantidadEjemplares() >= cantidad) {
                    libro->prestarLibro(cantidad);
                    usuario->prestarLibro(libro, cantidad);
                } else {
                    cout << "No hay suficientes ejemplares disponibles para este libro." << endl;
                    break;
                }

                // Usando la clase Fecha para las fechas
                Fecha fechaP, fechaD;
                fechaP.ingresarFecha("prestamo");
                fechaD.ingresarFecha("devolucion");

                Prestamo prestamo(usuario, libro, fechaP, fechaD);
                prestamo.mostrarDetalle();
                break;
            }

            case 4: {
                if (usuario != nullptr) {
                    usuario->mostrarLibrosPrestados();
                } else {
                    cout << "No hay usuario registrado." << endl;
                }
                break;
            }

            case 5: {
                for (Libro* libro : biblioteca) {
                    libro->mostrarLibro();
                }
                break;
            }

            case 6: {
                cout << "Saliendo del Sistema..." << endl;
                break;
            }
        }
    } while (opcion != 6);

    return 0;
}
