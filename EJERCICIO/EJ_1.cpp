// EJ_1.cpp 

#include <iostream>
#include <string>

using namespace std;

#define MAX_PRODUCTOS 100
#define MAX_ITEMS_PEDIDO 10
#define MAX_PEDIDOS 50

// Clase Producto: representa un producto de la tienda
class Producto {
private:
    string nombre;
    float precio;
    int cantidad;
public:
    Producto() : nombre(""), precio(0.0), cantidad(0) {}
    Producto(string n, float p, int c) : nombre(n), precio(p), cantidad(c) {}

    string getNombre() const { return nombre; }
    float getPrecio() const { return precio; }
    int getCantidad() const { return cantidad; }

    void setCantidad(int c) { cantidad = c; }

    void mostrarProducto() const {
        cout << "Producto: " << nombre << " | Precio: S/." << precio << " | Cantidad: " << cantidad << endl;
    }
};

// Clase Inventario: administra los productos de la tienda en un arreglo fijo
class Inventario {
private:
    Producto productos[MAX_PRODUCTOS];
    int numProductos;
public:
    Inventario() : numProductos(0) {}

    bool registrarProducto(const Producto& p) {
        if (numProductos >= MAX_PRODUCTOS)
            return false;
        productos[numProductos] = p;
        numProductos++;
        return true;
    }

    void mostrarInventario() const {
        cout << "\n---------- Inventario ----------" << endl;
        for (int i = 0; i < numProductos; i++) {
            cout << i + 1 << ". ";
            productos[i].mostrarProducto();
        }
    }

    // Busca un producto por nombre; devuelve el índice o -1 si no se encuentra
    int buscarProducto(const string& nombre) const {
        for (int i = 0; i < numProductos; i++) {
            if (productos[i].getNombre() == nombre)
                return i;
        }
        return -1;
    }

    // Devuelve una referencia al producto en el arreglo (versión no const)
    Producto& getProducto(int indice) {
        return productos[indice];
    }

    // Versión const para poder llamar a este método desde objetos const
    const Producto& getProducto(int indice) const {
        return productos[indice];
    }

    int getNumProductos() const {
        return numProductos;
    }
};

// Clase Pedido: almacena la información de un pedido realizado por un cliente
class Pedido {
private:
    string cliente;
    int itemIndices[MAX_ITEMS_PEDIDO];   // Índices de productos en el inventario
    int cantidades[MAX_ITEMS_PEDIDO];      // Cantidades solicitadas para cada producto
    int numItems;
    bool notificado;
public:
    Pedido() : cliente(""), numItems(0), notificado(false) {}
    Pedido(string cl) : cliente(cl), numItems(0), notificado(false) {}

    bool agregarItem(int indiceProducto, int cantidad) {
        if (numItems >= MAX_ITEMS_PEDIDO)
            return false;
        itemIndices[numItems] = indiceProducto;
        cantidades[numItems] = cantidad;
        numItems++;
        return true;
    }

    void mostrarPedido(const Inventario& inv) const {
        cout << "\nPedido de " << cliente << ":" << endl;
        for (int i = 0; i < numItems; i++) {
            cout << "- " << inv.getProducto(itemIndices[i]).getNombre()
                << " : " << cantidades[i] << " unidades" << endl;
        }
    }

    void notificarCliente() {
        notificado = true;
        cout << "Notificacion: El pedido de " << cliente; 
        cout << " esta listo para ser recogido." << endl;
    }
};

// Clase Ventas: registra el monto total de las ventas realizadas
class Ventas {
private:
    float totalVentas;
public:
    Ventas() : totalVentas(0) {}

    void registrarVenta(float monto) {
        totalVentas += monto;
    }

    void mostrarReporteVentas() const {
        cout << "\nReporte de Ventas: S/." << totalVentas << endl;
    }
};

// Clase SistemaPedidos: gestiona un arreglo de pedidos
class SistemaPedidos {
private:
    Pedido pedidos[MAX_PEDIDOS];
    int numPedidos;
public:
    SistemaPedidos() : numPedidos(0) {}

    bool registrarPedido(const Pedido& p) {
        if (numPedidos >= MAX_PEDIDOS)
            return false;
        pedidos[numPedidos] = p;
        numPedidos++;
        return true;
    }

    // Notifica y elimina el primer pedido pendiente
    void notificarPrimerPedido(const Inventario& inv) {
        if (numPedidos == 0) {
            cout << "\nNo hay pedidos pendientes." << endl;
            return;
        }
        pedidos[0].mostrarPedido(inv);
        pedidos[0].notificarCliente();
        // Desplazar pedidos hacia adelante
        for (int i = 1; i < numPedidos; i++) {
            pedidos[i - 1] = pedidos[i];
        }
        numPedidos--;
    }
};

// Función que implementa el menú principal del sistema
void menuTienda() {
    Inventario inventario;
    Ventas ventas;
    SistemaPedidos sistemaPedidos;
    int opcion;

    do {
        cout << "------------------------------------------" << endl;
        cout << "---- Sistema para Tienda de Abarrotes ----" << endl;
        cout << "------------------------------------------" << endl;
        cout << "1. Registrar producto en el inventario" << endl;
        cout << "2. Mostrar inventario" << endl;
        cout << "3. Realizar venta (pedido)" << endl;
        cout << "4. Notificar pedido listo" << endl;
        cout << "5. Reporte de ventas" << endl;
        cout << "6. Salir" << endl;
        cout << "------------------------------------------" << endl;
        cout << "\nIngrese su opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            string nombre;
            float precio;
            int cantidad;
            cout << "\nIngrese el nombre del producto: ";
            cin >> nombre;
            cout << "Ingrese el precio: ";
            cin >> precio;
            cout << "Ingrese la cantidad en inventario: ";
            cin >> cantidad;
            Producto p(nombre, precio, cantidad);
            if (inventario.registrarProducto(p)) {
                cout << "Producto registrado.\n" << endl;
            }
            else {
                cout << "Error: inventario lleno." << endl;
            }
        }
        else if (opcion == 2) {
            inventario.mostrarInventario();
            cout << "\n";
        }
        else if (opcion == 3) {
            string cliente;
            cout << "\nIngrese el nombre del cliente: ";
            cin >> cliente;
            Pedido pedido(cliente);
            int numItems;
            cout << "Cuantos productos desea comprar?: ";
            cin >> numItems;
            float totalVenta = 0;
            for (int i = 0; i < numItems; i++) {
                string prodNombre;
                int cantidadSolicitada;
                cout << "\nIngrese el nombre del producto: ";
                cin >> prodNombre;
                cout << "Ingrese la cantidad: ";
                cin >> cantidadSolicitada;
                int indice = inventario.buscarProducto(prodNombre);
                if (indice != -1) {
                    Producto& prod = inventario.getProducto(indice);
                    if (prod.getCantidad() >= cantidadSolicitada) {
                        totalVenta += cantidadSolicitada * prod.getPrecio();
                        prod.setCantidad(prod.getCantidad() - cantidadSolicitada);
                        pedido.agregarItem(indice, cantidadSolicitada);
                    }
                    else {
                        cout << "Stock insuficiente para " << prodNombre << endl;
                    }
                }
                else {
                    cout << "Producto " << prodNombre << " no encontrado." << endl;
                }
            }
            ventas.registrarVenta(totalVenta);
            sistemaPedidos.registrarPedido(pedido);
            cout << "\nVenta realizada. Total a pagar: S/." << totalVenta << endl << "\n";
        }
        else if (opcion == 4) {
            sistemaPedidos.notificarPrimerPedido(inventario);
            cout << "\n";
        }
        else if (opcion == 5) {
            ventas.mostrarReporteVentas();
            cout << "\n";
        }
        else if (opcion == 6) {
            cout << "\nSaliendo del sistema...\n" << endl;
        }
        else {
            cout << "\nOpcion no valida.\n" << endl;
        }

    } while (opcion != 6);
}

int main() {
    menuTienda();
    return 0;
}

