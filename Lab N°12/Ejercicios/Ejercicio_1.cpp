#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

struct Producto {
    string nombre;
    long codigo;
    string descripcion;
    int cantidad;
};

void mostrarLista(const Producto& p) {
        cout << "Nombre: " << p.nombre<< endl;
        cout << "Código: " << p.codigo << endl;
        cout << "Descripción: " << p.descripcion << endl;
        cout << "Cantidad: " << p.cantidad << endl;
        cout << endl;
};

int main()
{
    string nuevoNombre;
    long codigoNuevo;
    string descripcionNuevo;
    int cantidadNuevo;
    
    vector<Producto> productos;
    productos.push_back({"Laptop", 123456, "Laptop de última generación", 10});
    productos.push_back({"Smartphone", 789101, "Teléfono inteligente", 50});
    productos.push_back({"Tablet", 112233, "Tablet de 10 pulgadas", 20});
    
    vector <string> menu = {"____________________________________________________",
                            "\n1. Agregar un nuevo producto", 
                            "2. Actualizar la cantidad disponible",
                            "3. Buscar un producto por su codigo",
                            "4. Mostrar la lista de productos ordenados \n  alfabeticamente por su descripción",
                            "____________________________________________________"};
    
    while(true) {
        
        int respuesta = 0;
        for (auto& m: menu) {
            cout << m << endl;
        };
        
        cout << "Elegir una opción: ";
        cin >> respuesta;
        
        switch (respuesta) {
            
            case 1: {
                
                cout << "Ingrese el codigo: ";
                cin >> codigoNuevo;
                
                bool existe = false;
                for (const auto& prod : productos) {
                    if (prod.codigo == codigoNuevo) {
                        existe = true;
                        break;
                    }
                }
            
                if (existe) {
                    cout << "(!) Producto existente en el Inventario\n";
                    break;
                }
                        cin.ignore();

                        cout << "Ingrese el nombre: ";
                        getline(cin, nuevoNombre);

                        cout << "Ingrese una descripcion: ";
                        getline(cin, descripcionNuevo);

                        cout << "Ingrese la cantidad del producto nuevo: ";
                        cin >> cantidadNuevo;

                        try{
                            productos.push_back({nuevoNombre, codigoNuevo, descripcionNuevo, cantidadNuevo});
                        }
                        catch (...) {
                            cout << "(!) Error inesperado, intente más tarde\n";
                            break;
                        }       
                break;
            } 
            
            case 2: {
                
                cout << "Ingrese el codigo del producto: ";
                cin >> codigoNuevo;
                
                bool existe = false;
                for( auto& prod : productos) {
                    if(prod.codigo == codigoNuevo) {
                        cout << "Cantidad actual de " << prod.nombre << " es " << prod.cantidad << endl;
                        cout << "Ingrese la nueva cantidad: ";
                        cin >> cantidadNuevo;
                        prod.cantidad = cantidadNuevo;
                        existe = true;
                        break;
                    } 
                }    
                if(!existe) {
                    cout << "(!) Producto no encontrado. Intente de nuevo\n";
                    break;
                }
                break;
            }
            
            case 3: {
                    cout << "Ingrese el codigo del producto: ";
                    cin >> codigoNuevo;
                    
                    bool existe = false;
                    for( auto& prod : productos) {
                        if(prod.codigo == codigoNuevo) {
                            cout << "____________________________________________________\n";
                            mostrarLista(prod);
                            cout << "____________________________________________________\n";
                            existe = true;
                        }            
                    }
                    
                    if(!existe) {
                        cout << "(!) Producto no encontrado. Intente de nuevo\n";
                        break;
                    }
                break;
            }// fin case 3  
            
            case 4: {
                sort(productos.begin(), productos.end(), [](const Producto& a, const Producto& b) {
                    return a.descripcion < b.descripcion;
                }); 
                
                cout << "____________________________________________________\n";
                cout << "           Información ordenada alfabeticamente                \n";  
                
                for(auto& prod : productos ) {
                    mostrarLista(prod);
                }
            }
            default:{
                cout << "(!) Opción inválida. Intente nuevamente.\n";
            }

        }//fin del switch
        
    }// Fin del while

    return 0;
}
