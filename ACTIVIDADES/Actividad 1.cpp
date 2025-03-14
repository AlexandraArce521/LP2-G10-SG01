#include <iostream>
#include <list>
#include <string>

using namespace std;

void AgregarProduct (void);

int main()
{
    int TipoPer = 0;
    list <string> lista1;
    int opcionEm;

    
    lista1 = {"Menú (EMPLEADOS)","1. Ver Productos","2. Agregar nuevos productos","3. Reporte General","4. Ver Pedidos","5. Gestor de inventario"};
    
    cout << "Tipo de usuario:" << endl;
    cout << "1. Empleado" << endl;
    cout << "2. Cliente" << endl;
    cout << "Eliga una opción: " << endl;
    cin >> TipoPer;
    
    do 
    {   //OPCIONES PARA EL EMPLEADO
        if(TipoPer == 1)
        {
            for(string elemento1: lista1)
                cout << elemento1 << endl;
            cout << "Eliga una opcion como EMPLEADO: " << endl;
            cin >> opcionEm;
            switch (opcionEm)   {
                case 1:
                   { struct Productos;
                        string nombre;
                        int cantidad;
                        float precio;
                   }
                break;
                
                case 2: 
                    AgregarProduct();
                break;
            }
        }
        
        
        //OPCIONES PARA EL CLIENTE
        if (TipoPer == 2)
        {
            
        }
    } while (TipoPer == 1 and TipoPer == 2);
       
}

void AgregarProduct (void)
    {
        int newProduct,cantidad;
        string product;
        float precio; 
        
        cout << "Ingrese la cantidad de productos nuevos: " <<endl;
        cin >> newProduct;
                    
        for(int i = 0; i < newProduct; i = i + 1)
            {
                cout << "Ingrese el NOMBRE del producto" << endl;
                cin >> product;
                cout << "Ingrese el PRECIO del producto: " << endl;
                cin >> precio;
                cout << "Ingrese la CANTIDAD del producto" << endl;
                cin >> cantidad;
            }  
    }

