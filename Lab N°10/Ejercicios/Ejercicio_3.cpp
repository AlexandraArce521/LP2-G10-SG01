#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <class T> class Recipiente {
    private:
        vector <T> v;
    public:
        Recipiente(vector<T>& v)
         : v(v) {}
        
        void OrdenarLista() {
            sort(v.begin(), v.end());
        }
        
        void MostrarLista() {
            for (int i = 0; i < v.size(); ++i) {
                cout << v[i] << " ";
            }
            cout << endl;
        }
};

int main()
{
    vector<int> listEnteros = {5, 3, 1, 4, 2};
    vector<long> listLong = {5000, 3500, 4090, 4000};
    vector<string> listString = {"Z", "Y", "O", "A"};
    
    cout << "\n=====Ordenar lista de enteros======\n" << endl;
    
    Recipiente<int> ordEnteros(listEnteros);
    cout<< "Lista original: ";
    ordEnteros.MostrarLista();
    
    ordEnteros.OrdenarLista();
    cout<< "Lista ordenada: ";
    ordEnteros.MostrarLista();
    cout << "\n===================================\n" << endl;
    
    cout << "\n=====Ordenar lista de números largos======\n" << endl;
    Recipiente<long> ordLong(listLong);
    cout<< "Lista original: ";
    ordLong.MostrarLista();
    
    ordLong.OrdenarLista();
    cout<< "Lista ordenada: ";
    ordLong.MostrarLista();
    cout << "\n===================================\n" << endl;
    
    cout << "\n=====Ordenar lista de letras======\n" << endl;
    Recipiente<string> ordString(listString);
    cout<< "Lista original: ";
    ordString.MostrarLista();
    
    ordString.OrdenarLista();
    cout<< "Lista ordenada: ";
    ordString.MostrarLista();
    cout << "\n===================================\n" << endl;

    return 0;
    
}
