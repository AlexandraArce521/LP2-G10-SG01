#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Inventario {
private:
    struct Producto {
        string nombre;
        double precio;
        int cantidad;
    };
    vector<Producto> productos;

public:
    Inventario() {
        ofstream archivo("Productos.txt", ios::out);
        archivo.close();
    }

    void registrarProducto(const string nombre, double precio, int cantidad) {
        for (const auto& prod : productos) {
            if (prod.nombre == nombre) {
                cout << "Error: Producto ya existe.\n";
                return;
            }
        }
        if (precio < 0 || cantidad < 0) {
            cout << "Error: Precio o cantidad no pueden ser negativos.\n";
            return;
        }

        Producto nuevo = {nombre, precio, cantidad};
        productos.push_back(nuevo);
        cout << "Producto " << nombre << " registrado.\n";

        guardarProducto(nuevo); 
    }

    void guardarProducto(const Producto& p) {
        ofstream archivo("Productos.txt", ios::app); 
        if (archivo.is_open()) {
            archivo << p.nombre << "|" << p.precio << "|" << p.cantidad << "\n";
            archivo.close();
        } else {
            cout << "Error al abrir el archivo para escritura.\n";
        }
    }

    void reescribirArchivo() {
        ofstream archivo("Productos.txt", ios::out);
        if (archivo.is_open()) {
            for (const auto& prod : productos) {
                archivo << prod.nombre << "|" << prod.precio << "|" << prod.cantidad << "\n";
            }
            archivo.close();
        } else {
            cout << "Error al abrir el archivo para reescritura.\n";
        }
    }

    void actualizarProducto(const string& nombre, double nuevoPrecio, int nuevaCantidad) {
        for (auto& prod : productos) {
            if (prod.nombre == nombre && prod.cantidad >= 0) {
                if (nuevoPrecio < 0 || nuevaCantidad < 0) {
                    cout << "Error: Precio o cantidad no pueden ser negativos.\n";
                    return;
                }
                prod.precio = nuevoPrecio;
                prod.cantidad = nuevaCantidad;
                cout << "Producto " << nombre << " actualizado.\n";
                reescribirArchivo();  
                return;
            }
        }
        cout << "Error: Producto no encontrado.\n";
    }

    void cambiarProducto(const string& nombre, double nuevoPrecio, int nuevaCantidad) {
        for (auto& prod : productos) {
            if (prod.nombre == nombre) {
                if (nuevoPrecio < 0 || nuevaCantidad < 0) {
                    cout << "Error: Precio o cantidad no pueden ser negativos.\n";
                    return;
                }
                prod.precio = nuevoPrecio;
                prod.cantidad = nuevaCantidad;
                cout << "Producto actualizado: " << nombre << " | Precio: " << nuevoPrecio << " | Cantidad: " << nuevaCantidad << "\n";
                reescribirArchivo(); 
                return;
            }
        }
        cout << "Error: Producto no encontrado.\n";
    }

    void realizarVenta(const string& nombre, int cantidadVendida) {
        for (auto& prod : productos) {
            if (prod.nombre == nombre && prod.cantidad >= cantidadVendida) {
                if (cantidadVendida < 0) {
                    cout << "Error: Cantidad vendida no puede ser negativa.\n";
                    return;
                }
                prod.cantidad -= cantidadVendida;
                cout << "Venta de " << cantidadVendida << " unidades de " << nombre << " realizada.\n";
                reescribirArchivo(); // Actualiza el archivo completo
                return;
            }
        }
        cout << "Error: Producto no encontrado o cantidad insuficiente.\n";
    }

    void generarInforme() {
        if (productos.empty()) {
            cout << "No hay productos registrados.\n";
            return;
        }
        cout << "\n=== Informe de Inventario ===\n";
        cout << "Nombre\tPrecio\tCantidad\n";
        cout << "----------------------------\n";
        for (const auto& prod : productos) {
            if (prod.cantidad >= 0) {
                cout << prod.nombre << "\t" << prod.precio << "\t" << prod.cantidad << "\n";
            }
        }
    }

    void buscarProducto(const string& nombre) {
        for (const auto& prod : productos) {
            if (prod.nombre == nombre && prod.cantidad >= 0) {
                cout << "Producto encontrado: " << prod.nombre << ", Precio: " << prod.precio 
                     << ", Cantidad: " << prod.cantidad << "\n";
                return;
            }
        }
        cout << "Error: Producto no encontrado.\n";
    }
};

int main() {
    Inventario inv;

    inv.registrarProducto("Televisor", 500.0, 10);
    inv.registrarProducto("Laptop", 800.0, 5);

    inv.generarInforme();

    inv.actualizarProducto("Televisor", 550.0, 8);
    inv.realizarVenta("Laptop", 2);

    inv.generarInforme();

    inv.buscarProducto("Televisor");
    inv.cambiarProducto("Laptop", 850.0, 7);

    return 0;
}

