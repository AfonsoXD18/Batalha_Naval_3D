#ifndef GAMEUI_H
#define GAMEUI_H

#include "Tabuleiro.h"
#include "Constantes.h"

class GameUI {
private:
    Tabuleiro tabuleiroA;
    Tabuleiro tabuleiroB;
    std::string jogador;
    int camadaZ;

public:
    GameUI();

    void setup(std::string jogador, Tabuleiro tabuleiroA, Tabuleiro tabuleiroB, int camadaZ);

    void printGameUI();

    void disparar(Tabuleiro& tabuleiroObj, int x, int y, int z, int& pontuacao);
    
    void setCamadaZ(int camadaZ);

    std::vector<std::vector<std::vector<int>>>& getTabuleiro();

    std::string repetirString(const std::string& str, int vezes);
    std::string oQueImprimirLinha(int x, Tabuleiro tabuleiroBom, Tabuleiro tabuleiroMau, std::string jogador, int camada); // os parâmetros corretos

};

#endif