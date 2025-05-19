#include <iostream>
using namespace std;

class Reproductor {
public:
    virtual void reproducir() = 0;
    virtual void pausar() = 0;
    virtual void detener() = 0;
};

class ReproductorMP3: public Reproductor {
private:
    string cancion;
    
public:
    ReproductorMP3(string c)
     :cancion(c) {}
     
    void reproducir() override {
        cout << "Reproducir la canción: " << cancion << ".MP3" <<endl;
    }
    
    void pausar() override {
        cout << "Pausar la cancion: " << cancion << ".MP3" << endl;
    }
    
    void detener() override {
        cout << "Detener el ReproductorMP3\n";
    }    
    
};

int main()
{
    Reproductor* rp1 = new ReproductorMP3("Atlantis");
    
    rp1->reproducir();
    rp1->pausar();
    rp1->detener();    

    delete rp1;
    return 0;
}
