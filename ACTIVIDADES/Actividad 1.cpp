#include <iostream>
#include <list>
#include <string>

using namespace std;

void funcionEmpleado ();
//void funcionCliente ();

struct Inventario {
    string nombreProduc;
    float Precio;
    int Cantidad;
    string Descrip;
};
 //Objeto 
Inventario grupo[3];
int main()
{
    
    int TipoUsuario = 0;
    
    cout << "Ingrese que tipo de empleado:" << endl;
    cin >> TipoUsuario;
    
    do
    {
        if (TipoUsuario == 1)
            funcionEmpleado();
            
        else if (TipoUsuario == 2)
            //funcionCliente();
            cout << "Eres cliente" << endl;
        else
           { 
            cout << "Usuario no encontrado" << endl;
            cout << "Incorrecto. Ingrese que tipo de empleado:" << endl;
            cin >> TipoUsuario;
           }
    } while (TipoUsuario >= 1 && TipoUsuario <= 3);
    return 0;
}

void funcionEmpleado()
{
    
    list <string> lista1;
    int opcEm, sumaProduct = 3, limitProduct = 10, cantidadProduct = 0;
    
    lista1 = {
            "Menú (EMPLEADOS)",
            "1. Ver Productos",
            "2. Agregar nuevos productos",
            "3. Reporte General",
            "4. Gestor de inventario"
    };
            
    for(string opcion: lista1)
        cout << opcion << endl;
            
    cout << "Eliga una opción: " << endl;
    cin >> opcEm;
    
    switch (opcEm) {
    case 1:
    {
        cout << "Inventario"<< endl;
        for (int i = 0; i < sumaProduct; i++ )
           {  
            cout << "Producto:" << grupo[i].nombreProduc << "," << "Cantidad" << grupo[i].Cantidad << "," << "Precio:"<< grupo[i].Precio<< endl;
           }
        break;
    }
    case 2:
    {
        cout << "¿Cúantos productos va a ingresar?" << endl;
        cin >> cantidadProduct;
        
        for (int a = 0; a < cantidadProduct; a++)
        {
            cout << "Ingrese el NOMBRE del producto: " << endl;
            cin >> grupo[a].nombreProduc;
            
            cout << "Ingrese el PRECIO del producto" << endl;
            cin >> grupo[a].Precio;
            
            cout << "Ingrese la CANTIDAD que guardará del producto: " << endl;
            cin >> grupo[a].Cantidad;
            
            cout << "Ingrese una pequeña DESCRIPCIÓN del producto:" << endl;
            cin >> grupo[a].Descrip;
        }
        break;
    }
    
    }
    
}

