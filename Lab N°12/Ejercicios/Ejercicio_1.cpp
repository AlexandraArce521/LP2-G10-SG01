

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
};


int main()
{
    vector<Producto> productos;
    productos.push_back({"Laptop", 123456, "Laptop de última generación", 10});
    productos.push_back({"Smartphone", 789101, "Teléfono inteligente", 50});
    productos.push_back({"Tablet", 112233, "Tablet de 10 pulgadas", 20});
    
    vector <string> menu = {"____________________________________________________",
                            "1. Agregar un nuevo producto", 
                            "2. Actualizar la cantidad disponible",
                            "3. Buscar un producto por su codigo",
                            "4. Mostrar la lista de productos ordenados \n  alfabeticamente por su descripción",
                            "____________________________________________________"};
    
    int respuesta = 0;
    
    for (auto& m: menu) {
        cout << m << endl;
    };
    
    cout << "Elegir una opción: ";
    cin >> respuesta;
    
    switch (respuesta) {
        
        case 1:
            
            long nuevoCodigo;
            
            cout << "Ingrese el codigo: ";
            cin << nuevoCodigo;
            
            if(codigo.find(nuevoCodigo)) {
                cout << "(!) EL codigo ingresado pertenece a otro producto\n"
                break;
            }
    
    }

    return 0;
}
