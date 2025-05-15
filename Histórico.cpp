#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // Para setw
using namespace std;
// Armazena os resultados
struct Jogo {
    string jogador1;
    string jogador2;
    int resultado1; // Vitórias do jogador 1
    int resultado2; // Vitórias do jogador 2
    string data; // Data do jogo
};

// Classe para os resultados dos jogos
class HistoricoJogos {
private:
    vector<Jogo> jogos;
    const int maxJogos = 100;

public:
    // Adiciona um novo jogo ao histórico
    void adicionarJogo(const string& jogador1, const string& jogador2, int resultado1, int resultado2, const string& data) {
        if (jogos.size() >= maxJogos) {
            jogos.erase(jogos.begin()); // Remove o jogo mais antigo
        }
        jogos.push_back({jogador1, jogador2, resultado1, resultado2, data});
    }

    // Exibe a tabela de resultados
    void exibirResultados() const {
        cout << setw(20) << "Jogador 1" 
                  << setw(20) << "Jogador 2" 
                  << setw(10) << "Resultado 1" 
                  << setw(10) << "Resultado 2" 
                  << setw(15) << "Data" << endl;

        cout << string(85, '-') << endl;

        for (const auto& jogo : jogos) {
            cout << setw(20) << jogo.jogador1 
                 << setw(20) << jogo.jogador2 
                 << setw(10) << jogo.resultado1 
                 << setw(10) << jogo.resultado2 
                 << setw(15) << jogo.data << endl;
        }
    }
};

int main() {
    HistoricoJogos historico;

    // Adicionando alguns jogos ao histórico
    historico.adicionarJogo("Jogador A", "Jogador B", 3, 2, "2024-01-01");
    historico.adicionarJogo("Jogador C", "Jogador D", 1, 4, "2024-01-02");
    historico.adicionarJogo("Jogador E", "Jogador F", 0, 0, "2024-01-03");

    // Exibindo os resultados
    historico.exibirResultados();

    return 0;
}