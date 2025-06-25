#include <fstream>  
#include <iostream>  
#include <stdexcept>  
#include <vector>
using namespace std;  


class Persona{
private:
    string nombre;
    int edad;
    string direccion;

public:
    Persona(string n, int e, string d)
     : nombre(n), edad(e), direccion(d) {}
    
    string getNombre() {return nombre;}
    int getEdad() {return edad;}
    string getDireccion() {return direccion;}
    
    void setNombre(string n) {
        if(n.length() > 0) {
            nombre = n;
        }
        else {
            cout << "(!)Sin nombre. Ingrese un nombre\n";
            exit(1);
        }
    }
    
    void setEdad(int e) {
        if(edad > 0) {
            edad = e;
        }
        else {
            cout << "(!)Edad no valida. Ingresar edad valida\n";
            exit(1);
        }
    }
    
    void setDireccion(string d) {
        if(d.length() > 0) {
            direccion = d;
        }
        else {
            cout << "(!)Sin nombre. Ingrese un nombre\n";
            exit(1);
        }
        
    }
    void mostrar() const {
        cout << "Nombre: " << nombre << endl;
        cout << "Edad: " << edad << endl;
        cout << "Direccion: " << direccion << endl;
    }
    
    void escribirArchivo(ofstream& archivo) {
        size_t lenNombre = nombre.size();
        size_t lenDireccion = direccion.size();
    
        archivo.write((char*)&lenNombre, sizeof(lenNombre));
        archivo.write((char*)nombre.c_str(), lenNombre);
    
        archivo.write((char*)&edad, sizeof(edad));
    
        archivo.write((char*)&lenDireccion, sizeof(lenDireccion));
        archivo.write((char*)direccion.c_str(), lenDireccion);
    }

    void leerArchivo(ifstream& archivo)  {
        size_t lenNombre, lenDireccion;
    
        archivo.read((char*)&lenNombre, sizeof(lenNombre));
        nombre.resize(lenNombre);
        archivo.read(&nombre[0], lenNombre);
    
        archivo.read((char*)&edad, sizeof(edad));
    
        archivo.read((char*)&lenDireccion, sizeof(lenDireccion));
        direccion.resize(lenDireccion);
        archivo.read(&direccion[0], lenDireccion);
    }
};

int main()
{   
    // Declarar vector de personas
    vector<Persona> personas;

    personas.push_back(Persona("Juan", 2, "Av. Villa Hermosa"));
    personas.push_back(Persona("Matias", 12, "Av. Arequipa"));
    personas.push_back(Persona("Marta", 20, "Urb Misti"));
    personas.push_back(Persona("Oscar", 45, "Urb. Rivera"));
    personas.push_back(Persona("María", 70, "Av. Lima"));

    // Escribir en archivo binario
    ofstream archivoOut("Registro.bin", ios::out | ios::binary);
    for (auto& p : personas)
        p.escribirArchivo(archivoOut);
    archivoOut.close();

    //Leer lo que esta en el Archivo
    vector<Persona> personasLeidas;
    ifstream archivoIn("Registro.bin", ios::in |ios::binary);
    
    // Nuevo vector
    for (int i = 0; i < 5; ++i) {
        Persona p = Persona("", 0, "");
        personasLeidas.push_back(p);
    }
    

    // Mostrar las personas leídas
    for (auto& p : personasLeidas) {
        p.leerArchivo(archivoIn);
        p.mostrar();
        
        cout << "------------------\n";
    }
    archivoIn.close();

    
    return 0;
}
