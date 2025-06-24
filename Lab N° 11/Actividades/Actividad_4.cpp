#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<stdexcept>
using namespace std;

class Producto
{
    private:
    string nombre;
    double precio;
    int cantidad;

    public:
    Producto(string nombre, double precio, int cantidad) : nombre(nombre), precio(precio), cantidad(cantidad) {}
    string getNombre() const { return nombre; }
    double getPrecio() const { return precio; }
    int getCantidad() const { return cantidad; }
    void setPrecio(double p) { precio = p; }
    void setCantidad(int c) { cantidad = c; }
    
    void informacion() const 
    {
        cout << "Nombre: " << getNombre() << "\n"
             << "Precio: " << getPrecio() << "\n"
             << "Cantidad: " << getCantidad() << "\n";
    }
    virtual ~Producto() {}
};

class Registrar_Producto : protected Producto
{
    public:
    Registrar_Producto(string n, double p, int c) : Producto(n, p, c) {}
    
    void escribir() const
    {
        ofstream archivo;
        archivo.open("registro_producto.txt", ios::app);
        if(archivo.fail())
        {
            cout << "No se pudo abrir el archivo\n";
            return;
        }
        
        archivo << "Nombre: " << getNombre() << "\n";
        archivo << "Precio: " << getPrecio() << "\n";
        archivo << "Cantidad: " << getCantidad() << "\n";
        archivo << "-------------------\n";
        archivo.close();
        cout << "Producto registrado exitosamente\n";
    }
};

class Actualizar_informacion : protected Producto
{
    private:
    string nombreBuscar;
    double nuevoPrecio;
    int nuevaCantidad;

    public:
    Actualizar_informacion(string n, double p, int c) : Producto("", 0, 0), nombreBuscar(n), nuevoPrecio(p), nuevaCantidad(c) {}
    
    bool actualizar()
    {
        ifstream archivoLeer("registro_producto.txt");
        ofstream archivoTemp("temp.txt");
        
        if(archivoLeer.fail() || archivoTemp.fail())
        {
            cout << "Error al abrir archivos\n";
            return false;
        }
        
        string linea;
        bool encontrado = false;
        
        while(getline(archivoLeer, linea))
        {
            if(linea.find("Nombre: " + nombreBuscar) != string::npos)
            {
                encontrado = true;
                archivoTemp << linea << "\n";
                getline(archivoLeer, linea); // Saltar línea de precio actual
                archivoTemp << "Precio: " << nuevoPrecio << "\n";
                getline(archivoLeer, linea); // Saltar línea de cantidad actual
                archivoTemp << "Cantidad: " << nuevaCantidad << "\n";
            }
            else
            {
                archivoTemp << linea << "\n";
            }
        }
        
        archivoLeer.close();
        archivoTemp.close();
        
        if(encontrado)
        {
            remove("registro_producto.txt");
            rename("temp.txt", "registro_producto.txt");
            cout << "Producto actualizado exitosamente\n";
            return true;
        }
        else
        {
            remove("temp.txt");
            cout << "Producto no encontrado\n";
            return false;
        }
    }
};

class Venta_producto : protected Producto
{
    private:
    string nombreProducto;
    int cantidadVendida;

    public:
    Venta_producto(string n, int cantVenta) : Producto("", 0, 0), nombreProducto(n), cantidadVendida(cantVenta) {}
    
    bool vender()
    {
        ifstream archivoLeer("registro_producto.txt");
        ofstream archivoTemp("temp.txt");
        
        if(archivoLeer.fail() || archivoTemp.fail())
        {
            cout << "Error al abrir archivos\n";
            return false;
        }
        
        string linea;
        bool encontrado = false;
        
        while(getline(archivoLeer, linea))
        {
            if(linea.find("Nombre: " + nombreProducto) != string::npos)
            {
                encontrado = true;
                archivoTemp << linea << "\n";
                
                // Leer precio
                getline(archivoLeer, linea);
                archivoTemp << linea << "\n";
                
                // Leer y actualizar cantidad
                getline(archivoLeer, linea);
                size_t pos = linea.find(": ");
                if(pos != string::npos)
                {
                    int cantidadActual = stoi(linea.substr(pos + 2));
                    if(cantidadActual >= cantidadVendida)
                    {
                        int nuevaCantidad = cantidadActual - cantidadVendida;
                        archivoTemp << "Cantidad: " << nuevaCantidad << "\n";
                        cout << "Venta realizada. Cantidad restante: " << nuevaCantidad << "\n";
                    }
                    else
                    {
                        archivoTemp << linea << "\n";
                        cout << "Stock insuficiente. Cantidad disponible: " << cantidadActual << "\n";
                        archivoLeer.close();
                        archivoTemp.close();
                        remove("temp.txt");
                        return false;
                    }
                }
            }
            else
            {
                archivoTemp << linea << "\n";
            }
        }
        
        archivoLeer.close();
        archivoTemp.close();
        
        if(encontrado)
        {
            remove("registro_producto.txt");
            rename("temp.txt", "registro_producto.txt");
            return true;
        }
        else
        {
            remove("temp.txt");
            cout << "Producto no encontrado\n";
            return false;
        }
    }
};

class Informe
{
    public:
    void informacion() 
    {
        ifstream archivo;
        archivo.open("registro_producto.txt", ios::in);
        if(archivo.fail())
        {
            cout << "No se pudo abrir el archivo o no hay productos registrados\n";
            return;
        }
        
        string linea;
        cout << "\n=== INFORME DE PRODUCTOS ===\n";
        while(getline(archivo, linea))
        {
            cout << linea << "\n";
        }
        archivo.close();
    }
};

int main()
{
    string opcion = "s";
    int alternativa;
    
    do
    {   
        cout << "\n=== MENU DE OPCIONES ===\n";
        cout << "1. Registrar producto\n";
        cout << "2. Actualizar informacion\n";
        cout << "3. Venta de producto\n";
        cout << "4. Informe\n";
        cout << "5. Salir\n";
        
        try
        {
            cout << "Ingrese una opcion: ";
            cin >> alternativa;
            
            if(cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                throw runtime_error("No ingreso un numero entero valido");
            }
            
            switch (alternativa)
            {
                case 1:
                {
                    string nom;
                    double pre;
                    int can;
                    
                    cout << "Ingrese el nombre del producto: ";
                    cin.ignore();
                    getline(cin, nom);
                    cout << "Ingrese el precio del producto: ";
                    cin >> pre;
                    cout << "Ingrese la cantidad del producto: ";
                    cin >> can;
                    
                    if(pre < 0 || can < 0)
                    {
                        cout << "Error: Precio y cantidad deben ser valores positivos\n";
                        break;
                    }
                    
                    Registrar_Producto registro(nom, pre, can);
                    registro.escribir();
                }
                break;
                
                case 2:
                {
                    cout << "Actualizar informacion del producto\n";
                    string nom;
                    double pre;
                    int can;
                    
                    cout << "Ingrese el nombre del producto a actualizar: ";
                    cin.ignore();
                    getline(cin, nom);
                    cout << "Ingrese el nuevo precio: ";
                    cin >> pre;
                    cout << "Ingrese la nueva cantidad: ";
                    cin >> can;
                    
                    if(pre < 0 || can < 0)
                    {
                        cout << "Error: Precio y cantidad deben ser valores positivos\n";
                        break;
                    }
                    
                    Actualizar_informacion actualizar(nom, pre, can);
                    actualizar.actualizar();
                }
                break;
                
                case 3:
                {
                    cout << "Venta de producto\n";
                    string nomProducto;
                    int cantVenta;
                    
                    cout << "Ingrese el nombre del producto a vender: ";
                    cin.ignore();
                    getline(cin, nomProducto);
                    cout << "Ingrese la cantidad a vender: ";
                    cin >> cantVenta;
                    
                    if(cantVenta <= 0)
                    {
                        cout << "Error: La cantidad debe ser mayor a 0\n";
                        break;
                    }
                    
                    Venta_producto venta(nomProducto, cantVenta);
                    venta.vender();
                }
                break;
                
                case 4:
                {
                    Informe informe;
                    informe.informacion();
                }
                break;
                
                case 5:
                {
                    cout << "Saliendo del programa...\n";
                    opcion = "n";
                    continue;
                }
                break;
                
                default:
                {
                    cout << "Opcion no valida. Intente nuevamente.\n";
                }
                break;
            }
        }
        catch (const exception& e)
        {
            cout << "ERROR: " << e.what() << "\n";
        }
        
        if(opcion != "n")
        {
            cout << "Desea continuar? (s/n): ";
            cin >> opcion;
            
            try 
            {
                if (opcion != "s" && opcion != "S" && opcion != "n" && opcion != "N") 
                {
                    throw runtime_error("Opcion no valida, se continuara por defecto");
                }
            }
            catch (const runtime_error& e)       
            {
                cout << "Excepcion: " << e.what() << "\n";
                opcion = "s"; // Continuar por defecto
            }
        }
        
    } while(opcion == "s" || opcion == "S"); 
    
    return 0;
}
