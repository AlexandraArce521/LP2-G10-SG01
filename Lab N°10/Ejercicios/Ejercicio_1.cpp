#include <iostream>
using namespace std;

template <typename T>
void ordenarArreglo(T arr[], int tam) 
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

template <typename T>
void imprimirArreglo(T arr[], int tam) 
{
    for (int i = 0; i < tam; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() 
{
    int arrEnteros[] = {64, 34, 25, 12, 22, 11, 90};
    int tamEnteros = sizeof(arrEnteros) / sizeof(arrEnteros[0]);
    
    cout << "Arreglo de enteros original: ";
    imprimirArreglo(arrEnteros, tamEnteros);
    
    ordenarArreglo(arrEnteros, tamEnteros);
    
    cout << "Arreglo de enteros ordenado: ";
    imprimirArreglo(arrEnteros, tamEnteros);
    
    float arrFlotantes[] = {64.5, 34.2, 25.7, 12.1, 22.9};
    int tamFlotantes = sizeof(arrFlotantes) / sizeof(arrFlotantes[0]);
    
    cout << "\nArreglo de flotantes original: ";
    imprimirArreglo(arrFlotantes, tamFlotantes);
    
    ordenarArreglo(arrFlotantes, tamFlotantes);
    
    cout << "Arreglo de flotantes ordenado: ";
    imprimirArreglo(arrFlotantes, tamFlotantes);
    
    string arrCadenas[] = {"naranja", "manzana", "banana", "kiwi"};
    int tamCadenas = sizeof(arrCadenas) / sizeof(arrCadenas[0]);
    
    cout << "\nArreglo de cadenas original: ";
    imprimirArreglo(arrCadenas, tamCadenas);
    
    ordenarArreglo(arrCadenas, tamCadenas);
    
    cout << "Arreglo de cadenas ordenado: ";
    imprimirArreglo(arrCadenas, tamCadenas);
    
    return 0;
}
