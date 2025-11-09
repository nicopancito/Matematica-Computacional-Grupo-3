#include "Grafo.h"

using namespace std;

int main() {
    Grafo::mostrarCabecera();

    int n;
    do {
        cout << "Ingrese cantidad de nodos [8-16]: ";
        cin >> n;
        if (n < 8 || n>16) cout << "⚠️  Por favor ingrese un valor entre 8 y 16.\n";
    } while (n < 8 || n>16);

    Grafo g(n);

    int opcion;
    cout << "\n1. Generar grafo manualmente\n2. Generar grafo aleatoriamente\nSeleccione una opción: ";
    cin >> opcion;

    if (opcion == 1) g.llenarManual();
    else g.llenarAleatorio();

    g.mostrarMatriz();

    char nodoInicio;
    int inicio;
    do {
        cout << "\nIngrese nodo de inicio (A-" << char('A' + n - 1) << "): ";
        cin >> nodoInicio;
        nodoInicio = toupper(nodoInicio);
        inicio = nodoInicio - 'A';
        if (inicio < 0 || inicio >= n) cout << "⚠️ Nodo inválido. Intente nuevamente.\n";
    } while (inicio < 0 || inicio >= n);

    char nodoDestino;
    int destino;
    do {
        cout << "Ingrese nodo destino (A-" << char('A' + n - 1) << "), diferente al inicio: ";
        cin >> nodoDestino;
        nodoDestino = toupper(nodoDestino);
        destino = nodoDestino - 'A';
        if (destino < 0 || destino >= n || destino == inicio) cout << "⚠️ Nodo inválido. Intente nuevamente.\n";
    } while (destino < 0 || destino >= n || destino == inicio);

    g.dijkstraPasoAPaso(inicio, destino);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10);
    cout << "\n✅ PROCESO COMPLETADO EXITOSAMENTE.\n";
    SetConsoleTextAttribute(hConsole, 7);
    cout << "Gracias por usar el programa. ¡Hasta pronto!\n";

    return 0;
}
