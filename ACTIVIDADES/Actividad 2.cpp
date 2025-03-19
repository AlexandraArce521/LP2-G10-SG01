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
    // Es el CONSTRUCTOR
    Producto(string _nombre, float _precio, int _cantidad) :
        nombre(_nombre), precio(_precio), cantidadEnInventario(_cantidad) {}

    // Metodo para OBTENER  el nombre
    string getNombre() const {
        return nombre;
    }

    float getPrecio() const {
        return precio;
    }

    int getCantidadEnInventario() const {
        return cantidadEnInventario;
    }

    // Metodo para CAMBIAR el nombre
    void setNombre(string _nombre) {
        nombre = _nombre;
    }

    void setPrecio(float _precio) {
        precio = _precio;
    }

    void setCantidadEnInventario(int _cantidad) {
        cantidadEnInventario = _cantidad;
    }

    // MOSTRAR 
    void mostrarProducto() const {
        cout << "Producto: " << nombre
             << ", Precio: " << precio
             << ", Cantidad: " << cantidadEnInventario << endl;
    }
};

class Pedido {
private:
    vector<Producto> listaDeProductos;
    string estadoDelPedido;

public:
    // Constructor
    Pedido(string _estado) : estadoDelPedido(_estado) {}

    // Método para agregar un producto al pedido
    void agregarProducto(const Producto& producto) {
        listaDeProductos.push_back(producto);
    }

    // Método para mostrar el pedido completo
    void mostrarPedido() const {
        cout << "Estado del Pedido: " << estadoDelPedido << endl;
        for (const auto& producto : listaDeProductos) {
            producto.mostrarProducto();
        }
    }
};

int main() {
    Producto p1("Audífonos", 300.50, 10);
    Producto p2("Mouse", 25.75, 50);
    Producto p3("Teclado", 45.00, 30);

    Pedido pedido1("En Proceso");

    pedido1.agregarProducto(p1);
    pedido1.agregarProducto(p2);
    pedido1.agregarProducto(p3);

    pedido1.mostrarPedido();

    return 0;
}

