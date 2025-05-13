#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Clase base Cliente: guarda datos personales y financieros
class Cliente {
protected:
    string nombre;
    string email;
    string tarjeta;  // número de tarjeta (simulado)

    // Método protegido de cifrado muy básico (invierte el string)
    string cifrar(const string& dato) {
        string copia = dato;
        reverse(copia.begin(), copia.end());
        return copia;
    }

public:
    // Constructor de Cliente
    Cliente(const string& n, const string& e, const string& t)
        : nombre(n), email(e), tarjeta(t)
    {
        cout << "Cliente creado: " << nombre << "\n";
    }

    // Destructor de Cliente
    ~Cliente() {
        cout << "Cliente destruido: " << nombre << "\n";
    }
};

// Clase derivada pública ClienteSeguro
class ClienteSeguro : public Cliente {
public:
    // Constructor llama al de la base
    ClienteSeguro(const string& n, const string& e, const string& t)
        : Cliente(n, e, t)
    {
        cout << "ClienteSeguro inicializado\n";
    }

    // Destructor
    ~ClienteSeguro() {
        cout << "ClienteSeguro destruido\n";
    }

    // Método que cifra la tarjeta y la muestra
    void almacenarSeguro() {
        string tarCif = cifrar(tarjeta);
        cout << "Información cifrada de " << nombre
             << ": tarjeta = " << tarCif << "\n";
    }

    // Verifica autenticidad comparando cadenas cifradas
    bool verificar(const string& intento) {
        return cifrar(intento) == cifrar(tarjeta);
    }
};

// Herencia protegida
class ClienteProtegido : protected Cliente {
public:
    ClienteProtegido(const string& n, const string& e, const string& t)
        : Cliente(n, e, t) {}

    void demo() {
        cout << "Herencia protected: nombre = " << nombre << "\n";
    }
};

// Herencia privada
class ClientePrivado : private Cliente {
public:
    ClientePrivado(const string& n, const string& e, const string& t)
        : Cliente(n, e, t) {}

    void demo() {
        cout << "Herencia private: email = " << email << "\n";
    }
};

int main() {
    // Uso de ClienteSeguro (herencia pública)
    ClienteSeguro cs("Ana Pérez", "ana@ejemplo.com", "1234-5678-9012-3456");
    cs.almacenarSeguro();
    cout << "Verificación correcta: "
         << (cs.verificar("1234-5678-9012-3456") ? "sí" : "no") << "\n\n";

    // Demostración de herencia protegida
    ClienteProtegido cp("Luis Gómez", "luis@ejemplo.com", "0000-1111-2222-3333");
    cp.demo();

    // Demostración de herencia privada
    ClientePrivado cpr("Marta Ruiz", "marta@ejemplo.com", "9999-8888-7777-6666");
    cpr.demo();

    return 0;
}
