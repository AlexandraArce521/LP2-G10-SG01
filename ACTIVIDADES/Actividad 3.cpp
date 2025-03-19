#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Clase Producto
class Producto {
private:
    string nombre;
    float precio;
    int cantidadEnInventario;

public:
    // Constructor
    Producto(string _nombre, float _precio, int _cantidad) :
        nombre(_nombre), precio(_precio), cantidadEnInventario(_cantidad) {}

    string getNombre() const {
        return nombre;
    }

    float getPrecio() const {
        return precio;
    }

    int getCantidadEnInventario() const {
        return cantidadEnInventario;
    }

    void setNombre(string _nombre) {
        nombre = _nombre;
    }

    void setPrecio(float _precio) {
        precio = _precio;
    }

    void setCantidadEnInventario(int _cantidad) {
        cantidadEnInventario = _cantidad;
    }

    // Mostrar detalles del producto
    void mostrarProducto() const {
        cout << "Producto: " << nombre
             << ", Precio: " << precio
             << ", Cantidad: " << cantidadEnInventario << endl;
    }
};

// Clase Pedido
class Pedido {
private:
    vector<Producto> listaDeProductos;
    string estadoDelPedido;

public:
    // Constructor
    Pedido(string _estado) : estadoDelPedido(_estado) {}

    // Agregar producto al pedido
    void agregarProducto(const Producto& producto) {
        listaDeProductos.push_back(producto);
    }

    // Mostrar detalles del pedido
    void mostrarPedido() const {
        cout << "Estado del Pedido: " << estadoDelPedido << endl;
        for (const auto& producto : listaDeProductos) {
            producto.mostrarProducto();
        }
    }

    // Obtener la lista de productos del pedido
    vector<Producto> getListaDeProductos() const {
        return listaDeProductos;
    }
};

// Clase GestorDeInventario
class GestorDeInventario {
private:
    vector<Producto> listaDeProductos;

public:
    // Agregar un producto al inventario
    void agregarProducto(const Producto& nuevoProducto) {
        listaDeProductos.push_back(nuevoProducto);
    }

    // Actualizar inventario según el pedido
    void actualizarInventario(const Pedido& pedido) {
        vector<Producto> productosPedido = pedido.getListaDeProductos();

        for (const auto& productoPedido : productosPedido) {
            bool encontrado = false;
            for (auto& productoInventario : listaDeProductos) {
                if (productoInventario.getNombre() == productoPedido.getNombre()) {
                    if (productoInventario.getCantidadEnInventario() >= productoPedido.getCantidadEnInventario()) {
                        productoInventario.setCantidadEnInventario(productoInventario.getCantidadEnInventario() - productoPedido.getCantidadEnInventario());
                    } else {
                        cout << "Error: No hay suficiente inventario para " << productoPedido.getNombre() << endl;
                    }
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                cout << "Error: Producto " << productoPedido.getNombre() << " no encontrado en inventario." << endl;
            }
        }
    }

    // Mostrar el inventario completo
    void mostrarInventario() const {
        cout << "Inventario actual:" << endl;
        for (const auto& producto : listaDeProductos) {
            producto.mostrarProducto();
        }
    }
};

// Función principal
int main() {
    // Crear productos
    Producto p1("Laptop", 1500.50, 10);
    Producto p2("Mouse", 25.75, 50);
    Producto p3("Teclado", 45.00, 30);

    // Crear el gestor de inventario y agregar productos
    GestorDeInventario gestor;
    gestor.agregarProducto(p1);
    gestor.agregarProducto(p2);
    gestor.agregarProducto(p3);

    // Mostrar el inventario inicial
    gestor.mostrarInventario();

    // Crear un pedido
    Pedido pedido1("En Proceso");
    pedido1.agregarProducto(Producto("Laptop", 1500.50, 2));
    pedido1.agregarProducto(Producto("Mouse", 25.75, 5));

    // Mostrar el pedido
    pedido1.mostrarPedido();

    // Actualizar el inventario según el pedido
    gestor.actualizarInventario(pedido1);

    // Mostrar el inventario actualizado
    gestor.mostrarInventario();

    return 0;
}
