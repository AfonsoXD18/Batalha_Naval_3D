// g++ -std=c++11 Batalha_Naval_3D/teste3.cpp -o teste3; ./teste3
// g++ -std=c++11 teste3.cpp -o teste3; ./teste3

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Estado do jogo
bool jogoEmCurso = false;
bool espacamentoObrigatorio = false;

const int SIZE = 10;
// Declaração do tabuleiro 3D
vector<vector<vector<int>>> tabuleiro1(SIZE, vector<vector<int>>(SIZE, vector<int>(SIZE, 0)));
vector<vector<vector<int>>> tabuleiro2(SIZE, vector<vector<int>>(SIZE, vector<int>(SIZE, 0)));

void colocarNAVE(int x, int y, int z, int nave, int orientacao, vector<vector<vector<int>>> tabuleiro){ //Garantir que a nave cabe
    if (x<0 || x>=SIZE || y<0 || y>=SIZE || z<0 || z>=SIZE){
        switch (orientacao){
            case 0: // Horizontal direito --->
                for (int i  = 0; i < nave; i++){
                    tabuleiro[x+i][y][z] = 1;
                }
                break;
            case 1: // Horizontal esquerdo --->
                for (int i  = 0; i < nave; i++){
                    tabuleiro[x-i][y][z] = 1;
                }
                break;
            case 2: // vertical cima --->
                for (int i  = 0; i < nave; i++){
                    tabuleiro[x][y+i][z] = 1;
                }
                break;
            case 3: // vertical baixo --->
                for (int i  = 0; i < nave; i++){
                    tabuleiro[x][y-i][z] = 1;
                }
                break;
            case 4: // Profundidade lá --->
                for (int i  = 0; i < nave; i++){
                    tabuleiro[x][y][z+i] = 1;
                }
                break;
            case 5: // Profundidade cá --->
                for (int i  = 0; i < nave; i++){
                    tabuleiro[x][y][z-i] = 1;
                }
                break;
            default:
                cout << "Orientacao invalida.\n";
                break;
        }
    }


}
// Funções placeholder
void iniciarJogo() {
    cout << "Inserir nome do jogador1: ";
    string jogador1;
    cin >> jogador1;
    cout << "Inserir nome do jogador2: ";
    string jogador2;
    cin >> jogador2;

    // vars para guardar input
    int x, y, z, nave, orientacao;

    // Player 1
    cout << "Player 1 --> coloca as tuas babes: \n";
    for (int i = 0; i < 4; i++){
        cout << "Insira a coordenadas (x y z): ";
        cin >> x >> y >> z;
        cout << "Insira o tamanho da nave: ";   // Alterar para a pessoa meter o nome da nave e vcs tem que associar a um tamanho
        cin >> nave;
        cout << "Insira a orientacao (0: horizontal direita, 1: horizontal esquerda, 2: vertical cima, 3: vertical baixo, 4: profundidade la, 5: profundidade ca): ";
        cin >> orientacao;

        colocarNAVE(x, y, z, nave, orientacao, tabuleiro1);
        cout << "Nave colocada com sucesso!\n";
    }

    //Player 2
    cout << "Player 2 --> coloca as tuas babes: \n";
    for (int i = 0; i < 4; i++){
        cout << "Insira a coordenadas (x y z): ";
        cin >> x >> y >> z;
        cout << "Insira o tamanho da nave: ";   // Alterar para a pessoa meter o nome da nave e vcs tem que associar a um tamanho
        cin >> nave;
        cout << "Insira a orientacao (0: horizontal direita, 1: horizontal esquerda, 2: vertical cima, 3: vertical baixo, 4: profundidade la, 5: profundidade ca): ";
        cin >> orientacao;

        colocarNAVE(x, y, z, nave, orientacao, tabuleiro1);
        cout << "Nave colocada com sucesso!\n";
    }
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

    while (true) {
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
    }
}
