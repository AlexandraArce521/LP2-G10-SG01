#include <iostream>
#include <string>
using namespace std;

class Habitacion {
private:
   int numero;
   string tipo;
   double precioPorNoche;

public:
    
    Habitacion() {
        numero = 0;
        tipo = "Tipo no asignado";
        precioPorNoche = 0.0;
    }
    
    Habitacion(int num, string t, double precio)
    :numero(num), tipo(t), precioPorNoche(precio)   {
        cout << "Habitacion creada! ";
    }
    
    int getNumero() {
        return numero;
    }
    
    string getTipo() {
        return tipo;
    }
    
    double getPrecio() {
        return precioPorNoche;
    }
    
    void setNumero(int n) {
        numero = n;
    }
    
    void setTipo(string t) {
        tipo = t;
    }
    
    void setPrecio(double p) {
        precioPorNoche = p;
    }
    
    void mostrarHabitacion() const {
        cout << "\n==== Habitacion ====" << endl;
        cout << "Numero: " << numero << endl;
        cout << "Tipo de habitacion: " << tipo << endl;
        cout << "Precio por Noche: " << precioPorNoche << endl;
    }
    
    ~Habitacion() {
        cout << "Destructor de Habitacion invocado " << endl;
    }
};

class ReservaHotel {
private:
    string nombre;
    int cantidad;
    Habitacion* habitaciones;  

public:
    
    ReservaHotel() {
        nombre = "Sin nombre";
        cantidad = 0;
    }
    
    ReservaHotel(string n, int cant )
        :nombre(n), cantidad(cant)  {
            habitaciones = new Habitacion[cantidad];
            cout << "Reserva creada!" << endl;
        }
    
    string getNombre()  {
        return nombre;
    }
    
    int getCantidad() {
        return cantidad;
    }
    
    void setNombre(string n) {
        nombre = n;
    }
    
    void setCantidad(int c) {
        cantidad = c;
    }
    
    double TotalPorNoche() {
        double total = 0;
        for (int i = 0; i < cantidad; ++i) {
            total += habitaciones[i].getPrecio();
        }
        return total;
    }

    void asignarHabitacion(int indice, int num, string tipo, double precio) {
        if (indice >= 0 && indice < cantidad) {
            habitaciones[indice] = Habitacion(num, tipo, precio);
        } else {
            cout << "Índice fuera de rango al asignar habitación." << endl;
        }
    }


    void mostrarReserva() const {
        cout << "\n---- Detalles de la reserva ----\n"<<endl;
        cout << "Nombre de la reserva: " << nombre << endl;
        cout << "Cantidad de habitaciones: " << cantidad << endl;
        for (int i = 0; i < cantidad; ++i) {
            habitaciones[i].mostrarHabitacion();
        }
    }
    
    ~ReservaHotel() {
    delete[] habitaciones; // liberar memoria
    cout << "Destructor invocado para Reserva de " << nombre << endl;
}
   
};


int main()
{
    ReservaHotel reserva1("Juan Pérez", 1);
    ReservaHotel reserva2("Sofia Pérez", 2);
//_____________________________________________________

    reserva1.asignarHabitacion(0, 101, "Simple", 150.0);
    
    cout<<endl<< "____________ RESERVA 1 ____________"<<endl;
    reserva1.mostrarReserva();  
    cout << "\nPrecio total por noche: " 
         << reserva1.TotalPorNoche() << endl;
    cout << "====================================" << endl;
    cout << "____________________________________\n" << endl;
//_____________________________________________________

    reserva2.asignarHabitacion(0, 102, "Doble", 250.0);
    
    cout<<endl<< "____________ RESERVA 2 ____________"<<endl;
    reserva2.mostrarReserva();  
    cout << "\nPrecio total por noche: " 
         << reserva2.TotalPorNoche() << endl;
    cout << "====================================" << endl;
    cout << "____________________________________\n" << endl;
//_____________________________________________________
    
    reserva2.asignarHabitacion(1, 103, "Simple", 150.0);
    
    cout<<endl<< "____________ RESERVA 2 ____________"<<endl;
    cout<<endl<< "____________ completada ____________"<<endl;
    reserva2.mostrarReserva();  
    cout << "\nPrecio total por noche: " 
         << reserva2.TotalPorNoche() << endl;
    cout << "====================================" << endl;
    cout << "____________________________________\n" << endl;

    return 0;
}
