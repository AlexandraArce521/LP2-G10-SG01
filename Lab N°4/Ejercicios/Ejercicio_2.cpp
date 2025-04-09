#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Declaración anticipada de las clases
class Venta;

class Producto 
{
    private:
        int codigo;
        string nombre; 
        string descripcion;
        double precio;
        string proveedor;
    
    public:
        Producto(int codigo, string nombre, string descripcion, double precio, string proveedor)
        : codigo(codigo), nombre(nombre), descripcion(descripcion), precio(precio), proveedor(proveedor) {}
    
        int getCodigo() const 
        {
            return codigo;
        }
    
        string getNombre() const 
        {  
            return nombre;
        }
    
        string getDescripcion() const 
        {
            return descripcion;
        }
    
        double getPrecio() const 
        {
            return precio;
        }
    
        string getProveedor() const 
        {
            return proveedor;
        }
    
        void mostrarProducto() const 
        {
            cout << "Codigo: " << codigo << endl;
            cout << "Nombre: " << nombre << endl; 
            cout << "Descripcion: " << descripcion << endl;
            cout << "Precio: $" << precio << endl;
            cout << "Proveedor: " << proveedor << endl;
        }
};

class Cliente 
{
    private:
        string nombre;
        string direccion;
        int telefono;
        vector<Venta*> ventasRealizadas;  // Venta es usado antes de su definición completa
    
    public:
        Cliente(string nombre, string direccion, int telefono)
        : nombre(nombre), direccion(direccion), telefono(telefono) {}
    
        string getNombre() const 
        {
            return nombre;
        }
    
        void realizarCompra(Venta* venta) 
        {
            ventasRealizadas.push_back(venta);
        }
    
        void mostrarCompras() const;  // Declaración anticipada del método
};

class Pago 
{
    private:
        Cliente* cliente;
        double monto;
        string metodoPago;
        string fechaPago;
    
    public:
        Pago(Cliente* cliente, double monto, string metodoPago, string fechaPago)
        : cliente(cliente), monto(monto), metodoPago(metodoPago), fechaPago(fechaPago) {}
    
        void mostrarPago() const 
        {
            cout << "\nPago realizado por: " << cliente->getNombre() << endl;
            cout << "Monto: $" << monto << endl;
            cout << "Metodo de pago: " << metodoPago << endl;
            cout << "Fecha de pago: " << fechaPago << endl;
        }
};

class Venta 
{
    private:
        int numeroFactura;
        string fecha;
        Cliente* cliente;
        vector<Producto*> productosVendidos;
    
    public:
        Venta(int numeroFactura, string fecha, Cliente* cliente)
        : numeroFactura(numeroFactura), fecha(fecha), cliente(cliente) {}
    
        void agregarProducto(Producto* producto) 
        {
            productosVendidos.push_back(producto);
        }
    
        void mostrarDetalle() const 
        {
            cout << "\n--- Detalles de la Venta ---" << endl;
            cout << "\nFactura N°: " << numeroFactura << endl;
            cout << "Fecha: " << fecha << endl;
            cout << "Cliente: " << cliente->getNombre() << endl;
            cout << "Productos vendidos: " << endl;
            double total = 0;
            for (Producto* producto : productosVendidos) 
            {
                producto->mostrarProducto();
                total += producto->getPrecio();
            }
            cout << "\nTotal de la venta: $" << total << endl;
        }
    
        double calcularTotal() const 
        {
            double total = 0;
            for (Producto* producto : productosVendidos) 
            {
                total += producto->getPrecio();
            }
            return total;
        }
};

// Definición completa de la función mostrarCompras de Cliente
void Cliente::mostrarCompras() const 
{
    cout << "\nCompras realizadas por " << nombre << endl;
    for (Venta* venta : ventasRealizadas) 
    {
        venta->mostrarDetalle();
    }
}

int main() {
    vector<string> menuPrincipal = 
    {
        "1. Registrar Cliente",
        "2. Agregar Producto",
        "3. Realizar Venta",
        "4. Mostrar Compras de Cliente",
        "5. Registrar Pago",
        "6. Salir"
    };

    int opcion;
    string nombreCliente, direccionCliente, metodoPago, fechaPago;
    string descripcionProducto, nombreProducto, proveedor;
    int telefonoCliente, codigoProducto, numeroFactura;
    double precioProducto;
    Cliente* cliente = nullptr;
    Producto* producto = nullptr;
    Venta* venta = nullptr;

    vector<Cliente*> clientes;
    vector<Producto*> productos;

    do {
        cout << "\nBienvenido al sistema de gestión de tienda de ropa!" << endl;
        
        for (const string& opcionMenu : menuPrincipal) 
        {
            cout << opcionMenu << endl;
        }
        
        cout << "\nSeleccione una opción: ";
        cin >> opcion;

        switch (opcion) 
        {
            case 1: 
            {
                cout << "\nRegistrar nuevo Cliente." << endl;
                cout << "Ingrese su nombre: ";
                cin.ignore();
                getline(cin, nombreCliente);
                cout << "Ingrese su dirección: ";
                getline(cin, direccionCliente);
                cout << "Ingrese su teléfono: ";
                cin >> telefonoCliente;
                cliente = new Cliente(nombreCliente, direccionCliente, telefonoCliente);
                clientes.push_back(cliente);
                break;
            }

            case 2:
            {
                cout << "\nAgregar nuevo Producto." << endl;
                cout << "Ingrese el código del producto: ";
                cin >> codigoProducto;
                cout << "Ingrese el nombre del producto: "; 
                cin.ignore();
                getline(cin, nombreProducto);  // Debes leer el nombre antes
                cout << "Ingrese la descripción del producto: ";
                getline(cin, descripcionProducto);
                cout << "Ingrese el precio del producto: ";
                cin >> precioProducto;
                cout << "Ingrese el proveedor del producto: ";
                cin.ignore();
                getline(cin, proveedor);
                producto = new Producto(codigoProducto, nombreProducto, descripcionProducto, precioProducto, proveedor);
                productos.push_back(producto);
                break;
            }

            case 3: 
            {
                cout << "\nRealizar Venta." << endl;
                cout << "Ingrese el número de factura: ";
                cin >> numeroFactura;
                cout << "Ingrese la fecha de la venta (DD/MM/YYYY): ";
                string fechaVenta;
                cin.ignore();
                getline(cin, fechaVenta);
                
                cout << "Seleccione al cliente (por nombre): ";
                string nombre;
                getline(cin, nombre);
                for (Cliente* c : clientes) 
                {
                    if (c->getNombre() == nombre) 
                    {
                        cliente = c;
                        break;
                    }
                }

                venta = new Venta(numeroFactura, fechaVenta, cliente);
                
                int cantidadProductos;
                cout << "\n¿Cuántos productos desea agregar a la venta? ";
                cin >> cantidadProductos;
                for (int i = 0; i < cantidadProductos; i++) 
                {
                    cout << "Ingrese el código del producto: ";
                    int codigo;
                    cin >> codigo;
                    for (Producto* p : productos) 
                    {
                        if (p->getCodigo() == codigo) 
                        {
                            venta->agregarProducto(p);
                            break;
                        }
                    }
                }

                cliente->realizarCompra(venta);
                venta->mostrarDetalle();
                break;
            }

            case 4: 
            {
                cout << "\nMostrar Compras de Cliente." << endl;
                cout << "Ingrese el nombre del cliente: ";
                string nombreCliente;
                cin.ignore();
                getline(cin, nombreCliente);
                for (Cliente* c : clientes) 
                {
                    if (c->getNombre() == nombreCliente) 
                    {
                        c->mostrarCompras();
                        break;
                    }
                }
                break;
            }

            case 5: 
            {
                cout << "\nRegistrar Pago." << endl;
                cout << "Ingrese el nombre del cliente: ";
                string clienteNombre;
                cin.ignore();
                getline(cin, clienteNombre);
                for (Cliente* c : clientes) 
                {
                    if (c->getNombre() == clienteNombre) 
                    {
                        cout << "Ingrese el monto del pago: ";
                        double monto;
                        cin >> monto;
                        cout << "Ingrese el método de pago: ";
                        string metodo;
                        cin.ignore();
                        getline(cin, metodo);
                        cout << "Ingrese la fecha del pago (DD/MM/YYYY): ";
                        string fecha;
                        getline(cin, fecha);
                        Pago* pago = new Pago(c, monto, metodo, fecha);
                        pago->mostrarPago();
                        break;
                    }
                }
                break;
            }

            case 6: 
            {
                cout << "Saliendo del sistema..." << endl;
                break;
            }
        }
    } while (opcion != 6);

    return 0;
}
