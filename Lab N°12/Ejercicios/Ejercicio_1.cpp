#include <iostream>
#include <set>
#include <vector>
using namespace std;

struct Inventario {
    string codigo;
    string descripcion;
    int cantidad;
};

int main()
{
    vector <string> menu = {"____________________________________________________",
                            "1. Agregar un nuevo producto", 
                            "2. Actualizar la cantidad disponible",
                            "3. Buscar un producto por su codigo",
                            "4. Mostrar la lista de productos ordenados \n  alfabeticamente por su descripción",
                            "____________________________________________________"};
    
    for (auto& m: menu) {
        cout << m << endl;
    };
        
    
    return 0;
}

