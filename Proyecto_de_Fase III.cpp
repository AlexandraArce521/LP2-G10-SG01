#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

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

// ========== Clase Empresa (con punteros a trabajadores) ==========

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
    void iniciarSesion(const string& id, const string& pass) {
        if (userId == id && contrasenia == pass) {
            sesionActiva = true;
            cout << "Sesión iniciada correctamente.\n";
        } else {
            cout << "Credenciales incorrectas.\n";
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
    bool estaEnSesion() const { return sesionActiva; }
    


    virtual ~Usuario() = default;
};

// ========== Clase UsuarioTrabajador (abstracta) ==========

class UsuarioTrabajador : public Usuario {
protected:
    string nombre, celular;
    string dni;
    double sueldoBruto;
    int numHijos;
    AFP* afp;
    Empresa* empresa;
    static int asignacionFamiliar;

public:
    UsuarioTrabajador(string nom, string d, string cel, double sueldo, int hijos, AFP* a, Empresa* emp, string id, string pass)
        : Usuario(id, pass), nombre(nom), dni(d), celular(cel), sueldoBruto(sueldo), numHijos(hijos), afp(a), empresa(emp) {}
    
    
    void setAFP(AFP* a) { afp = a; }
    void setSueldo(double sueldo) { sueldoBruto = sueldo; }
    void setNumHijos(int hijos) { numHijos = hijos; }
    int getHijos(){return numHijos;}

    virtual double calcularSueldoNeto()  = 0;
    virtual string obtenerTipo()  = 0;

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
        cout << "area: " << area << "\nTipo: Gerente\n";
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

class Boleta {
    UsuarioTrabajador* empleado;
    float sueldoNeto;
    float descuentos;
    int inasistencias;
    vector <int> faltas;

public:
    Boleta(UsuarioTrabajador* emp, int faltas) : empleado(emp), inasistencias(faltas) {
        descuentos = empleado->calcularDescuento();
        sueldoNeto = empleado->calcularSueldoNeto() - (faltas * 20);
    }

    void mostrar() {
        cout << "=== BOLETA DE PAGO ===\n";
        empleado->mostrarDatos();

        cout << "Inasistencias: " << inasistencias
             << "\nDescuentos por afp: S/" << descuentos<<endl;

        if (empleado->getHijos()>0) {
            cout<<"bono de asignacion familiar: 133$"<< endl;
        }
        cout<< "\nSueldo Neto: S/" << sueldoNeto << "\n"<<endl;
    }
};



// ========== Clase Nomina ==========

class Nomina {
    vector<Boleta> boletas;
    map<string, int> inasistencias;
    

public:
    void generarParaTodos( vector<UsuarioTrabajador*>& trabajadores) {
        int n;
        n=trabajadores.size();
        string dni;
        int faltas;
        for (int  i = 0; i <n; ++i) {
            dni=trabajadores[i]->getDni();
            faltas=inasistencias[dni];
            Boleta b(trabajadores[i], faltas);
            boletas.push_back(b);
        }
    }
    
    void registrarFaltas(string dni, int cantidad) {
        inasistencias[dni] = cantidad;
    }

    void mostrarNomina() {
        for ( Boleta& b : boletas) {
            b.mostrar();
            cout << "--------------------\n";
        }
    }
};

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
        double sueldo;
        cout << "Nuevo sueldo: "; cin >> sueldo;
        emp->setSueldo(sueldo);
        cout<<"\nDatos actualizados correctamente..."<<endl;
    }

    void generarReporteGeneral(Nomina nom)  {
        cout << "=== REPORTE GENERAL ===\n";
        nom.generarParaTodos(empresa->getTrabajadores());
        nom.mostrarNomina();
        
    }

    void actualizarDatosEmpresa() {
        string nuevoNombre, nuevoRuc, nuevaDir;
        cout << "Ingrese nuevo nombre de empresa: ";
        cin>> nuevoNombre;
        cout << "Ingrese nuevo RUC: ";
        cin>>nuevoRuc;
        cout << "Ingrese nueva dirección: ";
        cin>>nuevaDir;

        empresa->actualizarDatos(nuevoNombre, nuevoRuc, nuevaDir);
    }

    void ReporteDni(UsuarioTrabajador* t){
        if (t) {
            Boleta b(t, 0);
            b.mostrar();
        }
        else{
            cout<<"no se encuentra al trabajador.."<<endl;
        }
    }

    void SueldoMes(UsuarioTrabajador* t, int faltas){
        if (t) {
            Boleta b(t, faltas);
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
        sort(copiaTrabajadores.begin(), copiaTrabajadores.end(),
             [](const UsuarioTrabajador* a, const UsuarioTrabajador* b) {
                 return *a < *b;
             });

        cout << "\n--- Sueldos de empleados (de mayor a menor) ---\n";
        for ( auto* emp : copiaTrabajadores) {
            emp->mostrarDatos();
            cout << "Sueldo Neto: S/" << emp->calcularSueldoNeto() << "\n--------------------\n";
        }
    }

};

// ========== Implementación de búsqueda en Empresa ==========

UsuarioTrabajador* Empresa::buscarPorDni(string& dni) {
    for (auto t : trabajadores) {
        if (t->getDni() == dni)
            return t;
    }
    return nullptr;
}

UsuarioTrabajador* registrarTrabajador(Empresa* empresa, map<string, UsuarioTrabajador*>& usuariosTrabajadores, string id, string pass) {
    string nombre, dni, celular, afpTipo;
    double sueldo;
    int hijos;

    cout << "Nombre: "; cin >> nombre;
    cout << "DNI: "; cin >> dni;
    cout << "Celular: "; cin >> celular;
    do{
    cout << "Sueldo Bruto: "; cin >> sueldo;
    }while (sueldo<0);

    do{
    cout << "Nro de hijos: "; cin >> hijos;
    }while (hijos<0);

    cout << "AFP (Integra, Prima, Profuturo): "; cin >> afpTipo;

    AFP* afp = nullptr;
    if (afpTipo == "Integra") afp = new AFPIntegra();
    else if (afpTipo == "Prima") afp = new AFPPrima();
    else if (afpTipo == "Profuturo") afp = new AFPProfuturo();


    cout <<"==TIPO DE TRABAJADOR=="<<endl;
    cout <<"1. Operario"<<endl;
    cout <<"2. Gerente"<<endl;
    cout<<"opcion: ";
    int op;
    cin>>op;

    if (op==1){
        Operario* nuevo = new Operario(nombre, dni, celular, sueldo, hijos, afp, empresa, id, pass);
        empresa->agregarEmpleado(nuevo);
        usuariosTrabajadores[id] = nuevo;
        return nuevo;
    }
    else if (op==2){
        cout<<"area: ";
        string ar;
        cin>>ar;
        Gerente* nuevo = new Gerente(nombre, dni, celular, sueldo, hijos, afp, empresa, id, pass, ar);
        empresa->agregarEmpleado(nuevo);
        usuariosTrabajadores[id] = nuevo;
        return nuevo;
    }

    return nullptr;
}

UsuarioAdministrador* registrarAdministrador(Empresa* empresa, map<string, UsuarioAdministrador*>& admins) {
    string nombre, dni, id, pass;
    cout << "Registro de administrador\n";
    cout << "Nombre: "; cin >> nombre;
    cout << "DNI: "; cin >> dni;
    cout << "Usuario: "; cin >> id;
    cout << "Contrasenia: "; cin >> pass;

    UsuarioAdministrador* admin = new UsuarioAdministrador(nombre, dni, id, pass, empresa);
    admins[id] = admin;
    return admin;
}

int main() {
    Empresa empresa("OpenTech", "123456789", "Av. Lima 123");
    Nomina n;
    map<string, UsuarioTrabajador*> trabajadores;
    map<string, UsuarioAdministrador*> administradores;
    
    vector <string> menu = {"\n____________________________________________________",
                                "1. Inciar sesion como Trabajador",
                                "2. Iniciar sesion como Administrador",
                                "3. Salir",
                                "____________________________________________________\n"
                                };
                                
    int opcion;
    
    while (true) {
        
        try {
            for (auto& m: menu) {
                cout << m << endl;
            };
            
            string respuesta;
            
            cout << "Elegir una opción: ";
            cin >> respuesta;
            
            opcion = stoi(respuesta);
            
            switch (opcion) {
            case 1:{
                string id, pass;
                cout << "Usuario: "; cin >> id;
                cout << "Contrasenia: "; cin >> pass;
    
                UsuarioTrabajador* t;
                if (trabajadores.count(id)) {
                    t = trabajadores[id];
                } else {
                    cout << "Usuario no registrado. Procediendo a registrar.\n";
                    cout << "Usuario: "; cin >> id;
                    cout << "Contrasenia: "; cin >> pass;
                    t = registrarTrabajador(&empresa, trabajadores, id, pass);
                }
                    
    
                t->iniciarSesion(id, pass);
                if (t->estaEnSesion()) {
                    int opcion;
                    do {
                        cout << "\n1. Actualizar datos\n2. Consultar boleta\n3. Salir\nOpcion: ";
                        cin >> opcion;
                        if (opcion == 1) {
                            string nombre, dni, celular, afpTipo;
                            double sueldo; int hijos;
                            cout << "Nuevo nombre: "; cin >> nombre;
                            cout << "Nuevo DNI: "; cin >> dni;
                            cout << "Nuevo celular: "; cin >> celular;
                            do{
                            cout << "Nuevo sueldo: "; cin >> sueldo;
                            } while (sueldo<0);
    
                            do{
                            cout << "Nuevo nro de hijos: "; cin >> hijos;
                            } while (hijos<0);
                            cout << "Nueva AFP (Integra, Prima, Profuturo): "; cin >> afpTipo;
    
                            AFP* afp = nullptr;
                            if (afpTipo == "Integra") afp = new AFPIntegra();
                            else if (afpTipo == "Prima") afp = new AFPPrima();
                            else if (afpTipo == "Profuturo") afp = new AFPProfuturo();
    
                            t->actualizarDatos(nombre, dni, celular);
                            t->setSueldo(sueldo);
                            t->setNumHijos(hijos);
                            t->setAFP(afp);
                        } else if (opcion == 2) {
                            Boleta b(t, 0);
                            b.mostrar();
                        }
                    } while (opcion != 3);
                }
                
                break;
            };
            case 2: {
                string id, pass;
                cout << "Usuario: "; cin >> id;
                cout << "Contrasenia: "; cin >> pass;
    
                UsuarioAdministrador* admin;
                if (administradores.count(id)) {
                    admin = administradores[id];
                } else {
                    cout << "Administrador no registrado. Procediendo a registrar.\n";
                    admin = registrarAdministrador(&empresa, administradores);
                }
    
                admin->iniciarSesion(id, pass);
                if (admin->estaEnSesion()) {
                    int op2;
                    do {
                        cout << "\n1. Actualizar datos de empleado\n2. Actualizar empresa\n3. Reportes\n4. Mostrar sueldos ordenados\n5. Salir\nOpcion: ";
                        cin >> op2;
                        if (op2 == 1) {
                            string dni;
                            cout << "DNI del empleado a actualizar: ";
                            cin >> dni;
                            UsuarioTrabajador* t = empresa.buscarPorDni(dni);
                            if (t) admin->actualizarDatosEmpleado(t);
                            else cout << "No se encontro empleado.\n";
                        } else if (op2 == 2) {
                            admin->actualizarDatosEmpresa();
                        } else if (op2 == 3) {
                            while (true){
                            int r;
                            cout << "\n1. Nomina completa\n2. Boleta por DNI\n3. Sueldo neto por mes (con faltas)\n4. Volver\nOpcion: ";
                            cin >> r;
                            if (r == 1) {
                                admin->generarReporteGeneral(n);
                            } else if (r == 2) {
                                string dni;
                                cout << "DNI: "; cin >> dni;
                                UsuarioTrabajador* t = empresa.buscarPorDni(dni);
                                if (t){
                                admin->ReporteDni(t);
                                }
                                else{
                                    cout<<"dni no encontrado..."<<endl;
                                }
                                
                            } else if (r == 3) {
                                string dni;
                                int faltas;
                                cout << "DNI: "; cin >> dni;
                                UsuarioTrabajador* t = empresa.buscarPorDni(dni);
                                if (t){
    
                                cout << "Inasistencias: "; cin >> faltas;
                                n.registrarFaltas(dni, faltas);
                                admin->SueldoMes(t,faltas);}
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
                break;
            };//fin del case 2 
            case 3: {
                cout << "Saliendo del sistema...\n";
                return 0;
            };// fin de case 3  
            
            default: {
                cout << "Opcion no valida\n";
            }
            }; // fin del switch case
            
        } catch (invalid_argument&) {
            cout << "(!) Entrada no válida. Ingrese un número.\n";
        } catch (out_of_range&) {
            cout << "(!) Número fuera de rango.\n";
        }    
    }
    return 0;
}
