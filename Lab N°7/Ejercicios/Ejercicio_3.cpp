#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Movil {
protected:
    string marca;
    string modelo;
    string SO;

public:
    Movil(string m, string model, string so)
     : marca(m), modelo(model), SO(so) {
        cout << "Constructor de la clase Movil invocado" << endl;
    }
    
    void setMarca(string m) {
        marca = m;
    }
    
    void setModelo(string model) {
        modelo = model;
    }
    
    void setSO (string so) {
        SO = so;
    }
    
    ~Movil() {
        cout << "Destructor  de la clase Movil invocado" << endl;
    }

};

class Telefono: protected Movil {
private:
    vector <string> aplicaciones;
    string gama;


public:
    Telefono(string m, string model, string so, vector<string>a, string g)
     : Movil(m, model, so), aplicaciones(a), gama(g)
    {
        mostrarFono();
        cout << "Constructor con parametros de " << marca << endl;
    }
    
    void mostrarFono() const {
        cout << "==============================" << endl;
        cout << "Detalles del Telefono. " << endl;
        cout << "Marca: " << marca << endl;
        cout << "Modelo " << modelo << endl;
        cout << "Sistema Operativo: " << SO << endl;
        cout << "Gama: " << gama << endl;

        mostrarAplicaciones();
        cout << "=============================" << endl;
    }
    
    void mostrarAplicaciones() const {
        cout << "Aplicaciones del teléfono:\n" << endl;
        for (const auto& app : aplicaciones) {
            cout <<"  *" <<app << endl;
        }
        cout << endl;
    }


    ~Telefono() {
        cout << "Destructor de Telefono con número: " << marca << endl;
    }

};

class Tablet: protected Movil {
private:
    bool tieneLapiz;

public:
    Tablet(string m, string model, string so, bool lapiz)
     : Movil(m, model, so), tieneLapiz(lapiz) {
         
        mostrarInfo();
        cout << "Constructor con parametros de " << marca << endl;

     }
     
     void mostrarInfo() const {
         cout << "===================" << endl;
         cout << "Detalles de la Tablet. " << endl;
         cout << "Marca: " << marca << endl;
         cout << "Modelo: " << modelo << endl;
         cout << "Sistema operativo: " << endl;
        if(tieneLapiz) {
            cout << modelo<< " tiene lapiz" << endl;
         }
         
        else {
            cout << modelo << " no tiene lapiz" << endl;
            
         }
         cout << "===================" << endl;
     }
     

   ~Tablet() {
        cout << "Destructor de Tablet " << endl;
   }
    
};

int main()
{
    vector<string>aplicaciones = {"Facebook", "Youtube", "Instagram"};
    
    Telefono t1("Samsung", "Galaxy S21", "Android", aplicaciones, "Alta");
    cout << endl;
    Tablet tab1("Apple", "iPad Pro", "iPadOS", true);
    cout << endl;
    
    return 0;
}
