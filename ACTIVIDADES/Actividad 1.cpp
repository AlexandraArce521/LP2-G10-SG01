#include <iostream>
#include <list>
#include <string>

using namespace std;

void funcionEmpleado();
void funcionCliente();

struct Inventario {
    string nombreProduc;
    float Precio;
    int Cantidad;
    string Descrip;
};

Inventario grupo[3];
int sumaProduct = 0;

int main() {
    int TipoUsuario = 0;

    while (true) {
        cout << "\n----BIENVENIDO----\n";
        cout << "1. Empleado\n2. Cliente\n3. Salir\n";
        cout << "Ingrese qué tipo de usuario es: ";
        cin >> TipoUsuario;

        if (TipoUsuario == 1) {
            funcionEmpleado();
        } else if (TipoUsuario == 2) {
            funcionCliente();
        } else if (TipoUsuario == 3) {
            cout << "Saliendo del programa..." << endl;
            break;
        } else {
            cout << "Usuario no válido. Intente nuevamente." << endl;
        }
    }

    return 0;
}

void funcionEmpleado() {
    list<string> menuEmpleado = {
        "Menú (EMPLEADOS)",
        "1. Ver Productos",
        "2. Agregar Nuevos Productos",
        "3. Reporte General",
        "4. Salir"
    };

    int opcEm, limitProduct = 3;

    while (true) {
        cout << "\n";
        for (const string& opcion : menuEmpleado) {
            cout << opcion << endl;
        }

        cout << "Elija una opción: ";
        cin >> opcEm;
        cout << "\n";

        switch (opcEm) {
            case 1: {
                cout << "---- Inventario ----\n";
                for (int i = 0; i < sumaProduct; i++) {
                    cout << "Producto: " << grupo[i].nombreProduc
                         << ", Cantidad: " << grupo[i].Cantidad
                         << ", Precio: " << grupo[i].Precio << "$" << endl;
                    }
                    break;
                }

            case 2: {
                if (sumaProduct >= limitProduct) {
                    cout << "Error: Capacidad máxima del inventario alcanzada." << endl;
                    break;
                }

                int cantidadProduct;
                cout << "¿Cuántos productos va a ingresar? ";
                cin >> cantidadProduct;

                if (sumaProduct + cantidadProduct > limitProduct) {
                    cout << "Solo puede ingresar " << limitProduct - sumaProduct << " productos más." << endl;
                    cantidadProduct = limitProduct - sumaProduct;
                }

                for (int a = 0; a < cantidadProduct; a++) {
                    
                    if (sumaProduct >= limitProduct) {
                        cout << "Error!: Capacidad máxima del inventario alcanzada." << endl;
                        break;
                    }
                    
                    cout << "Ingrese el NOMBRE del producto: ";
                    cin >> grupo[sumaProduct].nombreProduc;

                    cout << "Ingrese el PRECIO del producto: ";
                    cin >> grupo[sumaProduct].Precio;

                    cout << "Ingrese la CANTIDAD del producto: ";
                    cin >> grupo[sumaProduct].Cantidad;

                    cout << "Ingrese una pequeña DESCRIPCIÓN del producto: ";
                    cin >> grupo[sumaProduct].Descrip;

                    sumaProduct++;
                }
                break;
            }

            case 3: {
                float saldoTotal = 0;
                cout << "---- REPORTE GENERAL ----\n";
                cout << "1. Cantidad total de productos: " << sumaProduct << "\n";
                cout << "2. Detalle de los productos:\n";
                for (int i = 0; i < sumaProduct; i++) {
                    cout << "- " << grupo[i].nombreProduc
                         << ", Precio: " << grupo[i].Precio << "$"
                         << ", Cantidad: " << grupo[i].Cantidad << endl;
                    saldoTotal += grupo[i].Precio * grupo[i].Cantidad;
                }
                cout << "3. Valor total del inventario: " << saldoTotal << "$" << endl;
                break;
            }

            case 4: {
                cout << "Cerrando sistema de empleados..." << endl;
                return;
            }

            default: {
                cout << "Opción no válida. Inténtelo de nuevo." << endl;
                break;
            }
        }
    }
}

void funcionCliente() {
    list<string> menuCliente = {
        "Menú (CLIENTE)",
        "1. Ver Productos",
        "2. Hacer Pedido",
        "3. Salir"
    };

    int opcCli;

    while (true) {
        cout << "\n";
        for (const string& opcion : menuCliente) {
            cout << opcion << endl;
        }

        cout << "Elija una opción: ";
        cin >> opcCli;
        cout << "\n";

        switch (opcCli) {
            case 1: {
                cout << "---- PRODUCTOS DISPONIBLES ----\n";
                for (int i = 0; i < sumaProduct; i++) {
                    cout << i + 1 << ". " << grupo[i].nombreProduc
                         << " -> Precio: " << grupo[i].Precio << "$" << endl;
                }
                break;
            }

            case 2: {
                int cantidadSolicitada;
                float totalPagar = 0;

                cout << "¿Cuántos productos desea comprar? ";
                cin >> cantidadSolicitada;

                for (int j = 0; j < cantidadSolicitada; j++) {
                    string nombreProductoSolicitado;
                    int cantidadProducto;
                    bool productoEncontrado = false;

                    cout << "¿Qué producto desea? ";
                    cin >> nombreProductoSolicitado;

                    cout << "¿Cuántas unidades desea? ";
                    cin >> cantidadProducto;

                    for (int i = 0; i < sumaProduct; i++) {
                        if (nombreProductoSolicitado == grupo[i].nombreProduc) {
                            if (grupo[i].Cantidad >= cantidadProducto) {
                                float costoProducto = cantidadProducto * grupo[i].Precio;
                                totalPagar += costoProducto;
                                grupo[i].Cantidad -= cantidadProducto;
                            }
                            productoEncontrado = true;
                            break;
                        }
                    }
                }
                cout << "\nTotal a pagar: " << totalPagar << "$" << endl;
                break;
            }

            case 3: {
                cout << "Saliendo del sistema de clientes..." << endl;
                return;
            }
        }
    }
}


