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

float Empleado::asignacionFamiliar = 133;

// ===== DERIVADAS =====
class Gerente : public Empleado {
public:
    Gerente(string nom, string d, string cel, float sueldo, int h)
        : Empleado(nom, d, cel, sueldo, h) {}

    float calcularDescuento() const override {
        return sueldoBruto * 0.13;
    }

    float calcularSueldoNeto() const override {
        float desc = calcularDescuento();
        float bono;
        if (hijos > 0) { bono = asignacionFamiliar;} 
        else { bono = 0;}
        return sueldoBruto - desc + bono + 200;
    }

    string obtenerTipo() const override {
        return "Gerente";
    }
};

class Operario : public Empleado {
public:
    Operario(string nom, string d, string cel, float sueldo, int h)
        : Empleado(nom, d, cel, sueldo, h) {}

    float calcularDescuento() const override {
        return sueldoBruto * 0.13;
    }

    float calcularSueldoNeto() const override {
        float desc = calcularDescuento();
        float bono;
        if (hijos > 0) { bono = asignacionFamiliar;} 
        else { bono = 0;}
        return sueldoBruto - desc + bono;
    }

    string obtenerTipo() const override {
        return "Operario";
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

    while (true) {
        cout << "\n=== MENU PRINCIPAL ===\n";
        cout << "1. Administrador\n2. Trabajador\n3. Salir\nOpción: ";
        cin >> opcionPrincipal;

        switch (opcionPrincipal) {
            case 1: {
                int opAdmin;
                do {
                    cout << "\n--- MENU ADMINISTRADOR ---\n";
                    cout << "1. Registrar o Actualizar Empleado\n";
                    cout << "2. Actualizar datos de Empresa\n";
                    cout << "3. Reportes\n";
                    cout << "4. Salir\nOpción: ";
                    cin >> opAdmin;

                    switch (opAdmin) {
                        case 1: {
                            string nom, dni, cel, tipo;
                            float sueldo;
                            int hijos;
                            cout << "Nombre del Trabajador: "; cin >> nom;
                            cout << "DNI del Trabajador: "; cin >> dni;
                            cout << "Celular del Trabajador: "; cin >> cel;
                            cout << "Sueldo Bruto del Trabajador: "; cin >> sueldo;
                            cout << "Nro de hijos del Trabajador: "; cin >> hijos;
                            cout << "Tipo del Trabajador (gerente/operario): "; cin >> tipo;

                            Empleado* e = buscarEmpleado(empleados, dni);
                            if (e) {
                                e->actualizar(nom, dni, cel, sueldo, hijos);
                                cout << "Empleado actualizado.\n";
                            } else {
                                if (tipo == "gerente")
                                    empleados.push_back(new Gerente(nom, dni, cel, sueldo, hijos));
                                else
                                    empleados.push_back(new Operario(nom, dni, cel, sueldo, hijos));
                                cout << "Empleado registrado.\n";
                            }
                            break;
                        }
                        case 2: {
                            string nom, ruc, dir;
                            cout << "Nuevo nombre: "; cin >> nom;
                            cout << "Nuevo RUC: "; cin >> ruc;
                            cout << "Nueva dirección: "; cin >> dir;
                            empresa.actualizar(nom, ruc, dir);
                            cout << "Datos de empresa actualizados.\n";
                            break;
                        }
                        case 3: {
                            int sub;
                            cout << "\n1. Nomina completa\n2. Boleta por DNI\n3. Sueldo con faltas\nOpción: ";
                            cin >> sub;
                            switch (sub) {
                                case 1:
                                    if (empleados.empty()) {
                                        cout << "No hay empleados registrados.\n";
                                    } else {
                                        sort(empleados.begin(), empleados.end());
                                        for (Empleado* e : empleados) {
                                            e->mostrarDatos();
                                            cout << "Sueldo Neto: S/" << e->calcularSueldoNeto() << "\n---\n";
                                        }
                                    }
                                    break;
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
                                        cout << "Sueldo Neto ajustado: S/" << total << endl;
                                    } else {
                                        cout << "Empleado no encontrado.\n";
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                    }
                } while (opAdmin != 4);
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
                            cout << "Celular: "; cin >> cel;
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
