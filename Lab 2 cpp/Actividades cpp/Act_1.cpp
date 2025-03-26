#include <iostream>
#include <string>
using namespace std;

/* 
  a) CLASE DE ANIMALES
     - Atributos: nombre, edad, tipoDeAnimal
     - Métodos: alimentar(), hacerSonido()
*/

class Animal 
{
private:
    string nombre;
    int edad;
    string tipoDeAnimal;
public:
    Animal(string n, int e, string tipo) 
        : nombre(n), edad(e), tipoDeAnimal(tipo) {}

    void alimentar() 
    {
        cout << nombre << " está siendo alimentado." << endl;
    }

    void hacerSonido()
    {
        // Lógica mínima para el ejemplo
        if (tipoDeAnimal == "perro") {
            cout << nombre << " ladra: ¡Guau Guau!" << endl;
        } else if (tipoDeAnimal == "gato") {
            cout << nombre << " maúlla: ¡Miau!" << endl;
        } else {
            cout << nombre << " hace un sonido genérico de animal." << endl;
        }
    }

    // Opcional: métodos para reflexionar sobre atributos
    string getNombre() { return nombre; }
    int getEdad() { return edad; }
    string getTipo() { return tipoDeAnimal; }
};


/* 
  b) CLASE DE CARROS
     - Atributos: modelo, anio, velocidad
     - Métodos: acelerar(), frenar()
*/
class Coche 
{
private:
    string modelo;
    int anio;
    int velocidad;
public:
    Coche(string m, int a) 
        : modelo(m), anio(a), velocidad(0) {}

    void acelerar(int incremento) 
    {
        velocidad += incremento;
        cout << "El coche " << modelo << " acelera a " << velocidad << " km/h." << endl;
    }

    void frenar(int decremento) 
    {
        if (velocidad - decremento < 0) 
        {
            velocidad = 0;
        } 
        else 
        {
            velocidad -= decremento;
        }
        cout << "El coche " << modelo << " frena a " << velocidad << " km/h." << endl;
    }

    // Métodos opcionales para reflexionar
    string getModelo() { return modelo; }
    int getAnio() { return anio; }
    int getVelocidad() { return velocidad; }
};


/* 
  c) CLASE DE ESTUDIANTES
     - Atributos: nombre, edad, grado
     - Métodos: tomarExamen(), recibirCalificacion(float nota)
*/
class Estudiante 
{
private:
    string nombre;
    int edad;
    string grado;
public:
    Estudiante(string n, int e, string g) 
        : nombre(n), edad(e), grado(g) {}

    void tomarExamen()
    {
        cout << nombre << " (" << grado << ") está tomando un examen." << endl;
    }

    void recibirCalificacion(float nota) 
    {
        cout << nombre << " ha recibido una calificación de " << nota << "." << endl;
    }

    // Métodos opcionales
    string getNombre() { return nombre; }
    int getEdad() { return edad; }
    string getGrado() { return grado; }
};


/* 
  d) CLASE DE TIENDAS
     - Atributos: nombre, direccion, tipoDeTienda, stock (ejemplo básico)
     - Métodos: venderProducto(), agregarProducto()
*/
class Tienda 
{
private:
    string nombre;
    string direccion;
    string tipoDeTienda;
    int stock;  // conteo básico para ejemplificar
public:
    Tienda(string n, string d, string t) 
        : nombre(n), direccion(d), tipoDeTienda(t), stock(0) {}

    void agregarProducto(int cantidad)
    {
        stock += cantidad;
        cout << "Se agregaron " << cantidad << " productos a " << nombre 
             << ". Stock actual: " << stock << endl;
    }

    void venderProducto(int cantidad) 
    {
        if (cantidad > stock) 
        {
            cout << "No hay suficiente stock en " << nombre << " para vender " 
                 << cantidad << " productos." << endl;
        } 
        else 
        {
            stock -= cantidad;
            cout << "Se vendieron " << cantidad << " productos en " << nombre 
                 << ". Stock restante: " << stock << endl;
        }
    }

    // Métodos opcionales
    string getNombre() { return nombre; }
    string getDireccion() { return direccion; }
    string getTipo() { return tipoDeTienda; }
};

/* 
  FUNCIÓN PRINCIPAL
  Se crean objetos de cada clase y se prueban sus métodos
*/
int main() 
{
    cout << "=== Clase Animal ===" << endl;
    Animal perro("Bobby", 3, "perro");
    Animal gato("Mishifu", 2, "gato");
    Animal caballo("Tornado", 5, "caballo");

    perro.alimentar();
    perro.hacerSonido();

    gato.alimentar();
    gato.hacerSonido();

    caballo.alimentar();
    caballo.hacerSonido();

    cout << "\n=== Clase Coche ===" << endl;
    Coche coche1("Toyota Corolla", 2020);
    Coche coche2("Honda Civic", 2018);

    coche1.acelerar(20);
    coche1.frenar(10);

    coche2.acelerar(30);
    coche2.frenar(15);

    cout << "\n=== Clase Estudiante ===" << endl;
    Estudiante est1("Carlos", 16, "4to Secundaria");
    Estudiante est2("Andrea", 17, "5to Secundaria");

    est1.tomarExamen();
    est1.recibirCalificacion(15.5);

    est2.tomarExamen();
    est2.recibirCalificacion(18.0);

    cout << "\n=== Clase Tienda ===" << endl;
    Tienda tienda1("RopaFina", "Av. Principal 123", "Ropa");
    Tienda tienda2("TechWorld", "Calle Secundaria 456", "Electrónicos");

    tienda1.agregarProducto(50);
    tienda1.venderProducto(10);

    tienda2.agregarProducto(100);
    tienda2.venderProducto(120); // Ejemplo de stock insuficiente

    return 0;
}
