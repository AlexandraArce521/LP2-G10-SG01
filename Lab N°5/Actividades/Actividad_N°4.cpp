#include <iostream>
using namespace std;

class ComponenteA {
public:
    ComponenteA() {
        cout << "Constructor de ComponenteA\n";
    }
    ~ComponenteA() {
        cout << "Destructor de ComponenteA\n";
    }
};

class ComponenteB {
public:
    ComponenteB() {
        cout << "Constructor de ComponenteB\n";
    }
    ~ComponenteB() {
        cout << "Destructor de ComponenteB\n";
    }
};

class Sistema {
private:
    ComponenteA a;
    ComponenteB b;
public:
    Sistema() {
        cout << "Constructor de Sistema\n";
    }
    ~Sistema() {
        cout << "Destructor de Sistema\n";
    }
};

int main() {
    cout << "Creando objeto Sistema...\n";
    Sistema s;
    cout << "Fin del main\n";
    return 0;
}
