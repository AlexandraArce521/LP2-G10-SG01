#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace std;

int main()
{
    fstream archivo;
    string nombre;
    string mensaje;
    cout << "Ingrese el nombre para su archivo. " << endl;
    getline(cin, nombre);
    archivo.open(nombre, ios::out);
    
    cout << "Escriba el texto:\n";
    getline(cin, mensaje);
    archivo << mensaje << endl;
    
    
    archivo.close();
    try
    {
        archivo.open(nombre, ios::in);
        
        cout << "\n====El texto almacenado en el archivo====\n";
        while(getline(archivo, mensaje)) {
            cout << mensaje << endl;
        }
        cout << "-------------------------------\n";
        archivo.close();
    }
    catch(ios_base::failure other)
    {
        cout << "(!)El archivo no existe\n";
        if (!archivo.good()) {
            cout << "Confirmado: El fallo se debe a un error en la apertura." << endl;
        }
        return 0;
    }
    
    catch(...)
    {
        cout << "(!)Error inesperado\n";
    }
    return 0;
}
