#include <iostream>
using namespace std;
const int SIZE = 10; // Tamanho do tabuleiro 3D

// Classe para o tabuleiro
class Board {
public:
    char grid[SIZE][SIZE][SIZE]; // Tabuleiro 3D

    Board() {
        // Inicializa o tabuleiro
        for (int x = 0; x < SIZE; x++)
            for (int y = 0; y < SIZE; y++)
                for (int z = 0; z < SIZE; z++)
                    grid[x][y][z] = '.'; // '.' representa um espaço vazio
    }

    // Método para mostrar uma camada específica do tabuleiro
    void displayLayer(int z) {
        if (z < 0 || z >= SIZE) {
            cout << "Camada Z inválida!" << endl;
            return;
        }

        cout << "Camada Z = " << z << endl;
        cout << "   ";
        for (int x = 0; x < SIZE; x++) {
            cout << x << " ";
        }
        cout << endl;

        for (int y = 0; y < SIZE; y++) {
            cout << y << " | ";
            for (int x = 0; x < SIZE; x++) {
                cout << grid[x][y][z] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};

// Função principal
int main() {
    Board player1, player2; // Cria dois tabuleiros

    int z;
    cout << "Selecione a camada Z (0 a 9): ";
    cin >> z;

    // Exibe a camada selecionada para ambos os tabuleiros
    cout << "Tabuleiro do Jogador 1:" << endl;
    player1.displayLayer(z);
    cout << "Tabuleiro do Jogador 2:" << endl;
    player2.displayLayer(z);

    return 0;
}