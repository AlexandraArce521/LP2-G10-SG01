#include <iostream>
#include <string>
using namespace std;

/* 
  a) CLASE DE PERSONA
     - Atributos públicos y privados
     - Métodos get y set para los atributos privados
*/
class Persona {
public:
    // Atributo público (ejemplo)
    string nombre;

private:
    // Atributos privados
    string dni;
    int edad;

public:
    // Constructor
    Persona(string n, string d, int e) : nombre(n), dni(d), edad(e) {}

    // Getters y setters para los atributos privados
    string getDNI() const {
        return dni;
    }

    void setDNI(const string &nuevoDNI) {
        dni = nuevoDNI;
    }

    int getEdad() const {
        return edad;
    }

    void setEdad(int nuevaEdad) {
        // Ejemplo de validación
        if (nuevaEdad >= 0) {
            edad = nuevaEdad;
        } else {
            cout << "Edad no válida." << endl;
        }
    }
};

/* 
  b) CLASE DE CUENTA BANCARIA
     - Atributos públicos y privados
     - Métodos depositar(double monto), retirar(double monto) y getters/setters
     - Validar retiros mayores al saldo
*/
class CuentaBancaria {
public:
    // Atributo público (ejemplo)
    string titular;

private:
    // Atributos privados
    double saldo;
    string numeroCuenta;

public:
    // Constructor
    CuentaBancaria(string t, string nc, double s) 
        : titular(t), numeroCuenta(nc), saldo(s) {}

    // Getters y setters
    double getSaldo() const {
        return saldo;
    }

    void setSaldo(double nuevoSaldo) {
        if (nuevoSaldo >= 0) {
            saldo = nuevoSaldo;
        } else {
            cout << "No se puede asignar un saldo negativo." << endl;
        }
    }

    string getNumeroCuenta() const {
        return numeroCuenta;
    }

    void setNumeroCuenta(const string &nc) {
        numeroCuenta = nc;
    }

    // Métodos depositar y retirar
    void depositar(double monto) {
        if (monto > 0) {
            saldo += monto;
            cout << "Depósito exitoso. Nuevo saldo: " << saldo << endl;
        } else {
            cout << "Monto de depósito no válido." << endl;
        }
    }

    void retirar(double monto) {
        if (monto <= saldo && monto > 0) {
            saldo -= monto;
            cout << "Retiro exitoso. Saldo restante: " << saldo << endl;
        } else {
            cout << "No se puede retirar esa cantidad. Saldo insuficiente o monto no válido." << endl;
        }
    }
};

/* 
  c) CLASE DE LIBRO
     - Atributos privados y públicos (titulo, autor, genero)
     - Getters/setters y método auxiliar mostrarInfoLibro()
*/
class Libro {
public:
    // Atributo público (ejemplo)
    string genero;

private:
    // Atributos privados
    string titulo;
    string autor;

public:
    // Constructor
    Libro(string t, string a, string g) 
        : titulo(t), autor(a), genero(g) {}

    // Getters y setters
    string getTitulo() const {
        return titulo;
    }

    void setTitulo(const string &nuevoTitulo) {
        // Podríamos restringir cambios de título si ya está establecido
        titulo = nuevoTitulo;
    }

    string getAutor() const {
        return autor;
    }

    void setAutor(const string &nuevoAutor) {
        autor = nuevoAutor;
    }

    // Método auxiliar
    void mostrarInfoLibro() const {
        cout << "Libro: " << titulo << ", Autor: " << autor 
             << ", Género: " << genero << endl;
    }
};

/* 
  d) CLASE DE FACTURA
     - Atributos privados y públicos
     - Getters/setters y método mostrarFactura()
*/
class Factura {
public:
    // Atributo público (ejemplo)
    double monto;

private:
    // Atributos privados
    string numeroFactura;
    string fecha;

public:
    // Constructor
    Factura(string nf, string f, double m) 
        : numeroFactura(nf), fecha(f), monto(m) {}

    // Getters y setters
    string getNumeroFactura() const {
        return numeroFactura;
    }

    void setNumeroFactura(const string &nf) {
        numeroFactura = nf;
    }

    string getFecha() const {
        return fecha;
    }

    void setFecha(const string &f) {
        fecha = f;
    }

    // Método para mostrar la factura
    void mostrarFactura() const {
        cout << "Factura N°: " << numeroFactura 
             << ", Fecha: " << fecha 
             << ", Monto: " << monto << endl;
    }
};

int main() {
    // a) CLASE DE PERSONA
    cout << "=== CLASE PERSONA ===" << endl;
    Persona persona1("Carlos", "12345678", 25);
    cout << "Nombre: " << persona1.nombre << ", DNI: " << persona1.getDNI()
         << ", Edad: " << persona1.getEdad() << endl;

    persona1.setDNI("87654321");
    persona1.setEdad(30);
    cout << "Nuevos datos -> DNI: " << persona1.getDNI() 
         << ", Edad: " << persona1.getEdad() << endl;

    // b) CLASE DE CUENTA BANCARIA
    cout << "\n=== CLASE CUENTABANCARIA ===" << endl;
    CuentaBancaria cuenta1("María", "CTA-001", 500.0);
    cout << "Titular: " << cuenta1.titular 
         << ", Saldo: " << cuenta1.getSaldo() 
         << ", N° Cuenta: " << cuenta1.getNumeroCuenta() << endl;

    cuenta1.depositar(200);
    cuenta1.retirar(100);
    cuenta1.retirar(700); // Prueba de retiro inválido

    // c) CLASE DE LIBRO
    cout << "\n=== CLASE LIBRO ===" << endl;
    Libro libro1("El Principito", "Antoine de Saint-Exupery", "Fantasía");
    libro1.mostrarInfoLibro();
    libro1.setTitulo("El Principito (Edición Especial)");
    libro1.mostrarInfoLibro();

    // d) CLASE DE FACTURA
    cout << "\n=== CLASE FACTURA ===" << endl;
    Factura factura1("FAC-100", "2025-05-01", 250.0);
    factura1.mostrarFactura();
    factura1.monto = 300.0; // Atributo público (podría cambiarse sin control)
    factura1.setFecha("2025-05-02");
    factura1.mostrarFactura();

    return 0;
}
