#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

struct Actividad {
    string nombre;
    int inicio;      // hora original
    int fin;         // hora original
    bool realizada;
};

struct Dia {
    string nombre;
    vector<Actividad> actividades;
};

void mostrarHora(int h) {
    cout << setw(2) << setfill('0') << h << ":00";
}

int main() {

    vector<Dia> semana = {
        {"Domingo", {
            {"Descansar", 10, 12, false},
            {"Series", 18, 20, false}
        }},
        {"Lunes", {
            {"Juntada", 0, 2, false},
            {"Entrenar", 8, 9, false},
            {"Comer", 13, 14, false},
            {"Dormir", 23, 24, false}
        }},
        {"Martes", {
            {"Facultad", 8, 12, false},
            {"Estudiar", 14, 17, false},
            {"Dormir", 23, 24, false}
        }},
        {"Miercoles", {
            {"Entrenar", 8, 9, false},
            {"Proyecto", 10, 13, false},
            {"Dormir", 23, 24, false}
        }},
        {"Jueves", {
            {"Facultad", 8, 12, false},
            {"Caminar", 18, 19, false},
            {"Dormir", 23, 24, false}
        }},
        {"Viernes", {
            {"Entrenar", 8, 9, false},
            {"Salir", 20, 23, false}
        }},
        {"Sabado", {
            {"Compras", 10, 12, false},
            {"Familia", 15, 18, false}
        }}
    };

    // Obtener fecha y hora actual
    time_t ahora = time(nullptr);
    tm* tiempo = localtime(&ahora);

    int diaActual = tiempo->tm_wday;
    int horaActual = tiempo->tm_hour;

    Dia& hoy = semana[diaActual];

    cout << "=============================\n";
    cout << "DIA ACTUAL: " << hoy.nombre << endl;
    cout << "HORA ACTUAL: ";
    mostrarHora(horaActual);
    cout << endl;
    cout << "=============================\n\n";

    // Preguntar qué actividades ya hizo
    for (auto& act : hoy.actividades) {

        char r;

        cout << "Hiciste \"" << act.nombre << "\"? (s/n): ";
        cin >> r;

        act.realizada = (r == 's' || r == 'S');
    }

    cout << "\n=============================\n";
    cout << "CRONOGRAMA REPROGRAMADO\n";
    cout << "=============================\n\n";

    int horaLibre = horaActual;

    int horasPendientes = 0;

    for (auto& act : hoy.actividades) {

        if (!act.realizada) {

            int duracion = act.fin - act.inicio;

            mostrarHora(horaLibre);
            cout << " - ";
            mostrarHora(horaLibre + duracion);

            cout << " -> " << act.nombre << endl;

            horaLibre += duracion;
            horasPendientes += duracion;
        }
    }

    cout << "\nHoras pendientes: "
         << horasPendientes << endl;

    cout << "Horas restantes del dia: "
         << 24 - horaActual << endl;

    string nuevaActividad;
    int duracionNueva;

    cin.ignore();

    cout << "\nNueva actividad: ";
    getline(cin, nuevaActividad);

    cout << "Duracion (horas): ";
    cin >> duracionNueva;

    int tiempoLibreReal =
        (24 - horaActual) - horasPendientes;

    cout << "\n=============================\n";
    cout << "ANALISIS\n";
    cout << "=============================\n";

    if (duracionNueva <= tiempoLibreReal) {

        cout << "SI podes realizar "
             << nuevaActividad << endl;

        cout << "Te quedaran "
             << tiempoLibreReal - duracionNueva
             << " horas libres.\n";
    }
    else {

        cout << "NO podes realizar "
             << nuevaActividad << endl;

        cout << "Solo dispones de "
             << tiempoLibreReal
             << " horas libres.\n";
    }

    return 0;
}