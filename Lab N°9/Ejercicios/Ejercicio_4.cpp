#include <iostream>
#include <vector>
using namespace std;

class Personaje {
public:
    virtual void atacar() = 0;
    virtual void defender() = 0;
    virtual void habilidadEspecial() = 0;
    virtual void mostrar() = 0;
    virtual ~Personaje() = default;
};

class Guerrero : public Personaje {
private:
    string nombre;
    int fuerza;
    int defensa;

public:
    Guerrero(string n, int f, int d) : nombre(n), fuerza(f), defensa(d) {}

    void atacar() override {
        cout << "Guerrero: " << nombre << " ataca con su espada. Fuerza: " << fuerza << endl;
    }

    void defender() override {
        cout << "Guerrero: " << nombre << " bloquea con su escudo. Defensa: " << defensa << endl;
    }

    void habilidadEspecial() override {
        cout << "Guerrero: " << nombre << " usa 'Ira del Berserker' aumentando su fuerza!" << endl;
    }

    void mostrar() override {
        cout << "Información del Guerrero:" << endl;
        cout << "  Nombre: " << nombre << endl;
        cout << "  Fuerza: " << fuerza << endl;
        cout << "  Defensa: " << defensa << endl;
    }
};

class Mago : public Personaje {
private:
    string nombre;
    int poderMagico;
    int mana;

public:
    Mago(string n, int p, int m) : nombre(n), poderMagico(p), mana(m) {}

    void atacar() override {
        cout << "Mago: " << nombre << " lanza una bola de fuego. Poder: " << poderMagico << endl;
    }

    void defender() override {
        cout << "Mago: " << nombre << " se protege con un escudo mágico." << endl;
    }

    void habilidadEspecial() override {
        cout << "Mago: " << nombre << " usa 'Tormenta Arcana' gastando " << mana << " puntos de maná." << endl;
    }

    void mostrar() override {
        cout << "Información del Mago:" << endl;
        cout << "  Nombre: " << nombre << endl;
        cout << "  Poder Mágico: " << poderMagico << endl;
        cout << "  Maná: " << mana << endl;
    }
};

class Arquero : public Personaje {
private:
    string nombre;
    int precision;
    int velocidad;

public:
    Arquero(string n, int p, int v) : nombre(n), precision(p), velocidad(v) {}

    void atacar() override {
        cout << "Arquero: " << nombre << " dispara una flecha. Precisión: " << precision << endl;
    }

    void defender() override {
        cout << "Arquero: " << nombre << " esquiva rápidamente. Velocidad: " << velocidad << endl;
    }

    void habilidadEspecial() override {
        cout << "Arquero: " << nombre << " usa 'Lluvia de Flechas' atacando a todos los enemigos." << endl;
    }

    void mostrar() override {
        cout << "Información del Arquero:" << endl;
        cout << "  Nombre: " << nombre << endl;
        cout << "  Precisión: " << precision << endl;
        cout << "  Velocidad: " << velocidad << endl;
    }
};

int main() {
    vector<Personaje*> personajes;

    personajes.push_back(new Guerrero("Thorin", 80, 60));
    personajes.push_back(new Mago("Elora", 95, 120));
    personajes.push_back(new Arquero("Legolas", 85, 70));

    cout << "\n========== ACCIONES DE LOS PERSONAJES ==========\n";
    for (int i = 0; i < personajes.size(); ++i) {
        personajes[i]->atacar();
        personajes[i]->defender();
        personajes[i]->habilidadEspecial();
        cout << endl;
    }

    cout << "\n========== INFORMACIÓN DE LOS PERSONAJES ==========\n";
    for (int i = 0; i < personajes.size(); ++i) {
        cout << i+1 << ".- ";
        personajes[i]->mostrar();
        cout << endl;
    }

    for (int i = 0; i < personajes.size(); ++i) {
        delete personajes[i];
    }

    return 0;
}
