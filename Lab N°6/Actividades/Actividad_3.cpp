#include <iostream>
#include <string>
using namespace std;

class Banco 
{
public:
    static float tasaInteres; // Atributo estático

    static void cambiarTasa(float nuevaTasa) {
        tasaInteres = nuevaTasa;
    }
};

// Definición del atributo estático fuera de la clase
float Banco::tasaInteres = 3.5;

class Cuenta 
{
private:
    float saldo;

public:
    Cuenta(float s) {
        saldo = s;
    }

    void depositar(float monto) {
        saldo += monto;
    }

    void retirar(float monto) {
        if (monto <= saldo) {
            saldo -= monto;
        } else {
            cout << "Fondos insuficientes." << endl;
        }
    }

    float calcularInteres() {
        return saldo * Banco::tasaInteres / 100;
    }

    void mostrarSaldo() {
        cout << "Saldo: " << saldo << " | Interés ganado: " << calcularInteres() << endl;
    }
};

int main()
{
    Cuenta cuenta1(1000);
    cuenta1.depositar(500);
    cuenta1.retirar(200);
    cuenta1.mostrarSaldo();

    Banco::cambiarTasa(4.2);
    cuenta1.mostrarSaldo(); // Nuevo interés con nueva tasa

    return 0;
}
