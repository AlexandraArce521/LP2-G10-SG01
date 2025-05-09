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
        cout << "Destructor invocado" << endl;
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
        cout << "Constructor con parametros de " << marca << endl;
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
         if(tieneLapiz) {
             cout << marca << "tiene lapiz" << endl;
         }
         
         else {
             cout << marca << "no tiene lapiz" << endl;
            
         }
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

    
    return 0;
}
