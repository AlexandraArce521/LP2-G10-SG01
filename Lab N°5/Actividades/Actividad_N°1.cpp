#include <iostream>
using namespace std;

class CuentaBancaria {
private:
    int numero;
    string titular;
    double saldo;

public:
    CuentaBancaria(int n, string t, double s) {
        numero = n;
        titular = t;
        saldo = s;
    }

    // Método para depositar dinero
    CuentaBancaria& depositar(double monto) {
        saldo += monto;
        return *this;
    }

    // Método para retirar dinero
    CuentaBancaria& retirar(double monto) {
        if (monto <= saldo) {
            saldo -= monto;
        } else {
            cout << "Fondos insuficientes.\n";
        }
        return *this;
    }

    // Mostrar saldo actual
    void mostrarSaldo() {
        cout << "Saldo actual de " << titular << ": " << saldo << endl;
    }
};

int main() {
    CuentaBancaria cuenta(12345, "Juan Pérez", 500);
    cuenta.depositar(1000).retirar(200).mostrarSaldo();
    return 0;
}
