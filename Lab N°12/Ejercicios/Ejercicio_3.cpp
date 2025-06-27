

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

struct Contacto {
    string nombre;
    long numero;
    string correo;
};

void mostrarContactos(const Contacto& contac) {
    cout << "\nNombre: " << contac.nombre << endl;
    cout << "Número: " << contac.numero << endl;
    cout << "Correo: " << contac.correo << endl;
    cout << endl;
        
};


int main()
{
    string nuevoNombre;
    long nuevoNumero;
    string nuevoCorreo;    
    
    vector<Contacto> contactos;
    
    contactos.push_back({"Juan", 9878921345, "Juan@yahoo.com"});
    contactos.push_back({"Mariela", 932765623, "Mariela@hotmail.com"});
    contactos.push_back({"Vargas", 970810306, "Vargas@gmail.com"});
        
    
    vector <string> menu = {"\n____________________________________________________",
                            "\n1. Agregar un nuevo contacto", 
                            "2. Buscar un contacto por su nombre",
                            "3. Actualizar la información de un contacto existente",
                            "4. Mostrar la lista de contactos ordenada alfabéticamente",
                            "5. Salir",
                            "____________________________________________________"};
    while (true) {
        
        int respuesta = 0;
        
        for (auto& m: menu) {
            cout << m << endl;
        };
        
        cout << "Elegir una opción: ";
        cin >> respuesta;
        
        switch (respuesta) {
            case 1: {
                
                cout << "Ingrese el número de telefono: ";
                cin >> nuevoNumero;
                
                bool existe = false;
                for (auto& contac : contactos) {
                    if (nuevoNumero == contac.numero) {
                        cout << "(!) El número pertenece a " << contac.nombre << endl;
                        cout << "Intente nuevamente\n";
                        existe = true;
                        break;
                    }
                }
            
                if (existe) break;
                
                cin.ignore();
                
                cout << "Ingrese el nombre para el contacto: ";
                getline(cin, nuevoNombre);
                
                cout << "Ingrese el correo electronico para el contacto: ";
                getline(cin, nuevoCorreo); 
                
                try{
                    
                    contactos.push_back({nuevoNombre, nuevoNumero, nuevoCorreo});
                    cout << "Contacto agregado correctamente.\n";
                    
                } 
                catch (...) {
                    cout << "(!) Error inesperado. Intente más tarde\n";
                }
               
                break; //case 1  
            }//fin de case 1
            
            case 2: {

                cin.ignore();
                
                cout << "Ingrese el nombre del contacto: ";
                getline(cin, nuevoNombre);                
                
                bool existe = false;
                for (auto& contac : contactos) {
                    if (nuevoNombre == contac.nombre) {
                        mostrarContactos(contac);
                        existe = true;
                        break;
                    }
                }
                if (!existe) {
                    cout << "(!) Contacto no encontrado\n";
                    break;
                }
                
                break;//case 2
                
            }// fin de case 2

            case 3: {

                cin.ignore();

                cout << "Ingrese el nombre del contacto: ";
                getline(cin, nuevoNombre);       
                
                bool existe = false;
                for (auto& contac : contactos) {
                    if (nuevoNombre == contac.nombre) {
                        cout << "Ingrese el nuevo numero de contacto: ";
                        cin >> nuevoNumero;
                        
                        cin.ignore();
                        
                        cout << "Ingrese el nuevo correo del contacto: ";
                        getline(cin, nuevoCorreo);  
                        
                        contac.numero = nuevoNumero;
                        contac.correo = nuevoCorreo;
                        
                        cout << "\nInformación actualizada\n";
                        existe = true;
                        break;
                    }
                }
                if (!existe) {
                    cout << "(!) Contacto no encontrado\n";
                    break;
                }
                


                break;//case 3
                
            }// fin case 3 

            case 4: {
                
                sort(contactos.begin(), contactos.end(), [] (Contacto& a, Contacto& b) {
                    return a.nombre < b.nombre;
                });
                cout << "\n____________________________________________________\n";               
                cout << "Lista de contactos\n";

                for( auto& contac : contactos) {
                    mostrarContactos(contac);
                }

                break; //case 4
            }// fin case 4 
            
            case 5: {
                cout << "Saliendo del Menú...\n";
                return 0;           
            }//fin de case 5
            
            default:{
                cout << "(!) Opción inválida. Intente nuevamente.\n";
            }


        }//fin de switch case
    };

    return 0;
}
