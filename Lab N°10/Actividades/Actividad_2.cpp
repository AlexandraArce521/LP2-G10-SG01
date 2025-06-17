#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>    // para ostringstream
using namespace std;

class Entrega {
    string id;
    double peso;
public:
    Entrega(string id_, double peso_) : id(id_), peso(peso_) {}
    string getId() const { return id; }
    double getPeso() const { return peso; }
};

class SistemaRutas {
    vector<Entrega> entregas;
    map<string, string> asignaciones; // entregaId → vehiculoId (string)

    // Función helper para convertir cualquier VehiculoID a string
    template<typename T>
    string toString(const T& v) {
        ostringstream oss;
        oss << v;
        return oss.str();
    }

public:
    void agregarEntrega(const Entrega& e) {
        entregas.push_back(e);
    }

    template<typename VehiculoID>
    void asignarVehiculo(const string& entregaId, const VehiculoID& vehId) {
        asignaciones[entregaId] = toString(vehId);
        cout << "Asignada entrega " << entregaId
             << " al vehículo " << toString(vehId) << "\n";
    }

    template<typename TimeType>
    void planificarHorario(const string& entregaId,
                           const TimeType& inicio,
                           const TimeType& fin) {
        cout << "Entrega " << entregaId
             << " programada de " << toString(inicio)
             << " a " << toString(fin) << "\n";
    }

    void resumenAsignaciones() const {
        cout << "\nRESUMEN DE ASIGNACIONES\n";
        for (const auto& e : entregas) {
            string entId = e.getId();
            cout << "  Entrega " << entId
                 << " (peso " << e.getPeso() << "kg)"
                 << " → vehículo " << asignaciones.at(entId) << "\n";
        }
    }
};

int main() {
    SistemaRutas sistema;
    sistema.agregarEntrega(Entrega("E100", 12.5));
    sistema.agregarEntrega(Entrega("E101", 7.3));

    // Ahora funciona con int y con string:
    sistema.asignarVehiculo("E100", 42);
    sistema.asignarVehiculo("E101", string("CamionA"));

    sistema.planificarHorario("E100", 8, 10);
    sistema.planificarHorario("E101", string("09:30"), string("11:45"));

    sistema.resumenAsignaciones();
    return 0;
}
