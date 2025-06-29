#include<vector>
#include <iostream>
using namespace std;

class Animal {
public:
    virtual void comer() = 0;
    virtual void dormir() = 0;
    virtual void moverse() = 0;
    virtual void mostrar() = 0;
    virtual ~Animal() = default;
};

class Mamifero : public Animal {
private:
    string especie;
    string habitat;
    string nombre;
    int edad;
    

public:
    Mamifero(string e, string h, string n, int ed)
     :especie(e), habitat(h), nombre(n), edad(ed)  {}
    
    void comer() override {
        cout << "Mamifero: " << nombre << " esta comiendo "<<endl;

    }
    
    void dormir() override {
        cout << "Mamifero: " << nombre << " esta durmiendo " << endl;
    }
    
    void moverse() override {
        cout << "Mamifero: " << nombre << " se mueve en " << habitat << endl;
    }
    
    void mostrar() override {
        cout << "Información del Mamífero:" << endl;
        cout << "  Nombre: " << nombre << endl;
        cout << "  Especie: " << especie << endl;
        cout << "  Edad: " << edad << " años" << endl;
    }
};

class Ave : public Animal {
private:
    bool volar;
    string nombre;
    string especie;
    string habitat;
    int edad;

public:
    
    Ave(bool v, string n, string e, string h, int ed)
     : volar(v), nombre(n), especie(e), habitat(h), edad(ed) {}
     
    void comer() override {
        cout << "Ave: " << nombre << " esta comiendo "<<endl;

    }
    
    void dormir() override {
        cout << "Ave: " << nombre << " esta durmiendo " << endl;
    }
    
    void moverse() override {
        cout << "Ave: " << nombre << " se mueve en " << habitat << endl;
    }  

    void mostrar() override {
        cout << "Información del Ave:" << endl;
        cout << "  Nombre: " << nombre << endl;
        cout << "  Especie: " << especie << endl;
        cout << "  Edad: " << edad << " años" << endl;
        cout << (!volar ? "  No vuela" : "  Si vuela" ) << endl; // (condición)? valor_verdadero: valor_falso
    }
    
};

class Reptil : public Animal {
private:
    string nombre;
    string especie;
    string habitat;
    bool esVeneno;

public:
    Reptil(string n, string e, string h, bool veneno)
        : nombre(n), especie(e), habitat(h), esVeneno(veneno) {}

    void comer() override {
        cout << "Reptil: " << nombre << " esta comiendo "<<endl;

    }
    
    void dormir() override {
        cout << "Reptil: " << nombre << " esta durmiendo " << endl;
    }
    
    void moverse() override {
        cout << "Reptil: " << nombre << " se mueve en " << habitat << endl;
    } 

    void mostrar() override {
        cout << "Información del Reptil:" << endl;
        cout << "  Nombre: " << nombre << endl;
        cout << "  Especie: " << especie << endl;
        cout << "  ¿Es venenoso?: " << (esVeneno ? "Sí" : "No") << endl; // (condición)? valor_si_verdadero: valor_si_falso
    }
};


int main () {
    
    vector <Animal*> animales;
    
    animales.push_back(new Ave(true, "Loro", "Ave terrestre", "Ambientes tropicales", 2));
    animales.push_back(new Mamifero("Marsupial", "Bosques", "Spike", 4));
    animales.push_back(new Reptil("Pascal", "Chamaeleonidae", "Bosques", false));
    animales.push_back(new Ave(false, "Pingüino", "Ave marina", "Glaciares", 3));

    cout << "\n==============================" << endl;
    for (int i = 0; i < animales.size(); ++i) {
        animales[i]->comer();
    }
    cout << "==============================\n" << endl;
    cout << "\n==============================" << endl;
    for (int i = 0; i < animales.size(); ++i) {
        animales[i]->dormir();
    }    
    cout << "==============================\n" << endl;
    cout << "\n==============================" << endl;
    for (int i = 0; i < animales.size(); ++i) {
        animales[i]->moverse();
    }
    cout << "==============================\n" << endl;
    cout << "\n==============================" << endl;
    for (int i = 0; i < animales.size(); ++i) {
        cout << i+1 <<".- ";
        animales[i]->mostrar();
        cout<<endl;
    }
    cout << "==============================" << endl;

    return 0;
}
