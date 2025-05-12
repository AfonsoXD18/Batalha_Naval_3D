// g++ -std=c++11 batalha.cpp -o batalha; ./batalha
// Batalha Naval 3D - Estrutura Inicial do Projeto
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const int SIZE = 10;

// Tipos de naves
enum TipoNave { CACAS, FRAGATA, CONTRATORPEDEIRO, CRUZADOR, NAVE_MAE };

// Representa uma coordenada no espaço 3D
struct Coordenada {
    int x, y, z;
};

// Representa uma nave no tabuleiro
class Nave {
public:
    TipoNave tipo;
    vector<Coordenada> posicoes;
    vector<bool> atingida;

    Nave(TipoNave tipo, const vector<Coordenada>& pos) : tipo(tipo), posicoes(pos) {
        atingida = vector<bool>(pos.size(), false);
    }

    bool estaAfundada() const {
        for (bool a : atingida) if (!a) return false;
        return true;
    }

    bool verificarImpacto(const Coordenada& disparo) {
        for (size_t i = 0; i < posicoes.size(); ++i) {
            if (posicoes[i].x == disparo.x && posicoes[i].y == disparo.y && posicoes[i].z == disparo.z) {
                atingida[i] = true;
                return true;
            }
        }
        return false;
    }
};

// Representa um jogador
class Jogador {
public:
    string nomeGuerra;
    vector<Nave> frota;
    bool tabuleiro[SIZE][SIZE][SIZE] = {{{false}}};

    void adicionarNave(const Nave& nave) {
        for (const auto& c : nave.posicoes) {
            tabuleiro[c.x][c.y][c.z] = true;
        }
        frota.push_back(nave);
    }

    bool processarDisparo(char eixo, int c1, int c2) {
        bool houveImpacto = false;
        for (int i = 0; i < SIZE; ++i) {
            Coordenada alvo;
            if (eixo == 'X') alvo = {i, c1, c2};
            else if (eixo == 'Y') alvo = {c1, i, c2};
            else alvo = {c1, c2, i};

            for (auto& nave : frota) {
                if (nave.verificarImpacto(alvo)) {
                    cout << "Impacto em (" << alvo.x << "," << alvo.y << "," << alvo.z << ")\n";
                    houveImpacto = true;
                }
            }
        }
        return houveImpacto;
    }
};

// Função para mostrar o menu principal
void mostrarMenu() {
    cout << "=== Batalha Naval 3D ===\n";
    cout << "1. Iniciar jogo\n";
    cout << "2. Configuracao\n";
    cout << "3. Mostrar historico\n";
    cout << "4. Sair\n";
}

int main() {
    srand(time(0));
    mostrarMenu();
    // Aqui entra a lógica principal do jogo
    return 0;
}
// puta