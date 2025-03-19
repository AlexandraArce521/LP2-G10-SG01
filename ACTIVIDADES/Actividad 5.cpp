#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Producto {
private:
    string nombre;
    float precio;
    int cantidadEnInventario;

public:
    Producto(string _nombre, float _precio, int _cantidad) : nombre(_nombre), precio(_precio), cantidadEnInventario(_cantidad) {}

    string getNombre() const { return nombre; }
    float getPrecio() const { return precio; }
    int getCantidadEnInventario() const { return cantidadEnInventario; }

    void setCantidadEnInventario(int _cantidad) { cantidadEnInventario = _cantidad; }

    void mostrarProducto() const {
        cout << "Producto: " << nombre << ", Precio: " << precio << ", Cantidad: " << cantidadEnInventario << endl;
    }
};

class Pedido {
private:
    vector<Producto> listaDeProductos;
    string estadoDelPedido;

public:
    Pedido(string _estado) : estadoDelPedido(_estado) {}

    void agregarProducto(const Producto& producto) {
        listaDeProductos.push_back(producto);
    }

    vector<Producto> getListaDeProductos() const {
        return listaDeProductos;
    }

    void mostrarPedido() const {
        cout << "Estado del Pedido: " << estadoDelPedido << endl;
        for (const auto& producto : listaDeProductos) {
            producto.mostrarProducto();
        }
    }
};

class GestorDeInventario {
private:
    vector<Producto> listaDeProductos;

public:
    void agregarProducto(const Producto& nuevoProducto) {
        listaDeProductos.push_back(nuevoProducto);
    }

    void actualizarInventario(const Pedido& pedido) {
        for (const auto& productoPedido : pedido.getListaDeProductos()) {
            for (auto& productoInventario : listaDeProductos) {
                if (productoInventario.getNombre() == productoPedido.getNombre()) {
                    if (productoInventario.getCantidadEnInventario() >= productoPedido.getCantidadEnInventario()) {
                        productoInventario.setCantidadEnInventario(productoInventario.getCantidadEnInventario() - productoPedido.getCantidadEnInventario());
                    }
                    break;
                }
            }
        }
    }

    vector<Producto> getInventario() const {
        return listaDeProductos;
    }

    void mostrarInventario() const {
        cout << "Inventario actual:" << endl;
        for (const auto& producto : listaDeProductos) {
            producto.mostrarProducto();
        }
    }

    Producto* buscarProducto(const string& nombre) {
        for (auto& producto : listaDeProductos) {
            if (producto.getNombre() == nombre) {
                return &producto;
            }
        }
        return nullptr;
    }
};

class GeneradorDeReportes {
private:
    vector<Pedido> pedidosHistorial;
    GestorDeInventario& gestor;

public:
    GeneradorDeReportes(GestorDeInventario& _gestor) : gestor(_gestor) {}

    void agregarPedido(const Pedido& pedido) {
        pedidosHistorial.push_back(pedido);
    }

    void reporteVentas() const {
        cout << "--- REPORTE DE VENTAS ---" << endl;
        for (const auto& pedido : pedidosHistorial) {
            pedido.mostrarPedido();
        }
    }

    void reporteGeneral() const {
        cout << "--- REPORTE GENERAL ---" << endl;
        gestor.mostrarInventario();
        reporteVentas();
    }
};

int main() {
    GestorDeInventario gestor;
    GeneradorDeReportes generador(gestor);

    int opcion;
    do {
        cout << "\nMENU:\n";
        cout << "1. Registrar un nuevo producto\n";
        cout << "2. Crear y procesar un nuevo pedido\n";
        cout << "3. Generar reportes\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            string nombre;
            float precio;
            int cantidad;
            cout << "Ingrese el nombre del producto: ";
            cin >> nombre;
            cout << "Ingrese el precio del producto: ";
            cin >> precio;
            cout << "Ingrese la cantidad en inventario: ";
            cin >> cantidad;
            gestor.agregarProducto(Producto(nombre, precio, cantidad));
        } else if (opcion == 2) {
            Pedido nuevoPedido("En proceso");
            char continuar;
            do {
                string nombre;
                int cantidad;
                cout << "Ingrese el nombre del producto: ";
                cin >> nombre;
                Producto* producto = gestor.buscarProducto(nombre);
                if (producto) {
                    cout << "Ingrese la cantidad a pedir: ";
                    cin >> cantidad;
                    nuevoPedido.agregarProducto(Producto(producto->getNombre(), producto->getPrecio(), cantidad));
                } else {
                    cout << "Producto no encontrado.\n";
                }
                cout << "Agregar otro producto? (s/n): ";
                cin >> continuar;
            } while (continuar == 's' || continuar == 'S');

            generador.agregarPedido(nuevoPedido);
            gestor.actualizarInventario(nuevoPedido);
        } else if (opcion == 3) {
            generador.reporteGeneral();
        }

    } while (opcion != 4);

    cout << "Saliendo del programa." << endl;

    return 0;
}
