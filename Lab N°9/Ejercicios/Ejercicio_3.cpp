#include<vector>
#include <iostream>
using namespace std;

class Salario{
public:
    virtual double calcularSalario() = 0;
    virtual void informacionEmpleado() = 0;
    virtual ~Salario() = default; 
};

class Asalariado: public Salario {
private: 
    double sMensual;
    string nombre;

public:

    Asalariado(double mensual, string n)
     :sMensual(mensual), nombre(n) {}
     
    double calcularSalario() override {
        return sMensual * 12 * 0.90;
    }
    
    void informacionEmpleado() override {
        cout << "===INFORMACION DE EMPLEADO ASALARIADO==="<< endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Salario bruto: " << calcularSalario()/0.90 << endl;
        cout << "Descuento AFP (10%): " << calcularSalario()/0.90*0.10 << endl; 
        cout << "Salario neto anual: S/ " << calcularSalario() << endl;
    }
};

class PorHora: public Salario {
private:
    string nombre;
    int horasTrabajadas;
    double tarifaPorHora;

public:  
    PorHora(string n, int horas, double tarifa)
     :nombre(n), horasTrabajadas(horas), tarifaPorHora(tarifa) {}
    
    double calcularSalario() override {
        return horasTrabajadas*tarifaPorHora;
    }
    
    void informacionEmpleado() override {
        cout << "===INFORMACION DE EMPLEADO POR HORA==="<< endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Horas trabajadas: " << horasTrabajadas << endl;
        cout << "Tarifa: " << tarifaPorHora << "$ " << endl;
        cout << "Salario neto: " << calcularSalario() << endl;
    }
};

class Comisionista: public Salario {
private:
    string nombre;
    double sueldoBase;
    double ventas;
    double porcentajeComision;
    
public:
    Comisionista(string n, double sueldoB, double v, double porcentaje)
     :nombre(n), sueldoBase(sueldoB), ventas(v), porcentajeComision(porcentaje) {}

    double calcularSalario() override {
        return sueldoBase + (ventas*porcentajeComision);
    }
    
    void informacionEmpleado() override {
        cout << "===INFORMACION DE EMPLEADO POR COMISION==="<< endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Sueldo base: " << sueldoBase << endl;
        cout << "N° de ventas: " <<ventas << endl;
        cout << "Comisión por venta: " << porcentajeComision*100 << endl;
    }
    
};

int main () {
    vector <Salario*> empleados;
    
    empleados.push_back(new Asalariado(2500.0, "Juan Vega"));
    empleados.push_back(new PorHora("Claudia", 25.0, 160));
    empleados.push_back(new Comisionista("Pedro", 1200.0, 10000.0, 0.10));
    empleados.push_back(new Asalariado(3060.0, "Sheyla"));

    for (int i = 0; i < empleados.size(); ++i) {
        empleados[i]->informacionEmpleado();
        cout << "  => Salario calculado: S/ " << empleados[i]->calcularSalario() << "\n\n";
    }

    for (int i = 0; i < empleados.size(); ++i) {
        delete empleados[i];
    }    
    return 0;
}
