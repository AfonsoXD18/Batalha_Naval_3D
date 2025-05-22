#ifndef GAMEUI_H
#define GAMEUI_H

#include "Tabuleiro.h"
#include "Constantes.h"

class GameUI {
public:
    GameUI();
    void setup(std::string jogador, Tabuleiro* tabuleiroA, Tabuleiro* tabuleiroB, int camadaZ);
    void printGameUI();
    std::string repetirString(const std::string& s, int n);
    void setCamadaZ(int camadaZ);
    std::string oQueImprimirLinha(int x, Tabuleiro* tabuleiroBom, Tabuleiro* tabuleiroMau, std::string jogador, int camada);
private:
    Tabuleiro* tabuleiroA;
    Tabuleiro* tabuleiroB;
    std::string jogador;
    int camadaZ;
};

#endif