#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <vector>
#include "Constantes.h"
#include "Jukebox.h"

class Tabuleiro {
private:
    std::vector<std::vector<std::vector<int>>> tabuleiro;

public:
    Tabuleiro();

    bool colocarNave(int x, int y, int z, int tamanho, int orientacao);
    bool colocarNaveMae(int x, int y, int z);

    void disparar(int x, int y, int z, int& pontuacao);

    std::vector<std::vector<std::vector<int>>>& getTabuleiro();

    void tocarSom(const std::string& som);
};

#endif