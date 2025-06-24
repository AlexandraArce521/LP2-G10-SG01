#include <iostream>
#include <vector>
#include <string>

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
    void registrarProducto(const string& nombre, double precio, int cantidad) {
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

    return 0;
}
