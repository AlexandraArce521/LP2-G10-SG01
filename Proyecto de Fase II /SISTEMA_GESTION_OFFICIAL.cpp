#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ===== CLASE BASE =====
class Empleado {
protected:
    string nombre, dni, celular;
    float sueldoBruto;
    int hijos;
    static float asignacionFamiliar;

public:
    Empleado(string nom, string d, string cel, float sueldo, int h)
        : nombre(nom), dni(d), celular(cel), sueldoBruto(sueldo), hijos(h) {}

    virtual float calcularDescuento() const = 0;
    virtual float calcularSueldoNeto() const = 0;
    virtual string obtenerTipo() const = 0;

    virtual void mostrarDatos() const {
        cout << "Nombre: " << nombre << "\nDNI: " << dni << "\nCelular: " << celular
             << "\nSueldo Bruto: S/" << sueldoBruto << "\nHijos: " << hijos << endl;
    }

    string getDNI() const { return dni; }
    string getNombre() const { return nombre; }
    float getSueldoBruto() const { return sueldoBruto; }
    int getHijos() const { return hijos; }

    void actualizar(string nom, string d, string cel, float sueldo, int h) {
        nombre = nom; dni = d; celular = cel;
        sueldoBruto = sueldo; hijos = h;
    }

    bool operator<(const Empleado& otro) const {
        return this->calcularSueldoNeto() < otro.calcularSueldoNeto();
    }

    virtual ~Empleado() {}
};

float Empleado::asignacionFamiliar = 100;


// ===== CLASE DERIVADA: GERENTE =====
class Gerente : public Empleado {
private:
    float bonoDesempeno;

public:
    Gerente(string nom, string d, string cel, float sueldo, int h, float bono)
        : Empleado(nom, d, cel, sueldo, h), bonoDesempeno(bono) {}

    float calcularDescuento() const override {
        return sueldoBruto * 0.10;
    }

    float calcularSueldoNeto() const override {
        float desc = calcularDescuento();
        float bono = (hijos > 0) ? asignacionFamiliar*hijos : 0;
        return sueldoBruto - desc + bono + bonoDesempeno;
    }

    string obtenerTipo() const override {
        return "Gerente";
    }

    void mostrarDatos() const override {
        Empleado::mostrarDatos();
        cout << "Bono por Desempeño: S/" << bonoDesempeno << endl;
    }
};


// ===== CLASE DERIVADA: OPERARIO =====
class Operario : public Empleado {
private:
    int horasExtras;

public:
    Operario(string nom, string d, string cel, float sueldo, int h, int horas)
        : Empleado(nom, d, cel, sueldo, h), horasExtras(horas) {}

    float calcularDescuento() const override {
        return sueldoBruto * 0.10;
    }

    float calcularSueldoNeto() const override {
        float desc = calcularDescuento();
        float bono = (hijos > 0) ? asignacionFamiliar*hijos : 0;
        float pagoHorasExtras = horasExtras * 10; // 10 soles por hora extra
        return sueldoBruto - desc + bono + pagoHorasExtras;
    }

    string obtenerTipo() const override {
        return "Operario";
    }

    void mostrarDatos() const override {
        Empleado::mostrarDatos();
        cout << "Horas Extras: " << horasExtras << endl;
    }
};

// ===== EMPRESA =====
class Empresa {
    string nombre, ruc, direccion;
public:
    Empresa(string n, string r, string d) : nombre(n), ruc(r), direccion(d) {}
    void actualizar(string n, string r, string d) { nombre = n; ruc = r; direccion = d; }

    void mostrar() const {
        cout << "\n--- DATOS DE LA EMPRESA ---\n";
        cout << "Nombre: " << nombre << "\nRUC: " << ruc << "\nDirección: " << direccion << endl;
    }
};

// ===== FUNCIONES =====
Empleado* buscarEmpleado(vector<Empleado*>& lista, const string& dni) {
    for (Empleado* e : lista) {
        if (e->getDNI() == dni) return e;
    }
    return nullptr;
}

// ===== MAIN =====
int main() {
    vector<Empleado*> empleados;
    Empresa empresa("MiEmpresa", "12345678901", "Av. Principal 123");
    int opcionPrincipal;
    string contrAdmin;

    while (true) {
        cout << "\n=== MENU PRINCIPAL ===\n";
        cout << "1. Administrador\n2. Trabajador\n3. Salir\nOpción: ";
        cin >> opcionPrincipal;

        switch (opcionPrincipal) {
            case 1: {
                cout << "\nPara Ingresar al Sistema Administrador.\nIngrese la contraseña\n";
                cout << "Pista: Sistema123\n";
                cout << "Ingrese la contraseña: "; cin >> contrAdmin;
                while (contrAdmin != "Sistema123"){
                    cout << "Contraseña incorrecta.\n";
                    cout << "Ingrese contraseña: "; cin >> contrAdmin;
                }
                int opAdmin;
                do {
                    cout << "\n--- MENU ADMINISTRADOR ---\n";
                    cout << "1. Registrar Empleado\n";
                    cout << "2. Actualizar datos de Empleado\n";                    
                    cout << "3. Actualizar datos de Empresa\n";
                    cout << "4. Reportes\n";
                    cout << "5. Salir\nOpción: ";
                    cin >> opAdmin;

                    switch (opAdmin) {
                        case 1: 
                        {
                            string nom, dni, cel, tipo;
                            float sueldo;
                            int hijos;
                            cout << "Nombre del Trabajador: "; cin >> nom;
                            cout << "DNI del Trabajador: "; cin >> dni;
                            while (dni.length() != 8 || !all_of(dni.begin(), dni.end(), ::isdigit)) {
                                cout << "DNI inválido. Debe tener exactamente 8 dígitos numéricos.\n";
                                cout << "DNI del Trabajador: "; cin >> dni;
                            }
                            cout << "Celular del Trabajador: "; cin >> cel;
                            while (cel.length() != 9 || !all_of(cel.begin(), cel.end(), ::isdigit)) {
                                cout << "Celular inválido. Debe tener exactamente 9 dígitos numéricos.\n";
                                cout << "Celular del Trabajador: "; cin >> cel;
                            }
                            cout << "Sueldo Bruto del Trabajador: "; cin >> sueldo;
                            cout << "Nro de hijos del Trabajador: "; cin >> hijos;
                            cout << "Tipo del Trabajador (gerente/operario): "; cin >> tipo;
                            while (tipo != "gerente" && tipo != "operario") {
                                cout << "Tipo inválido. Solo se permite 'gerente' o 'operario'.\n";
                                cout << "Tipo del Trabajador (gerente/operario): "; cin >> tipo;
                            }

                            Empleado* e = buscarEmpleado(empleados, dni);
                            if (e) {
                                cout << "Ya existe un empleado con ese DNI.\n";
                            } else {
                                if (tipo == "gerente") {
                                    float bono;
                                    cout << "Bono por desempeño: "; cin >> bono;
                                    empleados.push_back(new Gerente(nom, dni, cel, sueldo, hijos, bono));
                                } else {
                                    int horas;
                                    cout << "Horas extras: "; cin >> horas;
                                    empleados.push_back(new Operario(nom, dni, cel, sueldo, hijos, horas));
                                }
                                cout << "Empleado registrado.\n";
                            }
                            break;
                        }
                        case 2:
                        {
                            string dni;
                            cout << "DNI del empleado a modificar: ";
                            cin >> dni;
                            Empleado* emp = buscarEmpleado(empleados, dni);
                            if (!emp) {
                                cout << "Empleado no encontrado.\n";
                                break;
                            }
                    
                            string tipoNuevo;
                            float nuevoSueldo;
                            cout << "Nuevo tipo (gerente/operario): "; cin >> tipoNuevo;
                            while (tipoNuevo != "gerente" && tipoNuevo != "operario") {
                                cout << "Tipo inválido. Ingrese 'gerente' o 'operario': "; cin >> tipoNuevo;
                            }
                            cout << "Nuevo sueldo bruto: "; cin >> nuevoSueldo;
                            
                            cout <<"\nEMPLEADO A MODIFICAR\n";
                            string nom = "", cel = "";
                            int hijos = emp->getHijos();
                    
                            // Extraemos nombre y celular desde el objeto
                            emp->mostrarDatos();  // Para ver los datos antes de cambiar                            // Eliminamos el antiguo
                            auto it = find(empleados.begin(), empleados.end(), emp);
                            if (it != empleados.end()) {
                                delete *it;
                                empleados.erase(it);
                            }
                    
                            if (tipoNuevo == "gerente") {
                                float bono;
                                cout << "\nNuevo bono por desempeño: "; cin >> bono;
                                empleados.push_back(new Gerente(nom, dni, cel, nuevoSueldo, hijos, bono));
                            } else {
                                int horas;
                                cout << "\nHoras extras nuevas: "; cin >> horas;
                                empleados.push_back(new Operario(nom, dni, cel, nuevoSueldo, hijos, horas));
                            }
                            cout << "Empleado modificado correctamente.\n";
                            break;
                        }
                        
                        case 3: {
                            string nom, ruc, dir;
                            cout << "Nuevo nombre: "; cin >> nom;
                            cout << "Nuevo RUC: "; cin >> ruc;
                            while (ruc.length() != 11 || !all_of(ruc.begin(), ruc.end(), ::isdigit)) {
                                cout << "RUC inválido. Debe tener exactamente 11 dígitos numéricos.\n";
                                cout << "RUC del Trabajador: "; cin >> ruc;
                            }
                            cout << "Nueva dirección: "; cin >> dir;
                            empresa.actualizar(nom, ruc, dir);
                            cout << "Datos de empresa actualizados.\n";
                            break;
                        }
                        case 4: {
                            int sub;
                            cout << "\n1. Nomina completa\n2. Boleta por DNI\n3. Sueldo con faltas\nOpción: ";
                            cin >> sub;
                            cout << endl;
                            switch (sub) {
                                case 1: {
                                    if (empleados.empty()) {
                                        cout << "No hay empleados registrados.\n";
                                    } else {
                                        int orden;
                                        cout << "\n--- VER NOMINA ---\n";
                                        cout << "1. Orden alfabético por nombre\n";
                                        cout << "2. Orden por salario neto (mayor a menor)\n";
                                        cout << "Opción: ";
                                        cin >> orden;
                                
                                        if (orden == 1) {
                                            sort(empleados.begin(), empleados.end(), [](Empleado* a, Empleado* b) {
                                                return a->getNombre() < b->getNombre(); 
                                            });
                                        } else if (orden == 2) {
                                            sort(empleados.begin(), empleados.end(), [](Empleado* a, Empleado* b) {
                                                return a->calcularSueldoNeto() > b->calcularSueldoNeto();
                                            });
                                        } else {
                                            cout << "Opción inválida.\n";
                                            break;
                                        }
                                
                                        for (Empleado* e : empleados) {
                                            e->mostrarDatos();
                                            cout << "Sueldo Neto: S/" << e->calcularSueldoNeto() << "\n---\n";
                                        }
                                    }
                                    break;
                                }
                                case 2: {
                                    string dni;
                                    cout << "DNI: "; cin >> dni;
                                    Empleado* e = buscarEmpleado(empleados, dni);
                                    if (e) {
                                        empresa.mostrar();
                                        e->mostrarDatos();
                                        cout << "Descuento: S/" << e->calcularDescuento() << endl;
                                        cout << "Sueldo Neto: S/" << e->calcularSueldoNeto() << endl;
                                    } else {
                                        cout << "Empleado no encontrado.\n";
                                    }
                                    break;
                                }
                                case 3: {
                                    string dni;
                                    int faltas;
                                    cout << "DNI: "; cin >> dni;
                                    Empleado* e = buscarEmpleado(empleados, dni);
                                    if (e) {
                                        cout << "Inasistencias: "; cin >> faltas;
                                        float total = e->calcularSueldoNeto() - (faltas * 20);
                                        e->mostrarDatos();
                                        cout << "Inasistencias: "<< faltas<< endl;
                                        cout << "Sueldo Neto con"<< faltas<< "inasistencias: S/" << total << endl;
                                    } else {
                                        cout << "Empleado no encontrado.\n";
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                    }
                } while (opAdmin != 5);
                break;
            }

            case 2: {
                if (empleados.empty()) {
                    cout << "\nNo hay empleados registrados.\n";
                    cout << "Si cree que hay algún problema, comuníquese con su administrador.\n";
                    break;
                }

                string dni;
                cout << "Ingrese su DNI: "; cin >> dni;
                Empleado* emp = buscarEmpleado(empleados, dni);
                if (!emp) {
                    cout << "Empleado no encontrado.\n";
                    break;
                }

                int opTrabajador;
                do {
                    cout << "\n--- MENU TRABAJADOR ---\n";
                    cout << "1. Actualizar Datos\n2. Consultar Boleta\n3. Salir\nOpción: ";
                    cin >> opTrabajador;
                    switch (opTrabajador) {
                        case 1: {
                            string nom, d, cel;
                            float sueldo;
                            int h;
                            cout << "Nuevo nombre: "; cin >> nom;
                            cout << "Nuevo DNI: "; cin >> d;
                            while (d.length() != 8 || !all_of(d.begin(), d.end(), ::isdigit)) {
                                cout << "DNI inválido. Debe tener exactamente 8 dígitos numéricos.\n";
                                cout << "DNI del Trabajador: "; cin >> d;
                            }
                            cout << "Celular: "; cin >> cel;
                            while (cel.length() != 9 || !all_of(cel.begin(), cel.end(), ::isdigit)) {
                                cout << "Celular inválido. Debe tener exactamente 9 dígitos numéricos.\n";
                                cout << "Celular del Trabajador: "; cin >> cel;
                            }
                            cout << "Sueldo Bruto: "; cin >> sueldo;
                            cout << "Nro hijos: "; cin >> h;
                            emp->actualizar(nom, d, cel, sueldo, h);
                            cout << "Datos actualizados.\n";
                            break;
                        }
                        case 2:
                            emp->mostrarDatos();
                            cout << "Descuento AFP: S/" << emp->calcularDescuento() << endl;
                            cout << "Sueldo Neto: S/" << emp->calcularSueldoNeto() << endl;
                            break;
                    }
                } while (opTrabajador != 3);
                break;
            }

            case 3:
                cout << "Saliendo del sistema...\n";
                for (Empleado* e : empleados) delete e;
                return 0;
        }
    }
}
