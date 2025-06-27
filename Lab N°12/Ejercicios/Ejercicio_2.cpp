#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

struct Evento {
    string nombre;
    string fecha;
    set<string> asistentes;
};

void mostrarEvento(Evento& ev) {
    cout << "\nFecha del evento: " << ev.fecha << endl;
    cout << "Nombre del evento: " << ev.nombre << endl;
    cout << "Asistentes del evento: " << endl;
    for (auto& a: ev.asistentes ) {
        cout <<".- "<< a  << endl;
    }
};

void mostrarAsistentes(Evento& ev) {
    cout << "Asistentes del evento: " << endl;
    for (auto& a: ev.asistentes ) {
        cout <<".- "<< a  << endl;
    }
};


int main()
{ 
    string nuevoNombre;
    string nuevaFecha;
    
    vector<Evento> eventos = {
        {"Conferencia de Tecnología", "2025-07-15", {"Ana Torres", "Carlos Ruiz", "Jose Manuel"}},
        {"Feria de Emprendimiento", "2025-08-01", {"Elena Mendoza", "Mario Gómez", "María Jose"}},
        {"Taller de Programación", "2025-09-10", {"Luis Pérez", "Andrea Ríos", "Camila de la Cruz"}}
    };
    
    vector <string> menu = {"____________________________________________________",
                            "\n1. Agregar un nuevo evento a la lista", 
                            "2. Agregar asistentes a un evento específico",
                            "3. Mostrar la lista de asistentes de un evento en orden alfabético",
                            "4. Buscar eventos por fecha.",
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
                
                cin.ignore();

                cout << "Fecha del evento (ej. 2025-06-26): ";
                getline(cin, nuevaFecha);    
                
                bool existe = false;
                for (const auto& ev : eventos) {
                    if (ev.fecha == nuevaFecha) {
                        existe = true;
                        break;
                    }
                }
                
                if (existe) {
                    cout << "(!) Evento para esa fecha\n";
                    break;
                }  
                
                cout << "Ingrese el nombre del evento: ";
                getline(cin, nuevoNombre);

                try{
                    eventos.push_back({nuevoNombre, nuevaFecha});
                    cout << "Evento agregado correctamente.\n";
                    break;
                }
                catch (...) {
                    cout << "(!) Error inesperado, intente más tarde\n";
                    break;
                }
                
            }//fin de case 1
            
            case 2: {
                
                int cantidad = 0;
                string asistente, nuevaFecha;
            
                cin.ignore(); 
            
                cout << "Fecha del evento (ej. 2025-06-26): ";
                getline(cin, nuevaFecha);  
            
                bool encontrado = false;
            
                for (auto& ev : eventos) {
                    if (ev.fecha == nuevaFecha) {
                        encontrado = true;
            
                        cout << "Cantidad de asistentes a registrar: ";
                        cin >> cantidad;
                        cin.ignore(); 
            
                        for (int i = 0; i < cantidad; ++i) {
                            cout << "Ingrese los Apellidos y Nombres del asistente #" << i + 1 << ": ";
                            getline(cin, asistente);
                            ev.asistentes.insert(asistente); 
                        }
                        cout << "Asistentes registrados correctamente.\n";
                        break; 
                    }
                }
            
                if (!encontrado) {
                    cout << "(!) No hay evento registrado para esa fecha.\n";
                }
                break;
            }// fin de case 2

            case 3: {
                    cout << "Ingrese la fecha del evento: ";
                    cin >> nuevaFecha;
                    
                    bool existe = false;
                    for( auto& ev : eventos) {
                        if(ev.fecha == nuevaFecha) {
                            cout << "____________________________________________________\n";
                            mostrarAsistentes(ev);
                            cout << "____________________________________________________\n";
                            existe = true;
                        }            
                    }
                    
                    if(!existe) {
                        cout << "(!) Evento no encontrado. Intente de nuevo\n";
                        break;
                    }
                break;
            }// fin case 3 

            case 4: {
                    cout << "Ingrese la fecha del evento: ";
                    cin >> nuevaFecha;
                    
                    bool existe = false;
                    for( auto& ev : eventos) {
                        if(ev.fecha == nuevaFecha) {
                            cout << "____________________________________________________\n";
                            mostrarEvento(ev);
                            cout << "____________________________________________________\n";
                            existe = true;
                        }            
                    }
                    
                    if(!existe) {
                        cout << "(!) Evento no encontrado. Intente de nuevo\n";
                        break;
                    }
                break;
            }// fin case 4 
            
            case 5: {
                cout << "Saliendo del Menú...\n";
                break;                
            }//fin de case 5
            
            default:{
                cout << "(!) Opción inválida. Intente nuevamente.\n";
            }

        }//fin de switch case
    };

    return 0;
}
