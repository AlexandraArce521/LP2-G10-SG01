#include <iostream>
#include <string>
using namespace std;

class Vehiculo {
protected:
    string marca, modelo, anyo;
    double precio;

public:
    
    Vehiculo(string marca, string modelo, string anyo, double precio) {
        this->marca = marca;
        this->modelo = modelo;
        this->anyo = anyo;
        this->precio = precio;
        cout << "Constructor de clase base Vehiculo" << endl;
    }
    
    string getMarca() {
        return marca;
    }
    
    string getModelo() {
        return modelo;
    }
    
    string getAnyo() {
        return anyo;
    }
    
    double getPrecio() {
        return precio;
    }
    
    void setMarca(string m) {
        marca = m;
    }
    
    void setModelo(string mo) {
        modelo = mo;
    }
    
    void setAnyo(string a) {
        anyo = a;
    }
    
    void setPrecio(double p) {
        precio = p;
    }
    
    ~Vehiculo() {
        cout << "Destructor de clase base Vehiculo" << endl;
    }
        
};

class Automovil: public Vehiculo {
private:
    int numPuertas;
    string tipoCombustible;

public:
    Automovil(string marca, string modelo, string anyo, double precio, int num, string tipo)
        : Vehiculo(marca, modelo, anyo, precio), numPuertas(num), tipoCombustible(tipo) {
        cout << "Constructor de clase derivada Automovil" << endl;
    }

    void mostrarAuto() {
        cout << "==================================" << endl;
        cout << "Detalles del Automovil.\n" << endl;
        cout << "Marca: " << marca << endl;
        cout << "Modelo: " << modelo << endl;
        cout << "Año: " << anyo << endl;
        cout << "Precio: " << precio << endl;
        cout << "Número de Puertas: " << numPuertas << endl;
        cout << "Tipo de combustible: " << tipoCombustible << endl;
        cout << "\n==================================" << endl;

    }
    
    int getNumPuertas() {
        return numPuertas;
    }
    
    string getTipo() {
        return tipoCombustible;
    }
    
    void setNumPuertas(int p) {
        numPuertas = p;
    }
    
    void setTipo(string tipo) {
        tipoCombustible = tipo;
    }

    ~Automovil () {
        cout << "Destructor de clase derivada Automovil" << endl;
    }
    


};

class Motocicleta: public Vehiculo {
private:
    int cilindrada;
    
public:
    Motocicleta(string marca, string modelo, string anyo, double precio, int cc)
        : Vehiculo(marca, modelo, anyo, precio), cilindrada(cc) {
        cout << "Constructor de clase derivada Motocicleta" << endl;
    }
    
    int getCilindrica() {
        return cilindrada;
    }
    
    void setCilindrica(int cc) {
        cilindrada = cc;
    }
    
    void mostrarMoto() {
        cout << "==================================\n" << endl;
        cout << "Detalles de Motocicleta." << endl;
        cout << "Marca: " << marca << endl;
        cout << "Modelo: " << modelo << endl;
        cout << "Año: " << anyo << endl;
        cout << "Precio: " << precio << endl;
        cout << "Cilindrada: " << cilindrada << " cc" <<endl;
        cout << "\n==================================" << endl;

    }
    
    ~Motocicleta() {
       cout << "Destructor de clase derivada Motocicleta" << endl; 
    }
};

int main()
{
    Automovil auto1("Toyota", "Corolla", "2023", 25000.0, 4, "Gasolina");
    auto1.mostrarAuto();
    cout << endl;
    Motocicleta moto1("Honda", "CBR500R", "2022", 7000.0, 8);
    moto1.mostrarMoto();
    
    return 0;
}
