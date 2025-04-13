#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
using namespace std;

class Administrador;
class Huesped;
class Habitacion;
class Reserva;


class Habitacion {
private:
    string codigo;
    string tipo;
    double precio;
    bool disponible;

public:
    Habitacion(string codigo, string tipo, double precio)
        : codigo(codigo), tipo(tipo), precio(precio), disponible(true) {}

    string getCodigo() const {
        return codigo;
    }

    string getTipo() const {
        return tipo;
    }

    double getPrecio() const {
        return precio;
    }

    bool estaDisponible() const {
        return disponible;
    }

    void mostrarHabitacion() const {
        cout << "Código: " << codigo << endl;
        cout << "Tipo: " << tipo << endl;
        cout << "Precio: " << precio << endl;
        cout << "Disponibilidad: " << (disponible ? "Disponible" : "No disponible") << endl;
    }

    void reservarHabitacion() {
        disponible = false;
    }

    void cancelarReserva() {
        disponible = true;
    }
};

class Reserva {
private:
    Huesped* huesped;
    Habitacion* habitacion;
    string fechaInicio;
    string fechaFin;

public:
    Reserva(Huesped* huesped, Habitacion* habitacion, string fechaInicio, string fechaFin)
        : huesped(huesped), habitacion(habitacion), fechaInicio(fechaInicio), fechaFin(fechaFin) {}

    void mostrarReserva();

    Habitacion* getHabitacion() const {
        return habitacion;
    }

    Huesped* getHuesped() const {
        return huesped;
    }
};

class Huesped {
private:
    string nombre;
    string dni;
    string nacionalidad;

public:
    Huesped(string nombre, string dni, string nacionalidad): 
    nombre(nombre), dni(dni), nacionalidad(nacionalidad) {}

    void mostrarDatosHuesped() const {
        cout << "Nombre: " << nombre << endl;
        cout << "DNI: " << dni << endl;
        cout << "Nacionalidad: " << nacionalidad << endl;
    }

    // ACTUALIZAR DATOS DE HUESPED
    void actualizarNombre(string nuevoNombre) {
        nombre = nuevoNombre;
    }

    void actualizarDni(string nuevoDni) {
        dni = nuevoDni;
    }

    void actualizarNacionalidad(string nuevaNacionalidad) {
        nacionalidad = nuevaNacionalidad;
    }

    string getDni() const {
        return dni;
    }
    
};

void Reserva::mostrarReserva() {
        cout << "Reserva: " << endl;
        huesped->mostrarDatosHuesped();
        habitacion->mostrarHabitacion();
        cout << "Fecha de inicio: " << fechaInicio << endl;
        cout << "Fecha de fin: " << fechaFin << endl;
    };
    
bool esNumeroValido(const string& dni) {
    if (dni.length() != 8) {
        return false;
    }
    for (char c : dni) {
        if (!isdigit(c)) return false;
    }
    return true;
}

int main() {
    vector<string> list2 = {
        "1. Registrar usuario",
        "2. Actualizar datos de usuario",
        "3. Buscar habitación",
        "4. Reservar habitación",
        "5. Cancelar reserva",
        "6. Salir"};
    vector<string> list1 = {
        "1. Usuario",
        "2. Administrador",
        "3. Salir"};

    vector<Habitacion*> habitaciones;
    vector<Reserva*> reservas;
    vector<Huesped*> huespedes;


    int opcion1;
    int opcion2;
    string nombre;
    string dni;
    string nacionalidad;

    do {
        cout << "\n======== Menú Principal ======" << endl;
        for (const string& opcion : list1) {
            cout << opcion << endl;
        }
        cout << "\nSeleccione una opción: ";
        cin >> opcion1;

        switch (opcion1) {
            case 1: {
                // Menú de usuario
                do {
                    cout << "\n======= Menú de Usuario =======" << endl;
                    for (const string& opcion : list2) {
                        cout << opcion << endl;
                    }
                    cout << "\nSeleccione una opción: ";
                    cin >> opcion2;
                    cin.ignore();

                    switch (opcion2) {
                        case 1: {
                            cout << "[1] Ingrese su nombre: ";
                            getline(cin, nombre);
                            cout << "[1] Ingrese su DNI (8 dígitos): ";
                            cin >> dni;

                            if (esNumeroValido(dni)) {
                                cout << "(°) DNI válido" << endl;
                            } else {
                                cout << "(!) DNI inválido. Debe ingresar exactamente 8 dígitos." << endl;
                                break;
                            }

                            cout << "[1] Ingrese su nacionalidad: ";
                            cin >> nacionalidad;
                            cin.ignore();

                            huespedes.push_back(new Huesped(nombre, dni, nacionalidad));
                            cout << "Usuario registrado con éxito." << endl;
                            break;
                        }

                        case 2: {
                            cout << "[1] Ingrese su DNI para actualizar datos: ";
                            cin >> dni;
                            cin.ignore();
                            bool encontrado = false;
                            for (Huesped* huesped : huespedes) {
                                if (huesped->getDni() == dni) {
                                    encontrado = true;
                                    cout << "[1] Ingrese el nuevo nombre: ";
                                    getline(cin, nombre);
                                    cout << "[1] Ingrese el nuevo DNI: ";
                                    cin >> dni;
                                    cin.ignore();
                                    cout << "[1] Ingrese la nueva nacionalidad: ";
                                    getline(cin, nacionalidad);
                                    huesped->actualizarNombre(nombre);
                                    huesped->actualizarDni(dni);
                                    huesped->actualizarNacionalidad(nacionalidad);
                                    cout << "Datos actualizados con éxito." << endl;
                                    break;
                                }
                            }
                            if (!encontrado) {
                                cout << "No se encontró un usuario con ese DNI." << endl;
                            }
                            break;
                        }

                        case 3: {
                            cout << "====== Habitaciones disponibles ======" << endl;
                            if (habitaciones.empty()) {
                                cout << "No hay habitaciones en el hotel." << endl;
                            } else {
                                for (auto hab : habitaciones) {
                                    hab->mostrarHabitacion();
                                }
                            }
                            break;
                        }

                        case 4: {
                            cout << "Funcionalidad para reservar habitación no implementada aún." << endl;
                            break;
                        }

                        case 6: {
                            cout << "Saliendo al menú de Usuario..." << endl;
                            break;
                        }

                        default: {
                            cout << "(!) Opción no válida." << endl;
                            break;
                        }
                    }
                } while (opcion2 != 6);
                break;
            }

            case 2: {
                cout << "falta clase administrador" << endl;
                break;
            }

            case 3: {
                cout << "Saliendo del programa..." << endl;
                break;
            }

            default: {
                cout << "(!) Opción no válida." << endl;
                break;
            }
        }
    } while (opcion1 != 3);

    return 0;
}
        
    }while(opcion1 != 3);
    
}
