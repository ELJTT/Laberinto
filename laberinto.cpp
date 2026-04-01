#include <iostream>
#include <conio.h>   // _kbhit(), _getch()
#include <ctime>     // clock()
#include <windows.h> // Sleep()
using namespace std;

int main() {
    char mapa[27][66] = {
        "################################################################",
        "#P#       #       #       #       #       #       #       #     #",
        "# # ##### # ##### # ##### # ##### # ##### # ##### # ##### ### # #",
        "# # #   # #     # #     # #     # #     # #     # #     #     # #",
        "# # # # # ##### # ##### # ##### # ##### # ##### # ##### ##### # #",
        "# #   # #     # #     # #       #     # #     # #     #     # # #",
        "# ##### ##### # ##### # ##### # ##### # ##### # ##### ##### # # #",
        "#     #     # #     # #     # #     # #     # #     #     # # # #",
        "##### ##### # ##### # ##### # ##### # ##### # # ### ##### # # # #",
        "#   #     # #       #     # #     # #     # #     #     # # # # #",
        "# # ##### # ##### # ##### # ##### # ##### # ##### ##### # # # # #",
        "# #     # #     # #     # #     #       # #     #     # # #   # #",
        "# ##### # ##### # ##### # ##### # ##### # ##### ##### # ##### # #",
        "#     # #     # #     # #     # #     # #     #     # #     # # #",
        "##### # ##### # ##### # ##### # ##### # ## ## ##### # ##### # # #",
        "#     #     # #     # #     # #     # #     #     # #     # #   #",
        "# ##### ##### # ##### # ##### # ##### # ##### ##### ##### ##### #",
        "#     #     # #     # #     # #     # #     #     #     #     # #",
        "# ### ##### # ##### # ##### # ##### # ## ## ##### ##### ##### # #",
        "#   #     # #       #     #         #     #     #     #     # # #",
        "# # ##### # ##### # ##### # ##### # ##### ##### ##### ##### # # #",
        "# #     # #     # #     # #     # #     #     #     #     # #   #",
        "# ##### # ##### # ##### # ##### # ##### ##### ##### ##### ##### #",
        "#     # #     # #     # #     # #     #     #     #     #     # #",
        "##### # ##### # ##### # ##### # ##### ##### ##### ##### ##### # #",
        "#     #       #       #       #       #       #       #       E#",
        "################################################################"
    };

    int x = 1, y = 1;

    // Aseguramos que el mapa original no tenga la "P" extra; la dibujamos dinámicamente.
    mapa[y][x] = ' ';

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cursorInfo);

    clock_t inicio = clock(); // ⏱️ iniciar cronómetro

    while (true) {
        // Ubica cursor en inicio para redibujar sin parpadeo de cls.
        COORD coord = {0, 0};
        SetConsoleCursorPosition(hOut, coord);

        // imprimir mapa con jugador en x,y
        for (int i = 0; i < 27; i++) {
            for (int j = 0; j < 66; j++) {
                char celda = mapa[i][j];
                if (i == y && j == x) {
                    cout << 'P';
                } else if (celda == 'P') {
                    cout << ' ';
                } else {
                    cout << celda;
                }
            }
            cout << endl;
        }
        double tiempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
        cout << "\nTiempo: " << tiempo << " segundos\n";

        cout << "Usa WASD para moverte (o flechas)." << endl;

        int nx = x;
        int ny = y;

        // detectar tecla sin Enter con movimiento por teclas WASD o flechas
        if (_kbhit()) {
            int key = _getch();

            if (key == 0 || key == 224) {
                key = _getch();
                if (key == 72) ny--; // flecha arriba
                if (key == 80) ny++; // flecha abajo
                if (key == 75) nx--; // flecha izquierda
                if (key == 77) nx++; // flecha derecha
            } else {
                if (key == 'w' || key == 'W') ny--;
                if (key == 's' || key == 'S') ny++;
                if (key == 'a' || key == 'A') nx--;
                if (key == 'd' || key == 'D') nx++;
            }
        }

        // Limitar al área del mapa
        if (nx < 0) nx = 0;
        if (ny < 0) ny = 0;
        if (nx >= 66) nx = 65;
        if (ny >= 27) ny = 26;

        char celdaDestino = mapa[ny][nx];

        if (celdaDestino != '#') {
            x = nx;
            y = ny;
        }

        if (celdaDestino == 'E') {
            SetConsoleCursorPosition(hOut, coord);
            cout << "\n🎉 Ganaste!\n";
            double tiempoFinal = (double)(clock() - inicio) / CLOCKS_PER_SEC;
            cout << "Tiempo total: " << tiempoFinal << " segundos\n";
            break;
        }

        Sleep(35); // aproximadamente 28 FPS para movimiento suave
    }

    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hOut, &cursorInfo);

    return 0;
}
