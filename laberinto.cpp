#include <iostream>
using namespace std;

int main() {
char mapa[27][66] = {
"################################################################",
"#P#       #       #       #       #       #       #       #     #",
"# # ##### # ##### # ##### # ##### # ##### # ##### # ##### ### # #",
"# # #   # #     # #     # #     # #     # #     # #     #     # #",
"# # # # # ##### # ##### # ##### # ##### # ##### # ##### ##### # #",
"# #   # #     # #     # #     # #     # #     # #     #     # # #",
"# ##### ##### # ##### # ##### # ##### # ##### # ##### ##### # # #",
"#     #     # #     # #     # #     # #     # #     #     # # # #",
"##### ##### # ##### # ##### # ##### # ##### # ##### ##### # # # #",
"#   #     # #     # #     # #     # #     # #     #     # # # # #",
"# # ##### # ##### # ##### # ##### # ##### # ##### ##### # # # # #",
"# #     # #     # #     # #     # #     # #     #     # # #   # #",
"# ##### # ##### # ##### # ##### # ##### # ##### ##### # ##### # #",
"#     # #     # #     # #     # #     # #     #     # #     # # #",
"##### # ##### # ##### # ##### # ##### # ##### ##### # ##### # # #",
"#     #     # #     # #     # #     # #     #     # #     # #   #",
"# ##### ##### # ##### # ##### # ##### # ##### ##### ##### ##### #",
"#     #     # #     # #     # #     # #     #     #     #     # #",
"# ### ##### # ##### # ##### # ##### # ##### ##### ##### ##### # #",
"#   #     # #     # #     # #     # #     #     #     #     # # #",
"# # ##### # ##### # ##### # ##### # ##### ##### ##### ##### # # #",
"# #     # #     # #     # #     # #     #     #     #     # #   #",
"# ##### # ##### # ##### # ##### # ##### ##### ##### ##### ##### #",
"#     # #     # #     # #     # #     #     #     #     #     # #",
"##### # ##### # ##### # ##### # ##### ##### ##### ##### ##### # #",
"#     #       #       #       #       #       #       #       E#",
"################################################################"
};



    int x = 1, y = 1;
    // inicio de temporizador
    clock_t inicio = clock(); 

    while (true) {
        // limpiar pantalla (ANSI)
        cout << "\033[2J\033[1;1H";

        // imprimir mapa
        for (int i = 0; i < 27; i++) {
            cout << mapa[i] << endl;
        }
        
        double tiempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;

        // input
        char mov;
        cout << "\nTiempo: " << tiempo << " segundos\n";
        cout << "Movimiento (WASD) oprimir (Enter) por tecla: ";
        cin >> mov;

        int nx = x;
        int ny = y;

        // calcular nueva posición
        if (mov == 'w') ny--;
        if (mov == 's') ny++;
        if (mov == 'a') nx--;
        if (mov == 'd') nx++;

        // mirar qué hay en la celda destino
        char celdaDestino = mapa[ny][nx];

        // validar movimiento
        if (celdaDestino != '#') {
            mapa[y][x] = ' ';
            x = nx;
            y = ny;

            if (celdaDestino != 'E')
                mapa[y][x] = 'P';
        }

        // verificar victoria
        if (celdaDestino == 'E') {
            cout << "\033[2J\033[1;1H";
            cout << "Ganaste\n";
            cout << "Tiempo total: " << tiempoFinal << " segundos\n";
            cin.get();
            cin.get();
            break;
        }
    }

    return 0;
}
