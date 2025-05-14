// Este ficheiro é a versão do jão! please não mexam :))
// Compilar com: g++ -std=c++14 jao.cpp -o jao; ./jao

#include <iostream>
#include <vector>

// Constantes + Variáveis globais
const int SIZE = 10;

std::vector<std::vector<std::vector<int>>> tabuleiro1 (SIZE, std::vector<std::vector<int>>(SIZE, std::vector<int>(SIZE, 0))); // --> Tabuleiro Player 1
std::vector<std::vector<std::vector<int>>> tabuleiro2 (SIZE, std::vector<std::vector<int>>(SIZE, std::vector<int>(SIZE, 0))); // --> Tabuleiro Player 2

//Declarar funções
int menu();
void prepJogo();
void gameUI(std::string jogador1, std::vector<std::vector<std::vector<int>>> tabuleiro = tabuleiro1);

int main() {
    menu();
    return 0;
}

int menu(){  // Menu com caracteres UTF-8 de box
    while (true){
        std::cout << "╔═════╣ BATALHA NAVAL 3D ╠═════╗\n";
        std::cout << "║   1. Iniciar jogo            ║\n";
        std::cout << "║   2. Configuração            ║\n";
        std::cout << "║   3. Mostrar histórico       ║\n";
        std::cout << "║   4. Sair                    ║\n";
        std::cout << "╚══════════════════════════════╝\n";
        std::cout << "Escolha uma opcão: ";
        
        std::string opcao;
        std::cin >> opcao;

        if (opcao == "1"){
            std::cout << "\n\n\n";
            prepJogo();
        } else if (opcao == "2"){
            std::cout << "\n\n\n";
            //configuracoes();
        } else if (opcao == "3"){
            std::cout << "\n\n\n";
            //mostrarHistorico();
        } else if (opcao == "4"){
            return 0;
        } else {
            std::cout << "\n\n⚠️ Opção inválida! Tente novamente.⚠️\n";
        }
    }
}

void prepJogo(){
    // Pedir input do Player1
    std::cout << "Insira o nome do jogador 1: ";
    std::string jogador1;
    std::cin >> jogador1;

    // Pedir input para colocar as naves do Player1
    gameUI(jogador1);
    std::string phrase = jogador1 + " coloca as tuas naves: \n";
    std::cout << phrase;

    // Assume-se que o jogador coloca as naves corretamente

    // Pedir input do Player2
    std::cout << "Insira o nome do jogador 2: ";
    std::string jogador2;
    std::cin >> jogador2;

    // Pedir input para colocar as naves do Player2
    gameUI(jogador2);
    phrase = jogador2 + " coloca as tuas naves: \n";
    std::cout << phrase;





}

void gameUI(std::string jogador1 = "Jogador 1", std::vector<std::vector<std::vector<int>>> tabuleiro) {
    std::string titulo = "╔══════════════════════════════════╣ " + jogador1 + " ╠══════════════════════════════════╗\n";
    std::cout << titulo;
    std::cout << "║                                                                            ║\n";
    std::cout << "║  Meu Tabuleiro:                                                            ║\n";
    std::cout << "║ ┏━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┓                                  ║\n";

    std::string tabuleiroStr = "║ ┃ 0 ┃ 1 ┃ 2 ┃ 3 ┃ 4 ┃ 5 ┃ 6 ┃ 7 ┃ 8 ┃ 9 ┃                                  ║\n";
    std::cout << tabuleiroStr;
    std::cout << "║ ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫                                  ║\n";
    std::cout << tabuleiroStr;
    std::cout << "║ ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫                                  ║\n";
    std::cout << tabuleiroStr;
    std::cout << "║ ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫                                  ║\n";
    std::cout << tabuleiroStr;
    std::cout << "║ ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫                                  ║\n";
    std::cout << tabuleiroStr;
    std::cout << "║ ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫                                  ║\n";
    std::cout << tabuleiroStr;
    std::cout << "║ ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫                                  ║\n";
    std::cout << tabuleiroStr;
    std::cout << "║ ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫                                  ║\n";
    std::cout << tabuleiroStr;
    std::cout << "║ ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫                                  ║\n";
    std::cout << tabuleiroStr;
    std::cout << "║ ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫                                  ║\n";
    std::cout << tabuleiroStr;
    std::cout << "║ ┗━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┛                                  ║\n";

    std::cout << "║                                                                            ║\n";
    std::cout << "║                                                                            ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════════════════════╝\n";
}