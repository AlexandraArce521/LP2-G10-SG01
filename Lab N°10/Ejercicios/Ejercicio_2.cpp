#include <iostream>
using namespace std;

template <typename T>
class Ordenar 
{
    private:
        T* arr; 
        int tam;
    
    public:
        Ordenar(T arr[], int tam) : tam(tam) 
        {
            this->arr = new T[tam];
            for (int i = 0; i < tam; i++) {
                this->arr[i] = arr[i];
            }
        }
    
        void ordenarArreglo() 
        {
            for (int i = 0; i < tam - 1; i++) 
            {
                for (int j = 0; j < tam - i - 1; j++) 
                {
                    if (arr[j] > arr[j + 1]) 
                    {
                        T temp = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = temp;
                    }
                }
            }
        }
    
        void imprimirArreglo() 
        {
            for (int i = 0; i < tam; i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
    
        ~Ordenar() {
            delete[] arr;
        }
};

int main() {
    int arrEnteros[] = {64, 34, 25, 12, 22, 11, 90};
    int tamEnteros = 7;
    
    Ordenar<int> ordEnteros(arrEnteros, tamEnteros);
    cout << "Arreglo de enteros original: ";
    ordEnteros.imprimirArreglo();
    
    ordEnteros.ordenarArreglo();
    cout << "Arreglo de enteros ordenado: ";
    ordEnteros.imprimirArreglo();

    float arrFlotantes[] = {64.5, 34.2, 25.7, 12.1, 22.9};
    int tamFlotantes = 5;
    
    Ordenar<float> ordFlotantes(arrFlotantes, tamFlotantes);
    cout << "\nArreglo de flotantes original: ";
    ordFlotantes.imprimirArreglo();
    
    ordFlotantes.ordenarArreglo();
    cout << "Arreglo de flotantes ordenado: ";
    ordFlotantes.imprimirArreglo();

    string arrCadenas[] = {"naranja", "manzana", "banana", "kiwi"};
    int tamCadenas = 4;
    
    Ordenar<string> ordCadenas(arrCadenas, tamCadenas);
    cout << "\nArreglo de cadenas original: ";
    ordCadenas.imprimirArreglo();
    
    ordCadenas.ordenarArreglo();
    cout << "Arreglo de cadenas ordenado: ";
    ordCadenas.imprimirArreglo();

    return 0;
}
