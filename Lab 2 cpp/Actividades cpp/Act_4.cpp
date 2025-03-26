#include <iostream>
#include <vector>
using namespace std;

// ========================== 1. Biblioteca y Libro ==========================
class Libro {
private:
    string titulo;
    bool prestado;
public:
    Libro(string t) : titulo(t), prestado(false) {}

    bool estaPrestado() const { return prestado; }
    string getTitulo() const { return titulo; }

    void prestar() { 
        if (!prestado) {
            prestado = true;
            cout << "El libro '" << titulo << "' ha sido prestado." << endl;
        } else {
            cout << "El libro '" << titulo << "' ya está prestado." << endl;
        }
    }

    void devolver() {
        if (prestado) {
            prestado = false;
            cout << "El libro '" << titulo << "' ha sido devuelto." << endl;
        } else {
            cout << "El libro '" << titulo << "' no estaba prestado." << endl;
        }
    }
};

class Biblioteca {
public:
    void prestarLibro(Libro& libro) { libro.prestar(); }
    void recibirLibro(Libro& libro) { libro.devolver(); }
};

// ========================== 2. Factura y Producto ==========================
class Producto {
private:
    string nombre;
    float precio;
    int cantidad;
public:
    Producto(string n, float p, int c) : nombre(n), precio(p), cantidad(c) {}

    string getNombre() const { return nombre; }
    float getPrecio() const { return precio; }
    int getCantidad() const { return cantidad; }

    void setCantidad(int c) { cantidad = c; }
};

class Factura {
private:
    vector<Producto> productos;
public:
    void agregarProducto(const Producto& producto) {
        productos.push_back(producto);
        cout << "Producto agregado: " << producto.getNombre() << endl;
    }

    float calcularTotal() const {
        float total = 0;
        for (const auto& producto : productos) {
            total += producto.getPrecio() * producto.getCantidad();
        }
        return total;
    }

    void mostrarFactura() const {
        cout << "---- Factura ----" << endl;
        for (const auto& producto : productos) {
            cout << producto.getNombre() << " - S/." << producto.getPrecio() << " x " << producto.getCantidad() << endl;
        }
        cout << "Total a pagar: S/." << calcularTotal() << endl;
    }
};

// ========================== 3. Carro y Rueda ==========================
class Rueda {
private:
    int tamano;
public:
    Rueda(int t) : tamano(t) {}

    int getTamano() const { return tamano; }
};

class Carro {
private:
    Rueda ruedas[4]; // Cuatro ruedas
public:
    Carro(int tamanoRueda) : ruedas{Rueda(tamanoRueda), Rueda(tamanoRueda), Rueda(tamanoRueda), Rueda(tamanoRueda)} {}

    void cambiarRueda(int posicion, int nuevoTamano) {
        if (posicion >= 0 && posicion < 4) {
            ruedas[posicion] = Rueda(nuevoTamano);
            cout << "Rueda en posición " << posicion << " cambiada a tamaño " << nuevoTamano << endl;
        } else {
            cout << "Posición no válida." << endl;
        }
    }

    void mostrarRuedas() const {
        for (int i = 0; i < 4; i++) {
            cout << "Rueda " << i << ": Tamaño " << ruedas[i].getTamano() << endl;
        }
    }
};

// ========================== 4. Tienda y Cliente ==========================
class Tienda {
private:
    vector<Producto> inventario;
public:
    void agregarProducto(const Producto& producto) {
        inventario.push_back(producto);
    }

    Producto* buscarProducto(const string& nombre) {
        for (auto& producto : inventario) {
            if (producto.getNombre() == nombre) {
                return &producto;
            }
        }
        return nullptr;
    }

    void venderProducto(const string& nombre, int cantidad) {
        Producto* producto = buscarProducto(nombre);
        if (producto && producto->getCantidad() >= cantidad) {
            producto->setCantidad(producto->getCantidad() - cantidad);
            cout << "Venta realizada: " << nombre << " x" << cantidad << endl;
        } else {
            cout << "Producto no disponible o stock insuficiente." << endl;
        }
    }
};

class Cliente {
private:
    string nombre;
public:
    Cliente(string n) : nombre(n) {}

    void comprarProducto(Tienda& tienda, const string& nombre, int cantidad) {
        tienda.venderProducto(nombre, cantidad);
    }
};

// ========================== FUNCION PRINCIPAL ==========================
int main() {
    cout << "\n----- PRUEBA DE COLABORACIÓN ENTRE OBJETOS -----\n" << endl;

    // === 1. Prueba de Biblioteca y Libro ===
    cout << "\nPrueba de Biblioteca y Libro:" << endl;
    Libro libro1("Cien años de soledad");
    Biblioteca biblioteca;
    biblioteca.prestarLibro(libro1);
    biblioteca.prestarLibro(libro1); // Intentar prestarlo de nuevo
    biblioteca.recibirLibro(libro1);
    biblioteca.recibirLibro(libro1); // Intentar devolverlo de nuevo

    // === 2. Prueba de Factura y Producto ===
    cout << "\nPrueba de Factura y Producto:" << endl;
    Producto p1("Laptop", 3000.0, 1);
    Producto p2("Mouse", 50.0, 2);
    Factura factura;
    factura.agregarProducto(p1);
    factura.agregarProducto(p2);
    factura.mostrarFactura();

    // === 3. Prueba de Carro y Rueda ===
    cout << "\nPrueba de Carro y Rueda:" << endl;
    Carro carro(17); // Ruedas tamaño 17
    carro.mostrarRuedas();
    carro.cambiarRueda(2, 18); // Cambiar una rueda a tamaño 18
    carro.mostrarRuedas();

    // === 4. Prueba de Tienda y Cliente ===
    cout << "\nPrueba de Tienda y Cliente:" << endl;
    Tienda tienda;
    tienda.agregarProducto(Producto("Televisor", 2000.0, 5));
    tienda.agregarProducto(Producto("Celular", 1000.0, 3));
    Cliente cliente("Carlos");
    cliente.comprarProducto(tienda, "Televisor", 2);
    cliente.comprarProducto(tienda, "Celular", 5); // Stock insuficiente

    return 0;
}
