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
    Producto p1("Audífonos", 300.50, 10);
    Producto p2("Mouse", 25.75, 50);
    Producto p3("Teclado", 45.00, 30);

    GestorDeInventario gestor;
    gestor.agregarProducto(p1);
    gestor.agregarProducto(p2);
    gestor.agregarProducto(p3);

    GeneradorDeReportes generador(gestor);

    Pedido pedido1("Completado");
    pedido1.agregarProducto(Producto("Laptop", 1500.50, 2));
    pedido1.agregarProducto(Producto("Mouse", 25.75, 5));

    generador.agregarPedido(pedido1);

    gestor.actualizarInventario(pedido1);

    generador.reporteGeneral();

    return 0;
}
