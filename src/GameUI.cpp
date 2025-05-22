#include "GameUI.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Constantes.h"

//construtor default
GameUI::GameUI(){
}

void GameUI::setup(std::string jogador, Tabuleiro* tabuleiroA, Tabuleiro* tabuleiroB, int camadaZ) {
    this->tabuleiroA = tabuleiroA;
    this->tabuleiroB = tabuleiroB;
    this->jogador = jogador;
    this->camadaZ = camadaZ;
}

void GameUI::printGameUI() {
    std::string titulo = "╔════════════════════════════════════════════╣ " + jogador + " ╠════════════════════════════════════════════╗\n";
    std::string empty = "║                                                         " + std::string(jogador.size(), ' ') + "                                   ║\n";
    std::string cabecalho = "║    Meu Tabuleiro:                              " + std::string(jogador.size(), ' ') + " Tabuleiro Inimigo:                         ║\n";
    std::string valores = "║     Y   1   2   3   4   5   6   7   8   9      " + std::string(jogador.size(), ' ') + "  Y   1   2   3   4   5   6   7   8   9     ║\n";   //41 caracteres para fazer tabuleiro    
    std::string tabuleiroIni = "║   ┏━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┓    " + std::string(jogador.size(), ' ') + "┏━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┓   ║\n";   //41 caracteres para fazer tabuleiro    
    std::string tabuleiroStr = "║   ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫    " + std::string(jogador.size(), ' ') + "┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫   ║\n";
    std::string tabuleiroEnd = "║   ┗━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┛    " + std::string(jogador.size(), ' ') + "┗━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┛   ║\n";
    std::string fim = "╚═════════════════════════════════════════════════" + repetirString("═", jogador.size()) + "═══════════════════════════════════════════╝\n";

    std::cout << titulo;
    std::cout << empty;
    std::cout << cabecalho;
    std::cout << empty;
    std::cout << valores;
    std::cout << tabuleiroIni;
    std::cout << "║ X " << oQueImprimirLinha(0, tabuleiroA, tabuleiroB, jogador, camadaZ) << " X ║\n";
    std::cout << tabuleiroStr;
    std::cout << "║ 1 " << oQueImprimirLinha(1, tabuleiroA, tabuleiroB, jogador, camadaZ) << " 1 ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 2 " << oQueImprimirLinha(2, tabuleiroA, tabuleiroB, jogador, camadaZ) << " 2 ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 3 " << oQueImprimirLinha(3, tabuleiroA, tabuleiroB, jogador, camadaZ) << " 3 ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 4 " << oQueImprimirLinha(4, tabuleiroA, tabuleiroB, jogador, camadaZ) << " 4 ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 5 " << oQueImprimirLinha(5, tabuleiroA, tabuleiroB, jogador, camadaZ) << " 5 ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 6 " << oQueImprimirLinha(6, tabuleiroA, tabuleiroB, jogador, camadaZ) << " 6 ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 7 " << oQueImprimirLinha(7, tabuleiroA, tabuleiroB, jogador, camadaZ) << " 7 ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 8 " << oQueImprimirLinha(8, tabuleiroA, tabuleiroB, jogador, camadaZ) << " 8 ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 9 " << oQueImprimirLinha(9, tabuleiroA, tabuleiroB, jogador, camadaZ) << " 9 ║\n";
    std::cout << tabuleiroEnd;
    std::cout << empty;
    std::cout << fim;
}

/* FUNÇÕES AUXILIARES */

std::string GameUI::oQueImprimirLinha(int x, Tabuleiro* tabuleiroBom, Tabuleiro* tabuleiroMau, std::string jogador, int camada) {
    std::ostringstream oss;
    std::vector<std::vector<std::vector<int>>>& tabBOM = tabuleiroBom->getTabuleiro();
    std::vector<std::vector<std::vector<int>>>& tabMAU = tabuleiroMau->getTabuleiro();

    // Tabuleiro do player em questão
    for (int i = 0; i < SIZE; i++) {
        int valor = tabBOM[x][i][camada];
        std::string placement = "";
        switch (valor){
            case 0: placement = " "; break;
            case 1: placement = "🚀"; break;
            case 2: placement = "💥"; break;
            case 3: placement = "❌"; break;
            default: return "⚠️";
        }
        oss << "┃" << std::setw(2) << std::setfill(' ') << placement << " ";
    }
    oss << "┃";
    oss << "    " + std::string(jogador.size(), ' ');

    // Tabuleiro do inimigo
    for (int i = 0; i < SIZE; i++) {
        int valor = tabMAU[x][i][camada];
        std::string placement = "";
        switch (valor){
            case 0: placement = " "; break;
            case 1: placement = " "; break; // Não mostra naves inimigas
            case 2: placement = "💥"; break;
            case 3: placement = "❌"; break;
            default: return "⚠️";
        }
        oss << "┃" << std::setw(2) << std::setfill(' ') << placement << " ";
    }
    oss << "┃";
    return oss.str();
}

std::string GameUI::repetirString(const std::string& s, int n) {
    std::string resultado;for (int i = 0; i < n; ++i) resultado += s;
    return resultado;
}

void GameUI::setCamadaZ(int camadaZ) {
    this->camadaZ = camadaZ;
}