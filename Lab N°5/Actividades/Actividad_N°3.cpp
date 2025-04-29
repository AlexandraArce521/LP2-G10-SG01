#include <iostream>
using namespace std;

class Fecha {
private:
    int dia, mes, anio;

public:
    Fecha(int d, int m, int a) : dia(d), mes(m), anio(a) {}

    void mostrarFecha() {
        cout << dia << "/" << mes << "/" << anio << endl;
    }
};

class Contrato {
private:
    string codigo;
    string descripcion;
    Fecha fechaInicio;

public:
    Contrato(string c, string d, Fecha f) : codigo(c), descripcion(d), fechaInicio(f) {}

    void mostrarContrato() {
        cout << "Contrato: " << codigo << ", " << descripcion << ", Fecha inicio: ";
        fechaInicio.mostrarFecha();
    }
};

class Empleado {
private:
    string nombre;
    Contrato contrato;

public:
    Empleado(string n, Contrato con) : nombre(n), contrato(con) {}

    void mostrarDatos() {
        cout << "Empleado: " << nombre << endl;
        contrato.mostrarContrato();
    }
};

int main() {
    Fecha fechaInicio(1, 4, 2025);
    Contrato contrato("C001", "Contrato indefinido", fechaInicio);
    Empleado emp("Luis García", contrato);
    emp.mostrarDatos();
    return 0;
}
