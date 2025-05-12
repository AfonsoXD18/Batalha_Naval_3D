// g++ -std=c++11 Batalha_Naval_3D/teste3.cpp -o teste3; ./teste3
#include <iostream>
#include <string>

using namespace std;

// Estado do jogo
bool jogoEmCurso = false;
bool espacamentoObrigatorio = false;

// Funções placeholder
void iniciarJogo() {
    cout << "\n[Iniciar Jogo]\n";
    // Aqui será implementada a lógica de preparação e execução do jogo
    jogoEmCurso = true;
    cout << "Inicio do jogo.\n";
}

void configuracoes() {
    cout << "\n[Configuracoes do Jogo]\n";
    cout << "Espaço obrigatório entre naves (atualmente "
         << (espacamentoObrigatorio ? "ATIVO" : "INATIVO") << ").\n";
    cout << "Deseja alterar esta configuracao? (s/n): ";
    char resposta;
    cin >> resposta;
    if (resposta == 's' || resposta == 'S') {
        espacamentoObrigatorio = !espacamentoObrigatorio;
        cout << "Configuracao atualizada com sucesso.\n";
    }
}

void mostrarHistorico() {
    cout << "\n[Historico de Jogos]\n";
    // Aqui será implementada a leitura do histórico de ficheiro
    cout << "Historico ainda nao implementado.\n";
}

bool confirmarSaida() {
    cout << "\nTem a certeza que deseja sair? (s/n): ";
    char resposta;
    cin >> resposta;
    if (resposta == 's' || resposta == 'S') {
        if (jogoEmCurso) {
            cout << "Nota: o jogo ainda esta em curso.\n";
        }
        return true;
    }
    return false;
}

int main() {
    int opcao;

    do {
        cout << "+----- MENU PRINCIPAL - BATALHA NAVAL 3D -----+\n";
        cout << "|   1. Iniciar jogo                           |\n";
        cout << "|   2. Configuracao                           |\n";
        cout << "|   3. Mostrar historico                      |\n";
        cout << "|   4. Sair                                   |\n";
        cout << "+---------------------------------------------+\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                iniciarJogo();
                break;
            case 2:
                configuracoes();
                break;
            case 3:
                mostrarHistorico();
                break;
            case 4:
                if (confirmarSaida()) {
                    cout << "A sair do jogo...\n";
                    return 0;
                }
                break;
            default:
                cout << "Opção invalida. Tente novamente.\n";
        }
    } while (true);
}
