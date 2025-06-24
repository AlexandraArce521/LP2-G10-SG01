#include <fstream>  
#include <iostream>  
#include <stdexcept>  
using namespace std;  
  
template <class T> 
void divide(T a, T b) { 
  
    if(b == 0) { 
        throw runtime_error("!"); 
    }     
    cout << "Dividir " << a << " / "  << b << " = "; 
    cout << a/b; 
    cout << "\n----------------------\n"; 
} 
  
int main() { 
     
    try 
    {     
     
    divide(10.0,4.0);  
    divide(5,2);  
    divide(47600L,2462L);  
    divide(10.0,0.0); 
  
  
    } 
     
    catch (runtime_error other) 
    { 
        cout << "(!) Error por dividir por cero" << endl; 
    } 
     
    catch(invalid_argument other) { 
        cout << "(!)  Error: Argementos no validos" << endl; 
    } 
    catch (...)  
    { 
        cout << "(!)Error inesperado" << endl; 
    } 
         
    return 0; 
} 
