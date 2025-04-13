#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

// Declaraciones anticipadas
class Administrador;
class Huesped;
class Habitacion;
class Reserva;
class Pago;

// ==================== CLASE HABITACION (PADRE) ====================
class Habitacion 
{
protected:
    string codigo;
    string tipo;
    double precio;
    bool disponible;
    
public:
    Habitacion(string codigo, string tipo, double precio)
        : codigo(codigo), tipo(tipo), precio(precio), disponible(true) {}
    
    string getCodigo() const { return codigo; }
    string getTipo() const { return tipo; }
    double getPrecio() const { return precio; }
    bool estaDisponible() const { return disponible; }
    
    virtual void MostrarInfo() const 
    {
        cout << "Código: " << codigo << endl;
        cout << "Tipo: " << tipo << endl;
        cout << "Precio: S/." << precio << endl;
        cout << "Disponibilidad: " << (disponible ? "Disponible" : "No disponible") << endl;
    }
    
    void Bloquear() { disponible = false; }
    void Desbloquear() { disponible = true; }
};

// ==================== CLASES HIJAS DE HABITACION ====================
class Simple : public Habitacion 
{
public:
    Simple(string codigo, double precio)
        : Habitacion(codigo, "Simple", precio) {}
};

class Doble : public Habitacion 
{
public:
    Doble(string codigo, double precio)
        : Habitacion(codigo, "Doble", precio) {}
};

class Matrimonial : public Habitacion 
{
public:
    Matrimonial(string codigo, double precio)
        : Habitacion(codigo, "Matrimonial", precio) {}
};

// ==================== CLASE RESERVA ====================
class Reserva
{
private:
    string codigo;
    string fechaInicio;
    string fechaFin;
    string estado; // "pendiente", "activa" o "cancelada"
    double costoTotal;
    Habitacion* habitacion;
    Huesped* huesped;
        
public:
    Reserva(string codigo, string fechaInicio, string fechaFin, Habitacion* habitacion, Huesped* huesped)
        : codigo(codigo), fechaInicio(fechaInicio), fechaFin(fechaFin), habitacion(habitacion), huesped(huesped) 
    {
        estado = "pendiente";
        costoTotal = 0;
    }
        
    double CalcularCosto()
    {
        costoTotal = habitacion->getPrecio();
        return costoTotal;
    }
    
    // Declaración; la definición se encuentra más abajo
    void MostrarReserva() const;
    
    void Cancelar() 
    {
        if (estado == "pendiente") 
        {
            estado = "cancelada";
            habitacion->Desbloquear();
        }
    }
    
    void Confirmar() 
    {
        if (estado == "pendiente") 
        {
            estado = "activa";
        }
    }
    
    string getCodigo() const { return codigo; }
    string getEstado() const { return estado; }
    double getCosto() const { return costoTotal; }
    Habitacion* getHabitacion() const { return habitacion; }
    Huesped* getHuesped() const { return huesped; }
};

// ==================== CLASE PAGO ====================
class Pago 
{
private:
    Reserva* reserva;
    double monto;
    string metodoPago;
    string fechaPago;
    
public:
    Pago(Reserva* reserva, double monto, string metodo, string fecha)
        : reserva(reserva), monto(monto), metodoPago(metodo), fechaPago(fecha) {}
    
    void RealizarPago() 
    {
        reserva->Confirmar();
        MostrarPago();
    }
    
    void MostrarPago() const {
        cout << "\n--- Detalle de Pago ---" << endl;
        cout << "Número de Reserva: " << reserva->getCodigo() << endl;
        cout << "Monto: S/." << monto << endl;
        cout << "Método de pago: " << metodoPago << endl;
        cout << "Fecha de pago: " << fechaPago << endl;
    }
};

// ==================== CLASE HUESPED ====================
class Huesped 
{
private:
    string nombre;
    string dni;
    string nacionalidad;
    vector<Reserva*> historialReservas;
    
public:
    Huesped(string nombre, string dni, string nacionalidad)
        : nombre(nombre), dni(dni), nacionalidad(nacionalidad) {}
        
    string getDni() const { return dni; }
    string getNombre() const { return nombre; }
        
    void ActualizarDatos(string nuevoNombre, string nuevoDni, string nuevaNacionalidad) 
    {
        nombre = nuevoNombre;
        dni = nuevoDni;
        nacionalidad = nuevaNacionalidad;
        cout << "Datos actualizados correctamente." << endl;
    }
        
    void BuscarHabitacion(const vector<Habitacion*>& habitaciones) const 
    {
        cout << "\nLista de habitaciones disponibles:\n";
        bool existen = false;
        for (Habitacion* hab : habitaciones) 
        {
            if (hab->estaDisponible()) 
            {
                hab->MostrarInfo();
                cout << endl;
                existen = true;
            }
        }
        if (!existen)
            cout << "No hay habitaciones disponibles actualmente." << endl;
    }
        
    void MostrarReservasPendientes() const {
        bool hayPendientes = false;
        cout << "\nReservas pendientes:" << endl;
        for (Reserva* r : historialReservas) {
            if (r->getEstado() == "pendiente") {
                r->MostrarReserva();
                hayPendientes = true;
            }
        }
        if (!hayPendientes)
            cout << "No tiene reservas pendientes." << endl;
    }
        
    void ReservarHabitacion(Habitacion* habitacion, string fechaInicio, string fechaFin, string codReserva) 
    {
        if (!habitacion->estaDisponible()) 
        {
            cout << "(!) La habitación no está disponible." << endl;
            return;
        }
        habitacion->Bloquear();
        Reserva* nueva = new Reserva(codReserva, fechaInicio, fechaFin, habitacion, this);
        nueva->CalcularCosto();
        historialReservas.push_back(nueva);
        cout << "Reserva realizada con éxito." << endl;
        nueva->MostrarReserva();
    }
        
    void CancelarReserva(string codReserva) 
    {
        MostrarReservasPendientes();
        cout << "\nIngrese el código de la reserva a cancelar: ";
        getline(cin, codReserva);
        
        for (size_t i = 0; i < historialReservas.size(); i++) 
        {
            if (historialReservas[i]->getCodigo() == codReserva) 
            {
                if (historialReservas[i]->getEstado() == "pendiente") 
                {
                    historialReservas[i]->Cancelar();
                    delete historialReservas[i];
                    historialReservas.erase(historialReservas.begin() + i);
                    cout << "Reserva cancelada correctamente." << endl;
                } 
                else 
                {
                    cout << "No se puede cancelar una reserva confirmada o ya cancelada." << endl;
                }
                return;
            }
        }
        cout << "(!) No se encontró una reserva con ese código." << endl;
    }
        
    void ConfirmarReserva(string codReserva) 
    {
        MostrarReservasPendientes();
        cout << "\nIngrese el código de la reserva a confirmar (realizar pago): ";
        getline(cin, codReserva);
        
        for (Reserva* r : historialReservas) 
        {
            if (r->getCodigo() == codReserva) 
            {
                if(r->getEstado() != "pendiente") {
                    cout << "La reserva ya fue confirmada o cancelada." << endl;
                    return;
                }
                double monto = r->getCosto();
                string fechaPago, metodo;
                cout << "Ingrese la fecha de pago: ";
                getline(cin, fechaPago);
                cout << "Ingrese el método de pago: ";
                getline(cin, metodo);
                Pago* p = new Pago(r, monto, metodo, fechaPago);
                p->RealizarPago();
                delete p;
                return;
            }
        }
        cout << "(!) No se encontró la reserva indicada." << endl;
    }
        
    void VerHistorialReservas() const 
    {
        if (historialReservas.empty()) 
        {
            cout << "No tiene reservas registradas." << endl;
            return;
        }
        cout << "\nHistorial de Reservas de " << nombre << ":" << endl;
        for (Reserva* r : historialReservas) {
            r->MostrarReserva();
        }
    }
};

// ==================== CLASE ADMINISTRADOR ====================
class Administrador 
{
private:
    string nombreAdmin;
    string codigoAdmin;  // Código de admin (8 dígitos)
    string contraseña;
    
public:
    Administrador(string nombre, string codigo, string clave)
        : nombreAdmin(nombre), codigoAdmin(codigo), contraseña(clave) {}
            
    void AgregarHabitacion(vector<Habitacion*>& habitaciones) 
    {
        int opcion;
        string codigo;
        double precio;
            
        cout << "Seleccione tipo de habitación:" << endl;
        cout << "1. Simple" << endl;
        cout << "2. Doble" << endl;
        cout << "3. Matrimonial" << endl;
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore();
            
        cout << "Ingrese el código de la habitación: ";
        getline(cin, codigo);
            
        cout << "Ingrese el precio: ";
        cin >> precio;
        cin.ignore();
            
        Habitacion* nueva = nullptr;
            
        if (opcion == 1)
            nueva = new Simple(codigo, precio);
        else if (opcion == 2)
            nueva = new Doble(codigo, precio);
        else if (opcion == 3)
            nueva = new Matrimonial(codigo, precio);
        else 
        {
            cout << "Opción inválida." << endl;
            return;
        }
            
        habitaciones.push_back(nueva);
        cout << "Habitación agregada correctamente." << endl;
    }
        
    void BloquearHabitacion(vector<Habitacion*>& habitaciones) 
    {
        if (habitaciones.empty()) {
            cout << "No existen habitaciones registradas." << endl;
            return;
        }
        cout << "\n-- Lista de habitaciones --" << endl;
        for (size_t i = 0; i < habitaciones.size(); i++) 
        {
            cout << i << ". ";
            habitaciones[i]->MostrarInfo();
            cout << endl;
        }
        int opcion;
        cout << "Seleccione habitación a bloquear: ";
        cin >> opcion;
        cin.ignore();
            
        if (opcion >= 0 && opcion < habitaciones.size()) 
        {
            habitaciones[opcion]->Bloquear();
            cout << "Habitación bloqueada." << endl;
        } 
        else 
        {
            cout << "Opción inválida." << endl;
        }
    }
        
    void DesbloquearHabitacion(vector<Habitacion*>& habitaciones) 
    {
        if (habitaciones.empty()) {
            cout << "No existen habitaciones registradas." << endl;
            return;
        }
        cout << "\n-- Lista de habitaciones --" << endl;
        for (size_t i = 0; i < habitaciones.size(); i++) 
        {
            cout << i << ". ";
            habitaciones[i]->MostrarInfo();
            cout << endl;
        }
        int opcion;
        cout << "Seleccione habitación a desbloquear: ";
        cin >> opcion;
        cin.ignore();
            
        if (opcion >= 0 && opcion < habitaciones.size()) 
        {
            habitaciones[opcion]->Desbloquear();
            cout << "Habitación desbloqueada." << endl;
        } 
        else 
        {
            cout << "Opción inválida." << endl;
        }
    }
        
    void VerReporteOcupacion(const vector<Habitacion*>& habitaciones) 
    {
        int total = habitaciones.size();
        int ocupadas = 0;
        for (Habitacion* h : habitaciones) 
        {
            if (!h->estaDisponible()) 
                ocupadas++;
        }
        cout << "\n--- Reporte de Ocupación ---" << endl;
        cout << "Total de habitaciones: " << total << endl;
        cout << "Ocupadas: " << ocupadas << endl;
        cout << "Disponibles: " << total - ocupadas << endl;
    }
        
    void VerReporteIngresos(const vector<Reserva*>& reservas) 
    {
        double total = 0;
        for (Reserva* r : reservas) 
            total += r->CalcularCosto();
        cout << "\n--- Reporte de Ingresos ---" << endl;
        cout << "Total: S/." << total << endl;
    }
    
    // Validación: se comparan el código y la contraseña
    bool validarAcceso(string codigo, string pass) 
    {
        return (codigo == codigoAdmin && pass == contraseña);
    }
};

// ==================== FUNCIONES AUXILIARES ====================
bool esDniValido(const string& dni) {
    if (dni.length() != 8)
        return false;
    for (char c : dni)
        if (!isdigit(c))
            return false;
    return true;
}

string generarCodigoReserva(int contador) {
    return "R" + to_string(contador);
}

// ==================== IMPLEMENTACIÓN DE RESERVA::MostrarReserva ====================

void Reserva::MostrarReserva() const 
{
    cout << "----------------------------------" << endl;
    cout << "Código de reserva: " << codigo << endl;
    cout << "Fecha de inicio: " << fechaInicio << endl;
    cout << "Fecha de fin: " << fechaFin << endl;
    cout << "Estado: " << estado << endl;
    cout << "Costo total: S/." << costoTotal << endl;
    cout << "Habitación: " << habitacion->getCodigo() << " (" << habitacion->getTipo() << ")" << endl;
    cout << "Huésped: " << huesped->getNombre() << endl;
    cout << "----------------------------------" << endl;
}

// ==================== MENÚ DEL SISTEMA ====================
int main() {
    vector<Habitacion*> habitaciones;
    vector<Reserva*> reservasGlobal;
    vector<Huesped*> huespedes;
    vector<Administrador*> administradores;
    
    // Se crea un administrador; se debe ingresar además un código (8 dígitos).
    administradores.push_back(new Administrador("Administrador", "12345678", "HOTEL123"));
    
    int reservaContador = 1;
    int opcionPrincipal;
    
    do {
        cout << "\n========== MENU PRINCIPAL ==========" << endl;
        cout << "1. Usuario (Huésped)" << endl;
        cout << "2. Administrador" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcionPrincipal;
        cin.ignore();
        
        if (opcionPrincipal == 1) {
            int opcionUsuario;
            do {
                cout << "\n======= MENÚ DE USUARIO (Huésped) =======" << endl;
                cout << "1. Registrar usuario" << endl;
                cout << "2. Actualizar datos de usuario" << endl;
                cout << "3. Buscar habitaciones disponibles" << endl;
                cout << "4. Reservar habitación" << endl;
                cout << "5. Cancelar reserva" << endl;
                cout << "6. Confirmar reserva (realizar pago)" << endl;
                cout << "7. Ver historial de reservas" << endl;
                cout << "8. Regresar al menú principal" << endl;
                cout << "Seleccione una opción: ";
                cin >> opcionUsuario;
                cin.ignore();
                
                if (opcionUsuario == 1) {
                    string nombre, dni, nacionalidad;
                    cout << "Ingrese su nombre: ";
                    getline(cin, nombre);
                    cout << "Ingrese su DNI (8 dígitos): ";
                    getline(cin, dni);
                    if (!esDniValido(dni)) {
                        cout << "(!) DNI inválido. Debe contener 8 dígitos." << endl;
                        continue;
                    }
                    cout << "Ingrese su nacionalidad: ";
                    getline(cin, nacionalidad);
                    
                    huespedes.push_back(new Huesped(nombre, dni, nacionalidad));
                    cout << "Usuario registrado con éxito." << endl;
                }
                else if (opcionUsuario == 2) {
                    string dni;
                    cout << "Ingrese su DNI: ";
                    getline(cin, dni);
                    bool encontrado = false;
                    for (Huesped* h : huespedes) {
                        if (h->getDni() == dni) {
                            encontrado = true;
                            string nuevoNombre, nuevoDni, nuevaNacionalidad;
                            cout << "Ingrese el nuevo nombre: ";
                            getline(cin, nuevoNombre);
                            cout << "Ingrese el nuevo DNI (8 dígitos): ";
                            getline(cin, nuevoDni);
                            if (!esDniValido(nuevoDni)) {
                                cout << "(!) DNI inválido." << endl;
                                break;
                            }
                            cout << "Ingrese la nueva nacionalidad: ";
                            getline(cin, nuevaNacionalidad);
                            h->ActualizarDatos(nuevoNombre, nuevoDni, nuevaNacionalidad);
                            break;
                        }
                    }
                    if (!encontrado)
                        cout << "No se encontró un usuario con ese DNI." << endl;
                }
                else if (opcionUsuario == 3) {
                    if (habitaciones.empty()) {
                        cout << "No hay habitaciones registradas en el hotel." << endl;
                    } else {
                        cout << "\nHabitaciones disponibles:" << endl;
                        if (!huespedes.empty())
                            huespedes[0]->BuscarHabitacion(habitaciones);
                        else
                            cout << "Primero debe registrarse como usuario." << endl;
                    }
                }
                else if (opcionUsuario == 4) {
                    if (habitaciones.empty()) {
                        cout << "No hay habitaciones registradas para reservar." << endl;
                        continue;
                    }
                    if (huespedes.empty()) {
                        cout << "Primero debe registrarse como usuario." << endl;
                        continue;
                    }
                    bool hayDisponibles = false;
                    for (Habitacion* hab : habitaciones)
                        if (hab->estaDisponible()) { hayDisponibles = true; break; }
                    if (!hayDisponibles) {
                        cout << "No hay habitaciones disponibles en este momento." << endl;
                        continue;
                    }
                    
                    string dni;
                    cout << "Ingrese su DNI para identificar su cuenta: ";
                    getline(cin, dni);
                    Huesped* usuarioActual = nullptr;
                    for (Huesped* h : huespedes) {
                        if (h->getDni() == dni) {
                            usuarioActual = h;
                            break;
                        }
                    }
                    if (!usuarioActual) {
                        cout << "No se encontró usuario con ese DNI. Regístrese primero." << endl;
                        continue;
                    }
                    
                    cout << "\nHabitaciones disponibles:" << endl;
                    for (size_t i = 0; i < habitaciones.size(); i++) {
                        if (habitaciones[i]->estaDisponible()) {
                            cout << i << ". ";
                            habitaciones[i]->MostrarInfo();
                            cout << endl;
                        }
                    }
                    int indice;
                    cout << "Seleccione el índice de la habitación que desea reservar: ";
                    cin >> indice;
                    cin.ignore();
                    if (indice < 0 || indice >= habitaciones.size() || !habitaciones[indice]->estaDisponible()) {
                        cout << "Índice inválido o habitación no disponible." << endl;
                        continue;
                    }
                    
                    string fechaInicio, fechaFin;
                    cout << "Ingrese la fecha de inicio (formato dd/mm/aaaa): ";
                    getline(cin, fechaInicio);
                    cout << "Ingrese la fecha de fin (formato dd/mm/aaaa): ";
                    getline(cin, fechaFin);
                    
                    string codReserva = generarCodigoReserva(reservaContador++);
                    usuarioActual->ReservarHabitacion(habitaciones[indice], fechaInicio, fechaFin, codReserva);
                    reservasGlobal.push_back(nullptr); // Opcional: almacenar la referencia
                }
                else if (opcionUsuario == 5) {
                    if (huespedes.empty()) {
                        cout << "No hay usuarios registrados." << endl;
                        continue;
                    }
                    string dni;
                    cout << "Ingrese su DNI: ";
                    getline(cin, dni);
                    Huesped* usuarioActual = nullptr;
                    for (Huesped* h : huespedes) {
                        if (h->getDni() == dni) {
                            usuarioActual = h;
                            break;
                        }
                    }
                    if (!usuarioActual) {
                        cout << "No se encontró usuario con ese DNI." << endl;
                        continue;
                    }
                    usuarioActual->CancelarReserva(""); // La función mostrará sus reservas pendientes y pedirá el código
                }
                else if (opcionUsuario == 6) {
                    if (huespedes.empty()) {
                        cout << "No hay usuarios registrados." << endl;
                        continue;
                    }
                    string dni;
                    cout << "Ingrese su DNI: ";
                    getline(cin, dni);
                    Huesped* usuarioActual = nullptr;
                    for (Huesped* h : huespedes) {
                        if (h->getDni() == dni) {
                            usuarioActual = h;
                            break;
                        }
                    }
                    if (!usuarioActual) {
                        cout << "No se encontró usuario con ese DNI." << endl;
                        continue;
                    }
                    usuarioActual->ConfirmarReserva(""); // La función mostrará sus reservas pendientes y pedirá el código y datos de pago
                }
                else if (opcionUsuario == 7) {
                    if (huespedes.empty()) {
                        cout << "No hay usuarios registrados." << endl;
                        continue;
                    }
                    string dni;
                    cout << "Ingrese su DNI: ";
                    getline(cin, dni);
                    Huesped* usuarioActual = nullptr;
                    for (Huesped* h : huespedes) {
                        if (h->getDni() == dni) {
                            usuarioActual = h;
                            break;
                        }
                    }
                    if (!usuarioActual)
                        cout << "No se encontró usuario con ese DNI." << endl;
                    else
                        usuarioActual->VerHistorialReservas();
                }
                else if (opcionUsuario == 8) {
                    cout << "Regresando al menú principal..." << endl;
                }
                else {
                    cout << "Opción inválida. Intente de nuevo." << endl;
                }
                
            } while (opcionUsuario != 8);
        }
        else if (opcionPrincipal == 2) {
            // LOGIN DE ADMINISTRADOR: se pide nombre, código (8 dígitos) y contraseña.
            string nombreAdmin, codigoAdmin, pass;
            cout << "Ingrese su nombre de administrador: ";
            getline(cin, nombreAdmin);
            cout << "Ingrese su código de administrador (8 dígitos): ";
            getline(cin, codigoAdmin);
            if (!esDniValido(codigoAdmin)) {
                cout << "Código inválido. Debe tener 8 dígitos." << endl;
                continue;
            }
            cout << "La contraseña es HOTEL123" << endl;
            cout << "Ingrese la contraseña: ";
            getline(cin, pass);
            bool acceso = false;
            Administrador* adminActual = nullptr;
            for (Administrador* a : administradores) {
                if (a->validarAcceso(codigoAdmin, pass)) {
                    acceso = true;
                    adminActual = a;
                    break;
                }
            }
            if (!acceso) {
                cout << "Credenciales incorrectas." << endl;
                continue;
            }
            
            int opcionAdmin;
            do {
                cout << "\n======= MENÚ ADMINISTRADOR =======" << endl;
                cout << "1. Agregar habitación" << endl;
                cout << "2. Bloquear habitación" << endl;
                cout << "3. Desbloquear habitación" << endl;
                cout << "4. Ver reporte de ocupación" << endl;
                cout << "5. Ver reporte de ingresos" << endl;
                cout << "6. Regresar al menú principal" << endl;
                cout << "Seleccione una opción: ";
                cin >> opcionAdmin;
                cin.ignore();
                
                if (opcionAdmin == 1) {
                    adminActual->AgregarHabitacion(habitaciones);
                }
                else if (opcionAdmin == 2) {
                    adminActual->BloquearHabitacion(habitaciones);
                }
                else if (opcionAdmin == 3) {
                    adminActual->DesbloquearHabitacion(habitaciones);
                }
                else if (opcionAdmin == 4) {
                    adminActual->VerReporteOcupacion(habitaciones);
                }
                else if (opcionAdmin == 5) {
                    adminActual->VerReporteIngresos(reservasGlobal);
                }
                else if (opcionAdmin == 6) {
                    cout << "Regresando al menú principal..." << endl;
                }
                else {
                    cout << "Opción inválida." << endl;
                }
                
            } while (opcionAdmin != 6);
        }
        else if (opcionPrincipal == 3) {
            cout << "Saliendo del sistema. ¡Hasta pronto!" << endl;
        }
        else {
            cout << "Opción inválida. Intente nuevamente." << endl;
        }
        
    } while (opcionPrincipal != 3);
    
    return 0;
}
