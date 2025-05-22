#include "Tabuleiro.h"
#include <iostream>
#include "Constantes.h"
#include "Jukebox.h"

//constutor
Tabuleiro::Tabuleiro() {
    tabuleiro = std::vector<std::vector<std::vector<int>>>(SIZE, std::vector<std::vector<int>>(SIZE, std::vector<int>(SIZE, 0)));
}

std::vector<std::vector<std::vector<int>>>& Tabuleiro::getTabuleiro() {
    return tabuleiro;
}
// Coloca uma nave no tabuleiro
// x, y, z: coordenadas da célula onde a nave deve ser colocada
// tamanho: tamanho da nave (1, 2, 3 ou 4)
// orientacao: direção da nave (0: +z, 1: -z, 2: +y, 3: -y, 4: +x, 5: -x)
// Retorna true se a nave foi colocada com sucesso, false caso contrário
bool Tabuleiro::colocarNave(int x, int y, int z, int tamanho, int orientacao) {
    // Definir direção com base na orientação
    int dx = 0, dy = 0, dz = 0;
    switch (orientacao) {
        case 0: dz = 1; break;  // +z
        case 1: dz = -1; break; // -z
        case 2: dy = 1; break;  // +y
        case 3: dy = -1; break; // -y
        case 4: dx = 1; break;  // +x
        case 5: dx = -1; break; // -x
        default: return false;
    }

    int nx = tabuleiro.size();
    int ny = tabuleiro[0].size();
    int nz = tabuleiro[0][0].size();

    // Verifica se a nave cabe e não sobrepõe outras naves
    for (int i = 0; i < tamanho; i++) {
        int xi = x + dx * i;
        int yi = y + dy * i;
        int zi = z + dz * i;

        // Verificação de limites
        if (xi < 0 || xi >= nx || yi < 0 || yi >= ny || zi < 0 || zi >= nz)
            return false;

        // Verifica sobreposição
        if (tabuleiro[xi][yi][zi] != 0)
            return false;
    }

    // Coloca a nave
    for (int i = 0; i < tamanho; i++) {
        int xi = x + dx * i;
        int yi = y + dy * i;
        int zi = z + dz * i;
        tabuleiro[xi][yi][zi] = 1;
        std::cout << "Nave colocada em: (" << xi << ", " << yi << ", " << zi << ")\n";
    }

    return true;
}

bool Tabuleiro::colocarNaveMae(int x, int y, int z) {
    // Usa a constante SIZE definida em Constantes.h

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            for (int k = -1; k <= 1; k++) {
                int xi = x + i;
                int yj = y + j;
                int zk = z + k;

                if (xi < 0 || xi >= SIZE || yj < 0 || yj >= SIZE || zk < 0 || zk >= SIZE)
                    return false;

                if (tabuleiro[xi][yj][zk] != 0)
                    return false;
            }
        }
    }

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            for (int k = -1; k <= 1; k++) {
                tabuleiro[x + i][y + j][z + k] = 1;
            }
        }
    }

    return true;
}

void Tabuleiro::disparar(int x, int y, int z, int& pontuacao) {
    bool acertou = false;
    Jukebox jukebox = Jukebox();

    // Se x == 0, o ataque percorre o eixo X
    if (x == 0) {
        for (int i = 0; i < SIZE; ++i) {
            if (tabuleiro[i][y][z] == 1) {
                jukebox.tocarSom(somExplosao);
                tabuleiro[i][y][z] = 2;
                pontuacao++;
                acertou = true;
            } else if (tabuleiro[i][y][z] == 0) {
                tabuleiro[i][y][z] = 3;
            }
        }
    }
    // Se y == 0, o ataque percorre o eixo Y
    else if (y == 0) {
        for (int i = 0; i < SIZE; ++i) {
            if (tabuleiro[x][i][z] == 1) {
                jukebox.tocarSom(somExplosao);
                tabuleiro[x][i][z] = 2;
                pontuacao++;
                acertou = true;
            } else if (tabuleiro[x][i][z] == 0) {
                tabuleiro[x][i][z] = 3;
            }
        }
    }
    // Se z == 0, o ataque percorre o eixo Z
    else if (z == 0) {
        for (int i = 0; i < SIZE; ++i) {
            if (tabuleiro[x][y][i] == 1) {
                jukebox.tocarSom(somExplosao);
                tabuleiro[x][y][i] = 2;
                pontuacao++;
                acertou = true;
            } else if (tabuleiro[x][y][i] == 0) {
                tabuleiro[x][y][i] = 3;
            }
        }
    }

    if (acertou) {
        std::cout << "🎯 Acertaste numa nave!\n";
    } else {
        std::cout << "💦 Não acertaste em nada...\n";
    }
}
