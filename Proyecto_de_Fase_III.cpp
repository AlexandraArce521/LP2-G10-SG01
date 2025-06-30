#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

bool validarLetra(const string& nombre) {
    bool tieneLetra = false;
    for (char c : nombre) {
        if (isalpha(c)) {
            tieneLetra = true;
        } else if (!isspace(c)) {
            throw invalid_argument("El nombre solo debe contener letras y espacios.");
        }
    }
    if (!tieneLetra) {
        throw invalid_argument("El nombre debe contener al menos una letra.");
    }
    return true;
}

class InasistenciaInvalidaException : public exception {
private:
    string mensaje;
public:
    explicit InasistenciaInvalidaException(const string& m) : mensaje(m) {}
    const char* what() const noexcept override { return mensaje.c_str(); }
};

bool validarDni(const string& dni) {
    if (dni.length() != 8)
        throw invalid_argument("El DNI debe tener exactamente 8 dígitos.");
    for (char c : dni) {
        if (!isdigit(c))
            throw invalid_argument("El DNI solo debe contener números.");
    }
    return true;
}

class CelularInvalidoException : public exception {
private:
    string mensaje;
public:
    explicit CelularInvalidoException(const string& m) : mensaje(m) {}
    const char* what() const noexcept override { return mensaje.c_str(); }
};

//===============================================

template<typename T>
bool compararPorSueldo(const T* a, const T* b) {
    return *a < *b; // Usa operator< ya definido
}
// ========== Clase AFP y subclases ==========

class AFP {
protected:
    float porcentajeAporte, porcentajeSeguro, porcentajeComision;

public:
    AFP(float aporte, float seguro, float comision)
        : porcentajeAporte(aporte), porcentajeSeguro(seguro), porcentajeComision(comision) {}

    float calcularDescuento(float sueldoBruto) const {
        float aporte = sueldoBruto * (porcentajeAporte / 100);
        float seguro = sueldoBruto * (porcentajeSeguro / 100);
        float comision = sueldoBruto * (porcentajeComision / 100);
        
        return aporte + seguro + comision;
    }

    virtual string obtenerTipo() = 0;

    virtual ~AFP() = default;
};

class AFPIntegra : public AFP {
public:
    string obtenerTipo() override { return "AFP Integra"; }
    AFPIntegra() : AFP(10.0, 1.74, 1.55) {}
};

class AFPPrima : public AFP {
public:
    string obtenerTipo() override { return "AFP Prima"; }
    AFPPrima() : AFP(10.0, 1.74, 1.60) {}
};

class AFPProfuturo : public AFP {
public:
    string obtenerTipo() override { return "AFP Profuturo"; }
    AFPProfuturo() : AFP(10.0, 1.74, 1.69) {}
};

// ========== Clase Empresa ==========

class UsuarioTrabajador;

class Empresa {
private:
    string nombre, ruc, direccion;
    vector<UsuarioTrabajador*> trabajadores;

public:
    Empresa(string nom, string r, string dir) : nombre(nom), ruc(r), direccion(dir) {}

    void actualizarDatos(string nom, string r, string dir) {
        nombre = nom; ruc = r; direccion = dir;
        cout << "Datos de la empresa actualizados correctamente." << endl;
    }

    void mostrarDatos() {
        cout << "Nombre de la Empresa: " << nombre << endl;
        cout << "RUC: " << ruc << endl;
        cout << "Direccion: " << direccion << endl;
    }

    void agregarEmpleado(UsuarioTrabajador* emp) {
        trabajadores.push_back(emp);
    }

    UsuarioTrabajador* buscarPorDni(string& dni);

    string getNombre() { return nombre; }

    vector<UsuarioTrabajador*>& getTrabajadores() { return trabajadores; }
};

// ========== Clase Usuario ==========


class Usuario {
protected:
    string userId, contrasenia;
    bool sesionActiva;

public:
    Usuario(string id = "", string pass = "") : userId(id), contrasenia(pass), sesionActiva(false) {}

    // Método para iniciar sesión
    bool iniciarSesion(const string& id, const string& pass) {
        if (userId == id && contrasenia == pass) {
            sesionActiva = true;
            cout << "Sesión iniciada correctamente.\n";
            return true;
        } else {
            cout << "Credenciales incorrectas.\n";
            return false;
        }
    }

    // Registro de usuario
    void registrarUsuario(const string& id, const string& pass) {
        userId = id;
        contrasenia = pass;
        cout << "Usuario registrado correctamente.\n";
    }

    // Verificar si el usuario coincide por ID
    bool verificarUsuario(const string& id) const {
        return userId == id;
    }

    void cerrarSesion() {
        sesionActiva = false;
        cout << "Sesión cerrada.\n";
    }

    string getUserId() const { return userId; }
    string getContra(){return contrasenia;}
    bool estaEnSesion() const { return sesionActiva; }
    


    virtual ~Usuario() = default;
};

// ========== Clase UsuarioTrabajador (abstracta) ==========

class UsuarioTrabajador : public Usuario {
protected:
    string nombre, dni, celular;
    double sueldoBruto;
    int numHijos;
    AFP* afp;
    Empresa* empresa;
    static int asignacionFamiliar;
    int inasistencias;

public:
    UsuarioTrabajador(string nom, string d, string cel, double sueldo, int hijos, AFP* a, Empresa* emp, string id, string pass)
        : Usuario(id, pass), nombre(nom), dni(d), celular(cel), sueldoBruto(sueldo), numHijos(hijos), afp(a), empresa(emp), inasistencias(0) {}
    
    
    void setAFP(AFP* a) { afp = a; }
    void setSueldo(double sueldo) { sueldoBruto = sueldo; }
    void setNumHijos(int hijos) { numHijos = hijos; }
    void setInasistencias(int n) {inasistencias=n;}
    int getInasistencias(){return inasistencias;}
    string getName(){return nombre;}
    int getHijos(){return numHijos;}

    virtual double calcularSueldoNeto()  = 0;
    virtual string obtenerTipo()  = 0;
    string getAfp() {return afp->obtenerTipo(); }

    void actualizarDatos(string nom, string d, string cel) {
        nombre = nom; dni = d; celular = cel;
    }

    double calcularDescuento() const {
        return afp->calcularDescuento(sueldoBruto) ;
    }

    bool operator<(const UsuarioTrabajador& otro) const {
        return sueldoBruto < otro.sueldoBruto;
    }

    virtual void mostrarDatos() {
        cout << "Nombre: " << nombre << "\nDNI: " << dni
             << "\nCelular: " << celular << "\nSueldo Bruto: S/" << sueldoBruto<< endl;
        cout << "Numero de Hijos: " << numHijos << endl;
        cout << "AFP: "<<afp->obtenerTipo()<<endl; 
    }

    string getDni() const { return dni; }
    double getSueldo() const { return sueldoBruto; }
    string getCelular() {return celular;}
    bool operator<(const UsuarioTrabajador& otro) {
        return sueldoBruto < otro.sueldoBruto;
    }    

    virtual ~UsuarioTrabajador() {};
};

int UsuarioTrabajador::asignacionFamiliar=133;

// ========== Subclases: Gerente y Operario ==========

class Gerente : public UsuarioTrabajador {
    string area;

public:
    Gerente(string nom, string d, string cel, double sueldo, int hijos, AFP* a, Empresa* e, string id, string pass, string area = "")
        : UsuarioTrabajador(nom, d, cel, sueldo, hijos, a, e,id ,pass), area(area) {}

    double calcularSueldoNeto() override {
        double descuento = calcularDescuento();
        double asignacion = numHijos > 0 ? asignacionFamiliar : 0;
        return sueldoBruto - descuento + asignacion;
    }

    string obtenerTipo() override {
        return "Gerente";
    }

    void mostrarDatos() override {
        UsuarioTrabajador::mostrarDatos();
        cout << "Departamento: " << area << "\nTipo: Gerente\n";
    }

};

class Operario : public UsuarioTrabajador {
public:
    Operario(string nom, string d, string cel, double sueldo, int hijos, AFP* a, Empresa* e,string id, string pass)
        : UsuarioTrabajador(nom, d, cel, sueldo, hijos, a, e, id ,pass) {}

    double calcularSueldoNeto() override {
        return sueldoBruto - calcularDescuento() + (numHijos > 0 ? asignacionFamiliar : 0);
    }

    string obtenerTipo() override {
        return "Operario";
    }

    void mostrarDatos() override {
        UsuarioTrabajador::mostrarDatos();
        cout << "Tipo: Operario\n";
    }
};

// ========== Clase UsuarioAdministrador (con puntero a Empresa) ==========

// ========== Clase Boleta ==========
template <typename T>
class Boleta {
    T* empleado;
    float sueldoNeto;
    float descuentos;
    int inasistencias;
    vector <int> faltas;

public:
    Boleta(T* emp, int faltas) : empleado(emp), inasistencias(faltas) {
        descuentos = empleado->calcularDescuento();
        sueldoNeto = empleado->calcularSueldoNeto() - (empleado->getInasistencias()* 20);
    }

    string getNombre() const { return empleado->getName(); }
    string getDni() const { return empleado->getDni(); }
    string getTipo() const { return empleado->obtenerTipo(); }
    string getTipoAfp() const { return empleado->getAfp(); }
    double getSueldoBruto() const { return empleado->getSueldo(); }
    double getDescuentoAFP() const { return descuentos; }
    double getSueldoNeto() const { return sueldoNeto; }
    int getFaltas() const { return empleado->getInasistencias(); }
    int getHijos() const { return empleado->getHijos(); }
    string getAFP() const { return empleado->calcularDescuento() > 0 ? "Sí" : "No"; }

    void mostrar() {
        cout << "=== BOLETA DE PAGO ===\n";
        empleado->mostrarDatos();

        cout << "Inasistencias: " << empleado->getInasistencias()
             << "\nDescuentos por afp: S/" << descuentos<<endl;

        if (empleado->getHijos()>0) {
            cout<<"bono de asignacion familiar: 133$"<< endl;
        }
        cout<< "\nSueldo Neto: S/" << sueldoNeto << "\n"<<endl;
    }
};



// ========== Clase Nomina ==========

class Nomina {
    vector<Boleta<UsuarioTrabajador>> boletas;
    map<string, int> inasistencias;
    

public:
    void generarParaTodos( vector<UsuarioTrabajador*>& trabajadores) {
        boletas.clear();  // MUY IMPORTANTE para evitar duplicados y reiniciar
        for (auto& t : trabajadores) {
            Boleta<UsuarioTrabajador> b(t, t->getInasistencias());
            boletas.push_back(b);
        }
    }
    
    const vector<Boleta<UsuarioTrabajador>>& getBoletas() const {
        return boletas;
    }

    void registrarFaltas(string dni, int cantidad) {
        inasistencias[dni] = cantidad;
    }

    void mostrarNomina() {
    cout << "\n============================================= NÓMINA DE TRABAJADORES ===============================================\n";
    cout << left;
    cout.width(15); cout << "NOMBRE";
    cout.width(12); cout << "DNI";
    cout.width(10); cout << "TIPO";
    cout.width(15); cout << "AFP";
    cout.width(10); cout << "FALTAS";
    cout.width(15); cout << "SUELDO BRUTO";
    cout.width(10); cout << "HIJOS";
    cout.width(12); cout << "DESCUENTO";
    cout.width(14); cout << "ASIG.FAM.";
    cout.width(14); cout << "SUELDO NETO";
    cout << "\n-----------------------------------------------------------------------------------------------------------------\n";

    for (Boleta<UsuarioTrabajador>& b: boletas) {
        cout.width(15); cout << b.getNombre();
        cout.width(12); cout << b.getDni();
        cout.width(10); cout << b.getTipo();
        cout.width(15); cout << b.getTipoAfp();
        cout.width(10); cout << b.getFaltas();
        cout.width(15); cout << fixed << setprecision(2) << b.getSueldoBruto();
        cout.width(10); cout << b.getHijos();
        cout.width(12); cout << fixed << setprecision(2) << b.getDescuentoAFP();
        cout.width(14); cout << (b.getHijos() > 0 ? "133.00" : "0.00");
        cout.width(14); cout << fixed << setprecision(2) << b.getSueldoNeto();
        cout << "\n";
    }
    cout << "====================================================================================================================\n";
}
};


/////////////////////////////////////////////////////////////////////
//                   GESTOR ARCHIVOS                              ///
/////////////////////////////////////////////////////////////////////
class UsuarioAdministrador;
class GestorArchivos {
public:
    static void guardarTrabajadores(const map<string, UsuarioTrabajador*>& trabajadores);
    static void guardarAdministradores(const map<string, UsuarioAdministrador*>& admins);
    static void guardarNomina(const Nomina& nomina);

    static void cargarTrabajadores(Empresa* empresa, map<string, UsuarioTrabajador*>& trabajadores);
    static void cargarAdministradores(Empresa* empresa, map<string, UsuarioAdministrador*>& admins);
};


void GestorArchivos::guardarNomina(const Nomina& nomina) {
    ofstream file("nomina.txt");
    file << left;
    file << setw(15) << "NOMBRE" << setw(12) << "DNI" << setw(10) << "TIPO"
         << setw(15) << "AFP" << setw(10) << "FALTAS"
         << setw(15) << "SUELDO BRUTO" << setw(10) << "HIJOS"
         << setw(12) << "DESCUENTO" << setw(14) << "ASIG.FAM." << setw(14) << "SUELDO NETO" << "\n";
    file << string(120, '-') << "\n";

    for (const Boleta<UsuarioTrabajador>& b : nomina.getBoletas()) {
        file << setw(15) << b.getNombre()
             << setw(12) << b.getDni()
             << setw(10) << b.getTipo()
             << setw(15) << b.getTipoAfp()
             << setw(10) << b.getFaltas()
             << setw(15) << fixed << setprecision(2) << b.getSueldoBruto()
             << setw(10) << b.getHijos()
             << setw(12) << fixed << setprecision(2) << b.getDescuentoAFP()
             << setw(14) << (b.getHijos() > 0 ? "133.00" : "0.00")
             << setw(14) << b.getSueldoNeto()
             << "\n";
    }
    file.close();
}

class UsuarioAdministrador : public Usuario {
private:
    string nombre, dni;
    Empresa* empresa;
    UsuarioTrabajador* trabajador;

public:
    UsuarioAdministrador(string nom, string d, string id, string pass, Empresa* emp)
        : Usuario(id, pass), nombre(nom), dni(d), empresa(emp) {}

    void setDatos( string nom,  string d) {
        nombre = nom;
        dni = d;
        cout<<"cambios hechos..."<<endl;
    } 

    void actualizarDatosEmpleado(UsuarioTrabajador* emp) {
        string entradaSueldo;
        double sueldo;
    
        while (true) {
            cout << "Nuevo sueldo: ";
            cin >> entradaSueldo;
    
            try {
                if (entradaSueldo.empty()) {
                    throw invalid_argument("Debe ingresar un valor.");
                }
    
                bool puntoEncontrado = false;
                for (char c : entradaSueldo) {
                    if (c == '.') {
                        if (puntoEncontrado) {
                            throw invalid_argument("Formato inválido: hay más de un punto decimal.");
                        }
                        puntoEncontrado = true;
                    } else if (!isdigit(c)) {
                        throw invalid_argument("El sueldo solo debe contener números (y como máximo un punto decimal).");
                    }
                }
    
                sueldo = stod(entradaSueldo);
    
                if (sueldo <= 0) {
                    throw invalid_argument("El sueldo debe ser mayor a 0.");
                }
    
                break;
    
            } catch (const invalid_argument& e) {
                cout << "Error: " << e.what() << endl;
            } catch (...) {
                cout << "Error inesperado. Intente nuevamente.\n";
            }
        }
    
        emp->setSueldo(sueldo);
        cout << "\nDatos actualizados correctamente..." << endl;
    }

    void generarReporteGeneral(Nomina& nom)  {
        cout << "=== REPORTE GENERAL ===\n";
        nom.generarParaTodos(empresa->getTrabajadores());
        nom.mostrarNomina();
        GestorArchivos::guardarNomina(nom);
    }

    void actualizarDatosEmpresa() {
        string nuevoNombre, nuevoRuc, nuevaDir;
        cout << "Ingrese nuevo nombre de empresa: ";
        cin>> nuevoNombre;
        
        while (true) {
            cout << "Ingrese nuevo RUC: ";
            cin >> nuevoRuc;
    
            try {
                if (nuevoRuc.length() != 9) {
                    throw invalid_argument("El RUC debe tener exactamente 9 dígitos.");
                }
    
                for (char c : nuevoRuc) {
                    if (!isdigit(c)) {
                        throw invalid_argument("El RUC solo debe contener números.");
                    }
                }
                break; 
    
            } catch (const invalid_argument& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
        cout << "Ingrese nueva dirección: ";
        cin>>nuevaDir;

        empresa->actualizarDatos(nuevoNombre, nuevoRuc, nuevaDir);
    }

    void ReporteDni(UsuarioTrabajador* t){
        if (t) {
            Boleta<UsuarioTrabajador> b(t, t->getInasistencias());
            b.mostrar();
        }
        else{
            cout<<"no se encuentra al trabajador.."<<endl;
        }
    }

    void SueldoMes(UsuarioTrabajador* t){
        if (t) {
            Boleta<UsuarioTrabajador> b(t, t->getInasistencias());
            b.mostrar();
        }
        else{
            cout<<"no se encontro al empleado..."<<endl;
        }
    }


    void mostrarSueldosOrdenados() {
        const auto& trabajadores = empresa->getTrabajadores();
        if (trabajadores.empty()) {
            cout << "\nNo hay empleados registrados para mostrar sueldos.\n";
            return;
        }

        vector<UsuarioTrabajador*> copiaTrabajadores = trabajadores;
        sort(copiaTrabajadores.begin(), copiaTrabajadores.end(), compararPorSueldo<UsuarioTrabajador>);

        cout << "\n--- Sueldos de empleados (de mayor a menor) ---\n";
        for ( auto* emp : copiaTrabajadores) {
            emp->mostrarDatos();
            cout << "Sueldo Neto: S/" << emp->calcularSueldoNeto() << "\n--------------------\n";
        }
    }
    string getNombre(){return nombre;}
    string getDni(){return dni;}

};
void GestorArchivos::guardarNomina(const Nomina& nomina);

void GestorArchivos::guardarTrabajadores(const map<string, UsuarioTrabajador*>& trabajadores) {
    ofstream file("trabajadores.txt");
    for (const auto& par : trabajadores) {
        string id = par.first;
        UsuarioTrabajador* t = par.second;
        file << id << "|" << t->getContra() << "|" << t->getDni() << "|" << t->getName() << "|"<< t->getCelular()<< "|"
             << t->getSueldo() << "|" << t->getHijos() << "|" << t->getAfp() << "|" 
             << t->getInasistencias() << "|" << t->obtenerTipo() << "\n";
    }
    file.close();
}

void GestorArchivos::guardarAdministradores(const map<string, UsuarioAdministrador*>& admins) {
    ofstream file("administradores.txt");
    for (const auto& par : admins) {
        string id = par.first;
        UsuarioAdministrador* admin = par.second;
        file << id << "|" << admin->getContra() << "|" << admin->getNombre() <<"|" << admin->getDni() <<"\n";
    }
    file.close();
}

// ========== Implementación de búsqueda en Empresa ==========

UsuarioTrabajador* Empresa::buscarPorDni(string& dni) {
    for (auto t : trabajadores) {
        if (t->getDni() == dni)
            return t;
    }
    return nullptr;
}

UsuarioTrabajador* registrarTrabajador(Empresa* empresa, map<string, UsuarioTrabajador*>& usuariosTrabajadores, string id, string pass) {
    string nombre, dni, celular, afpTipo, entradaSueldo, entradaHijos;
    double sueldo;
    int hijos;

    while (true) {
        cout << "Nombre: ";
        getline(cin, nombre);
        try {
            validarLetra(nombre);
            break;
        } catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    while (true) {
        cout << "DNI: ";
        getline(cin, dni);
        try {
            validarDni(dni);
            break;
        } catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    
    while (true) {
        cout << "Celular: ";
        getline(cin, celular);
        try {
            if (celular.length() != 9) {
                throw CelularInvalidoException("El número de celular debe tener exactamente 9 dígitos.");
            }
            for (char c : celular) {
                if (!isdigit(c)) {
                    throw CelularInvalidoException("El número de celular solo debe contener dígitos.");
                }
            }
            break; 
        } catch (const CelularInvalidoException& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    while (true) {
        cout << "Sueldo Bruto: ";
        cin >> entradaSueldo;
        try {
            sueldo = stod(entradaSueldo);
            if (sueldo <= 0) {
                cout << "El sueldo debe ser mayor a 0.\n";
                continue;
            }
            break;
        } catch (...) {
            cout << "Entrada no válida. Ingrese un número válido para el sueldo.\n";
        }
    }

    while (true) {
        cout << "Nro de hijos: ";
        cin >> entradaHijos;
        try {
            hijos = stoi(entradaHijos);
            if (hijos < 0) {
                cout << "El número de hijos no puede ser negativo.\n";
                continue;
            }
            break;
        } catch (...) {
            cout << "Entrada no válida. Ingrese un número entero para hijos.\n";
        }
    }

    //  AFP
    while (true) {
        cout << "AFP (Integra, Prima, Profuturo): ";
        cin >> afpTipo;
        if (afpTipo == "Integra" || afpTipo == "Prima" || afpTipo == "Profuturo") break;
        cout << "AFP no válida. Ingrese: Integra, Prima o Profuturo.\n";
    }

    AFP* afp = nullptr;
    if (afpTipo == "Integra") afp = new AFPIntegra();
    else if (afpTipo == "Prima") afp = new AFPPrima();
    else if (afpTipo == "Profuturo") afp = new AFPProfuturo();

    int op;
    string entradaOp;
    while (true) {
        cout << "==TIPO DE TRABAJADOR==\n1. Operario\n2. Gerente\nOpcion: ";
        cin >> entradaOp;
        try {
            op = stoi(entradaOp);
            if (op == 1 || op == 2) break;
            else cout << "Opción fuera de rango.\n";
        } catch (...) {
            cout << "Entrada no válida. Ingrese 1 o 2.\n";
        }
    }

    if (op == 1) {
        Operario* nuevo = new Operario(nombre, dni, celular, sueldo, hijos, afp, empresa, id, pass);
        empresa->agregarEmpleado(nuevo);
        usuariosTrabajadores[id] = nuevo;
        GestorArchivos::guardarTrabajadores(usuariosTrabajadores);
        return nuevo;
    } else {
        string area;
        cout << "Departamento (ejem. Finanzas): ";
        getline(cin, area);

        Gerente* nuevo = new Gerente(nombre, dni, celular, sueldo, hijos, afp, empresa, id, pass, area);
        empresa->agregarEmpleado(nuevo);
        usuariosTrabajadores[id] = nuevo;
        GestorArchivos::guardarTrabajadores(usuariosTrabajadores);
        return nuevo;
    }
}

UsuarioAdministrador* registrarAdministrador(Empresa* empresa, map<string, UsuarioAdministrador*>& admins, string id, string pass) {
    string nombre, dni;
    cout << "Registro de administrador\n";
    
    cin.ignore();
    while (true) {
        cout << "Nombre: ";
        getline(cin, nombre);
        try {
            validarLetra(nombre);
            break;
        } catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    while (true) {
        cout << "DNI: ";
        getline(cin, dni);
        try {
            validarDni(dni);
            break;
        } catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    UsuarioAdministrador* admin = new UsuarioAdministrador(nombre, dni, id, pass, empresa);
    admins[id] = admin;
    GestorArchivos::guardarAdministradores(admins);

    return admin;
}


void GestorArchivos::cargarTrabajadores(Empresa* empresa, map<string, UsuarioTrabajador*>& trabajadores) {
    ifstream file("trabajadores.txt");
    if (!file.is_open()) return;
    string linea;
    while (getline(file, linea)) {
        stringstream ss(linea);
        string id, pass, dni, nombre,celular, afpTipo, tipo;
        double sueldo;
        int hijos, faltas;

        getline(ss, id, '|');
        getline(ss, pass, '|');
        getline(ss, dni, '|');
        getline(ss, nombre, '|');
        getline(ss, celular, '|');
        ss >> sueldo; ss.ignore();
        ss >> hijos; ss.ignore();
        getline(ss, afpTipo, '|');
        ss >> faltas; ss.ignore();
        getline(ss, tipo);
        
        //**
        while (true) {
            cout << "AFP (Integra, Prima, Profuturo): ";
            cin >> afpTipo;
            if (afpTipo == "Integra" || afpTipo == "Prima" || afpTipo == "Profuturo") break;
            cout << "AFP no válida. Ingrese: Integra, Prima o Profuturo.\n";
        }

        AFP* afp = nullptr;
        if (afpTipo == "AFP Integra") afp = new AFPIntegra();
        else if (afpTipo == "AFP Prima") afp = new AFPPrima();
        else if (afpTipo == "AFP Profuturo") afp = new AFPProfuturo();

        UsuarioTrabajador* t = nullptr;
        if (tipo == "Operario")
            t = new Operario(nombre, dni, celular, sueldo, hijos, afp, empresa, id, pass);
        else if (tipo == "Gerente")
            t = new Gerente(nombre, dni, celular, sueldo, hijos, afp, empresa, id, pass, "");

        if (t) {
            t->setInasistencias(faltas);
            trabajadores[id] = t;
            empresa->agregarEmpleado(t);
        }
    }
    file.close();
}

void GestorArchivos::cargarAdministradores(Empresa* empresa, map<string, UsuarioAdministrador*>& admins) {
    ifstream file("administradores.txt");
    if (!file.is_open()) return;
    string linea;
    while (getline(file, linea)) {
        stringstream ss(linea);
        string id, pass, nombre, dni;
        getline(ss, id, '|');
        getline(ss, pass,'|');
        getline(ss, nombre, '|');
        getline(ss, dni);

        UsuarioAdministrador* admin = new UsuarioAdministrador(nombre, dni, id, pass, empresa);
        admins[id] = admin;
    }
    file.close();
}

void menuTrabajador(UsuarioTrabajador* t, map<string, UsuarioTrabajador*>& usuariosTrabajadores) {
    if (t->estaEnSesion()) {
        int opcion;
        string entrada;

        do {
            cout << "\n1. Actualizar datos\n2. Consultar boleta\n3. Salir\nOpcion: ";
            cin >> entrada;

            try {
                opcion = stoi(entrada);
            } catch (...) {
                cout << "(!) Entrada no válida. Ingrese un número.\n";
                continue;
            }

            if (opcion == 1) {
                string nombre, dni, celular, afpTipo, entradaHijos;
                int hijos;

                while (true) {
                    cout << "Nuevo nombre: ";
                    getline(cin, nombre);
                    try {
                        validarLetra(nombre);
                        break;
                    } catch (const invalid_argument& e) {
                        cout << "Error: " << e.what() << endl;
                    }
                }

                while (true) {
                    cout << "Nuevo DNI: ";
                    getline(cin, dni);
                    try {
                        validarDni(dni);
                        break;
                    } catch (const invalid_argument& e) {
                        cout << "Error: " << e.what() << endl;
                    }
                }

                while (true) {
                    cout << "Celular: ";
                    getline(cin, celular);
                    try {
                        if (celular.length() != 9) {
                            throw CelularInvalidoException("El número de celular debe tener exactamente 9 dígitos.");
                        }
                        for (char c : celular) {
                            if (!isdigit(c)) {
                                throw CelularInvalidoException("El número de celular solo debe contener dígitos.");
                            }
                        }
                        break; 
                    } catch (const CelularInvalidoException& e) {
                        cout << "Error: " << e.what() << endl;
                    }
                }

                while (true) {
                    cout << "Nuevo nro de hijos: ";
                    cin >> entradaHijos;
                    try {
                        hijos = stoi(entradaHijos);
                        if (hijos < 0) {
                            cout << "La cantidad no puede ser negativa.\n";
                            continue;
                        }
                        break;
                    } catch (...) {
                        cout << "Entrada no válida. Ingrese un número entero.\n";
                    }
                }

                while (true) {
                    cout << "Nueva AFP (Integra, Prima, Profuturo): ";
                    cin >> afpTipo;
                    if (afpTipo == "Integra" || afpTipo == "Prima" || afpTipo == "Profuturo") break;
                    cout << "AFP no válida. Ingrese: Integra, Prima o Profuturo.\n";
                }

                AFP* afp = nullptr;
                if (afpTipo == "Integra") afp = new AFPIntegra();
                else if (afpTipo == "Prima") afp = new AFPPrima();
                else if (afpTipo == "Profuturo") afp = new AFPProfuturo();

                t->actualizarDatos(nombre, dni, celular);
                t->setNumHijos(hijos);
                t->setAFP(afp);

                GestorArchivos::guardarTrabajadores(usuariosTrabajadores);

                cout << "Datos actualizados exitosamente..." << endl;

            } else if (opcion == 2) {
                Boleta<UsuarioTrabajador> b(t, t->getInasistencias());
                b.mostrar();
            } else if (opcion != 3) {
                cout << "(!) Opción fuera de rango.\n";
            }

        } while (opcion != 3);
    }
}

void menuAdmin(UsuarioAdministrador* admin, Nomina& n, Empresa& empresa, map<string, UsuarioTrabajador*>& usuariosTrabajadores){
    if (admin->estaEnSesion()) {
        int op2;
        do {
            cout << "\n1. Actualizar datos de empleado\n2. Actualizar empresa\n3. Reportes\n4. Mostrar sueldos ordenados\n5. Salir\nOpcion: ";
            cin >> op2;
            if (op2 == 1) {
                string dni;
                cin.ignore();
                
                while (true) {
                    cout << "DNI del empleado a actualizar: ";
                    getline(cin, dni);
                    try {
                        validarDni(dni);
                        break;
                    } catch (const invalid_argument& e) {
                        cout << "Error: " << e.what() << endl;
                    }
                }
                
                UsuarioTrabajador* t = empresa.buscarPorDni(dni);
                if (t) admin->actualizarDatosEmpleado(t);
                else cout << "No se encontro empleado.\n";
                GestorArchivos::guardarTrabajadores(usuariosTrabajadores);

                cout<<"Datos actualizados exitosamente..."<<endl;
            } else if (op2 == 2) {
                admin->actualizarDatosEmpresa();

            } else if (op2 == 3) {
                cin.ignore();
                while (true){
                    int r;
                    cout << "\n1. Nomina completa\n2. Boleta por DNI\n3. Sueldo neto por mes (con faltas)\n4. Volver\nOpcion: ";
                    cin >> r;
                    if (r == 1) {
                        admin->generarReporteGeneral(n);
                    } else if (r == 2) {
                        string dni;
   
                        while (true) {
                            cout << "DNI: ";
                            getline(cin, dni);
                            try {
                                validarDni(dni);
                                break;
                            } catch (const invalid_argument& e) {
                                cout << "Error: " << e.what() << endl;
                            }
                        }
                        
                        UsuarioTrabajador* t = empresa.buscarPorDni(dni);
                        if (t){
                            admin->ReporteDni(t);
                        }
                        else{
                            cout<<"dni no encontrado..."<<endl;
                        }
                            
                    } else if (r == 3) {
                        cin.ignore();
                        string dni;
                        int faltas;
                        string entradaFaltas;

                        while (true) {
                            cout << "DNI: ";
                            getline(cin, dni);
                            try {
                                validarDni(dni);
                                break;
                            } catch (const invalid_argument& e) {
                                cout << "Error: " << e.what() << endl;
                            }
                        }
                        UsuarioTrabajador* t = empresa.buscarPorDni(dni);
                        if (t){

                        while (true) {
                            cout << "Inasistencias: ";
                            cin >> entradaFaltas;
                        
                            try {
                                if (entradaFaltas.empty()) {
                                    throw invalid_argument("Debe ingresar al menos un dígito.");
                                }
                        
                                for (char c : entradaFaltas) {
                                    if (!isdigit(c)) {
                                        throw invalid_argument("Las inasistencias solo deben contener números.");
                                    }
                                }
                        
                                faltas = stoi(entradaFaltas); 
                                break;
                        
                            } catch (const invalid_argument& e) {
                                cout << "Error: " << e.what() << endl;
                            } catch (...) {
                                cout << "Error inesperado. Intente nuevamente.\n";
                            }
                        }
                            
                            t->setInasistencias(faltas);
                            admin->SueldoMes(t);
                            GestorArchivos::guardarTrabajadores(usuariosTrabajadores);
                            cout<<"Datos actualizados exitosamente..."<<endl;
                        }
                        else{
                            cout<<"dni no encontrado..."<<endl;
                        }
                        
                    }else if (r==4){
                        break;
                    }
                }
            } else if (op2 == 4) {
                admin->mostrarSueldosOrdenados();
            }
        } while (op2 != 5);     
    }
    return;
}

int main() {
    Empresa empresa("OpenTech", "123456789", "Av. Lima 123");
    Nomina n;
    map<string, UsuarioTrabajador*> trabajadores;
    map<string, UsuarioAdministrador*> administradores;

    GestorArchivos::cargarTrabajadores(&empresa, trabajadores);
    GestorArchivos::cargarAdministradores(&empresa, administradores);


    vector <string> menu = {"\n____________________________________________________",
                                "1. Inciar sesion como Trabajador",
                                "2. Iniciar sesion como Administrador",
                                "3. Salir",
                                "____________________________________________________\n"
                                };
    int opcion;
    string respuesta;
    while (true) {

         try {
            for (auto& m: menu) {
                cout << m << endl;
            };
            cout << "Elegir una opción: ";
            cin >> respuesta;
            
            opcion = stoi(respuesta);

            switch(opcion) {
                case 1: {
                    cin.ignore();
                    string id, pass;
                    cout << "Usuario: "; 
                    getline(cin, id);
                    cout << "Contrasenia: ";
                    getline(cin, pass);

                    UsuarioTrabajador* t;
                    if (trabajadores.count(id)) {
                        t = trabajadores[id];
                    } else {
                        cout << "Usuario no registrado. Procediendo a registrar.\n";
                        cout << "Usuario: "; 
                        getline(cin, id);
                        cout << "Contrasenia: "; 
                        getline(cin, pass);
                        t = registrarTrabajador(&empresa, trabajadores, id, pass);
                    }
                        
                    if (t->iniciarSesion(id, pass)){
                        menuTrabajador(t,trabajadores);
                    }
                    else{
                        do{
                        cout << "Usuario: "; 
                        getline(cin, id);
                        cout << "Contrasenia: "; 
                        getline(cin, pass);
                        }while (t->iniciarSesion(id, pass)==false);
                        menuTrabajador(t,trabajadores);
                    }
                    break;
                } //fin de case 1
        
                case 2: {
                    cin.ignore();
                    string id, pass;
                    cout << "Usuario: "; 
                    cin >> id;
                    cout << "Contrasenia: "; 
                    cin >> pass;
        
                    UsuarioAdministrador* admin;
                    if (administradores.count(id)) {
                        admin = administradores[id];
                    } else {
                        cout << "Administrador no registrado. Procediendo a registrar.\n";
                        cout << "Usuario: "; cin >> id;
                        cout << "Contrasenia: "; cin >> pass;
                        admin = registrarAdministrador(&empresa, administradores,id, pass);
                    }
        
                    if (admin->iniciarSesion(id, pass)){
                        menuAdmin(admin,n,empresa,trabajadores);
                    }
                    else{
                        do{
                        cout << "Usuario: "; cin >> id;
                        cout << "Contrasenia: "; cin >> pass;
                        }while (admin->iniciarSesion(id, pass)==false);
                        menuAdmin(admin,n,empresa,trabajadores);
                    }
                    break;
                } //fin de case 2
                case 3: {
                    cout << "Saliendo del sistema...\n";
                    return 0;
                };// fin de case 3  
                    
                default: {
                    cout << "(!) Número fuera de rango.\n";
                }
            };// fin de switch case
        } catch (invalid_argument&) {
            cout << "(!) Entrada no válida. Ingrese un número.\n";
            
        } catch (out_of_range&) {
            cout << "(!) Número fuera de rango.\n";
        }  
    }
    return 0;
}

