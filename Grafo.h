#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <windows.h>

using namespace std;

class Grafo {
private:
    int n; 
    vector<vector<int>> matriz;

    void setColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void imprimirCaminosRec(int nodo, int inicio, vector<vector<int>>& predecesores, vector<int>& camino) {
        camino.push_back(nodo);

        if (nodo == inicio) {
            // Camino completo
            for (int i = camino.size() - 1; i >= 0; i--) {
                setColor(14);
                cout << char('A' + camino[i]);
                setColor(7);
                if (i > 0) cout << " -> ";
            }
            cout << "\n";
        }
        else {
            for (int pred : predecesores[nodo]) {
                imprimirCaminosRec(pred, inicio, predecesores, camino);
            }
        }

        camino.pop_back();
    }

public:
    Grafo(int n) {
        this->n = n;
        matriz.resize(n, vector<int>(n, 0));
        srand(time(nullptr));
    }

    static void mostrarCabecera() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 11);
        cout << "=============================================\n";
        cout << "          ALGORITMO DE DIJKSTRA 50%         \n";
        cout << "=============================================\n\n";
        SetConsoleTextAttribute(hConsole, 7);
    }

    void llenarManual() {
        cout << "\nIngrese el peso (0 si no hay conexion):\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) matriz[i][j] = 0;
                else {
                    cout << "Peso de [" << char('A' + i) << "] -> [" << char('A' + j) << "]: ";
                    cin >> matriz[i][j];
                }
            }
        }
    }

    void llenarAleatorio() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) matriz[i][j] = 0;
                else matriz[i][j] = (rand() % 2 == 0) ? (rand() % 9 + 1) : 0;
            }
        }
        cout << "\nGrafo generado aleatoriamente.\n";
    }

    void mostrarMatriz() {
        cout << "\nMatriz de adyacencia:\n   ";
        for (int i = 0; i < n; i++) cout << setw(3) << char('A' + i);
        cout << "\n";

        for (int i = 0; i < n; i++) {
            cout << char('A' + i) << " ";
            for (int j = 0; j < n; j++) {
                if (matriz[i][j] == 0) cout << setw(3) << "-";
                else cout << setw(3) << matriz[i][j];
            }
            cout << "\n";
        }
        cout << endl;
    }

    void dijkstraPasoAPaso(int inicio, int destino) {
        vector<int> distancia(n, INT_MAX);
        vector<bool> visitado(n, false);
        vector<vector<int>> predecesores(n);

        distancia[inicio] = 0;

        cout << "\n🔹 INICIANDO DIJKSTRA DESDE EL NODO " << char('A' + inicio) << " 🔹\n";
        cout << "Explicación: \nCada paso elegimos el nodo no visitado con la menor distancia conocida, y actualizamos las distancias de sus vecinos.\n\n";

        for (int paso = 0; paso < n - 1; paso++) {
            int minDist = INT_MAX, u = -1;
            for (int i = 0; i < n; i++) {
                if (!visitado[i] && distancia[i] <= minDist) {
                    minDist = distancia[i];
                    u = i;
                }
            }

            if (u == -1) break; 

            visitado[u] = true;

            setColor(11);
            cout << "\nPaso " << paso + 1 << ": Nodo seleccionado para explorar -> " << char('A' + u) << "\n";
            setColor(7);
            cout << "Explicación: Este nodo tiene la menor distancia conocida no visitada (" << distancia[u] << ").\n";

            for (int v = 0; v < n; v++) {
                if (matriz[u][v] && !visitado[v] && distancia[u] != INT_MAX) {
                    if (distancia[u] + matriz[u][v] < distancia[v]) {
                        distancia[v] = distancia[u] + matriz[u][v];
                        predecesores[v].clear();
                        predecesores[v].push_back(u);

                        setColor(14);
                        cout << "  - Actualizando distancia de " << char('A' + v) << " a " << distancia[v] << " (nuevo camino mas corto desde " << char('A' + u) << ")\n";
                        setColor(7);
                    }
                    else if (distancia[u] + matriz[u][v] == distancia[v]) {
                        predecesores[v].push_back(u);

                        setColor(13);
                        cout << "  - Encontrado otro camino de igual distancia para " << char('A' + v) << " desde " << char('A' + u) << "\n";
                        setColor(7);
                    }
                }
            }

            cout << "\nDistancias actuales:\n";
            for (int i = 0; i < n; i++) {
                if (visitado[i]) setColor(10);
                else if (distancia[i] == INT_MAX) setColor(8);
                else setColor(14);

                cout << "  " << char('A' + i) << " : ";
                if (distancia[i] == INT_MAX) cout << "∞\n";
                else cout << distancia[i] << "\n";
                setColor(7);
            }

            cout << "---------------------------------------------\n";
            Sleep(1000);
        }

        if (distancia[destino] == INT_MAX) {
            cout << "\nNo hay caminos desde " << char('A' + inicio) << " a " << char('A' + destino) << "\n";
            return;
        }

        cout << "\n🔹 TODOS LOS CAMINOS MINIMOS DESDE " << char('A' + inicio) << " HASTA " << char('A' + destino) << " (Distancia minima: " << distancia[destino] << ") 🔹\n";

        vector<int> camino;
        imprimirCaminosRec(destino, inicio, predecesores, camino);

        cout << endl;
    }
};

