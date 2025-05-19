#include <iostream>
using namespace std;

class Empleado {
public:
    virtual double calcularSalario() = 0;
};

class EmpleadoTiempoCompleto: public Empleado {
private:
    double salAnual;
    
public:
    EmpleadoTiempoCompleto(double anual) 
     :salAnual(anual) {}
    
    double calcularSalario() override {
      return salAnual / 12.0;  
    };
    
};

class EmpleadoMedioTiempo : public Empleado {
private:
    double tarifaHora;
    int horasPorSemana;

public:
    EmpleadoMedioTiempo(double tarifa, int horas)
        : tarifaHora(tarifa), horasPorSemana(horas) {}

    double calcularSalario() override {
        return tarifaHora * horasPorSemana * 4.33; // 52 semanas / 12 meses = 4.33
    }
};

int main()
{
    Empleado* empCompleto1 = new EmpleadoTiempoCompleto(14500);
    Empleado* empMedio1 = new EmpleadoMedioTiempo(3.4, 48);
    
    cout << "El empleado de tiempo completo tiene un sueldo mensual de: " << empCompleto1 ->calcularSalario() << "$\n";
    cout << "El empleado de medio tiempo tiene un sueldo mensual de: " << empMedio1 ->calcularSalario() << "$\n";
    
    delete empCompleto1;
    delete empMedio1;
    
    return 0;
}
