#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
using namespace std;

// Template de función para calcular la distancia euclídea entre dos puntos
template<typename T>
T calcularDistancia(T x1, T y1, T x2, T y2) {
    T dx = x2 - x1;
    T dy = y2 - y1;
    return static_cast<T>(sqrt(dx*dx + dy*dy));
}

// Template de función para estimar el tiempo de viaje dado distancia y velocidad
template<typename Distancia, typename Velocidad>
auto calcularTiempoEstimado(Distancia d, Velocidad v) -> decltype(d / v) {
    return d / v;
}

// Template de función para generar un informe a partir de un contenedor de pares <Distancia, Tiempo>
template<typename Container>
void generarInforme(const Container& datos) {
    cout << "\nINFORME DE RUTAS\n";
    cout << "---------------------------"<< endl;
    for (const auto& item : datos) {
        cout << "Distancia: " << item.first << endl;
        cout << "Tiempo:    " << item.second << endl;
        cout << "---------------------------"<< endl;
    }
    cout << "FIN DEL INFORME\n";
}

int main() {
    // 1) Prueba de calcularDistancia
    double distancia = calcularDistancia(-12.5, 4.0, 8.2, -3.5);
    cout << "Distancia: " << distancia << " unidades\n";

    // 2) Prueba de calcularTiempoEstimado
    double tiempo = calcularTiempoEstimado(distancia, 60.0); // velocidad 60 km/h
    cout << "Tiempo estimado: " << tiempo << " horas\n";

    // 3) Prueba de generarInforme
    vector<pair<double,double>> rutas = {
        {distancia, tiempo},
        {10.5,  0.25},
        {120.0, 2.00},
        {55.3,  1.10}
    };
    generarInforme(rutas);

    return 0;
}
