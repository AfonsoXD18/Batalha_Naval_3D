// Este ficheiro é a versão do jão! please não mexam :))
// Compilar com: g++ -std=c++14 jao.cpp -o jao; ./jao

#include <sstream>
#include <iomanip>
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
std::string oQueImprimirLinha(int x, int y, std::vector<std::vector<std::vector<int>>> tabuleiroBom, std::vector<std::vector<std::vector<int>>> tabuleiroMau, std::string jogador);
std::string repetirString(const std::string& s, int n);

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

void gameUI(std::string jogador = "Jogador", std::vector<std::vector<std::vector<int>>> tabuleiro) {
    std::string titulo = "╔══════════════════════════════════════════╣ " + jogador + " ╠══════════════════════════════════════════╗\n";
    std::string empty = "║                                                       " + std::string(jogador.size(), ' ') + "                                 ║\n";
    std::string cabecalho = "║  Meu Tabuleiro:                              " + std::string(jogador.size(), ' ') + " Tabuleiro Inimigo:                       ║\n";
    std::string tabuleiroIni = "║ ┏━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┓    " + std::string(jogador.size(), ' ') + "┏━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┓ ║\n";   //41 caracteres para fazer tabuleiro    
    std::string tabuleiroStr = "║ ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫    " + std::string(jogador.size(), ' ') + "┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫ ║\n";
    std::string tabuleiroEnd = "║ ┗━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┛    " + std::string(jogador.size(), ' ') + "┗━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┛ ║\n";
    std::string fim = "╚═══════════════════════════════════════════════" + repetirString("═", jogador.size()) + "═════════════════════════════════════════╝\n";

    std::cout << titulo;
    std::cout << empty;
    std::cout << cabecalho;
    std::cout << tabuleiroIni;
    std::cout << "║ " + oQueImprimirLinha(0,0, tabuleiro1, tabuleiro2, jogador) + " ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ " + oQueImprimirLinha(1,0, tabuleiro1, tabuleiro2, jogador) + " ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ " + oQueImprimirLinha(2,0, tabuleiro1, tabuleiro2, jogador) + " ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ " + oQueImprimirLinha(3,0, tabuleiro1, tabuleiro2, jogador) + " ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ " + oQueImprimirLinha(4,0, tabuleiro1, tabuleiro2, jogador) + " ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ " + oQueImprimirLinha(5,0, tabuleiro1, tabuleiro2, jogador) + " ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ " + oQueImprimirLinha(6,0, tabuleiro1, tabuleiro2, jogador) + " ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ " + oQueImprimirLinha(7,0, tabuleiro1, tabuleiro2, jogador) + " ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ " + oQueImprimirLinha(8,0, tabuleiro1, tabuleiro2, jogador) + " ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ " + oQueImprimirLinha(9,0, tabuleiro1, tabuleiro2, jogador) + " ║\n";
    std::cout << tabuleiroEnd;
    std::cout << empty;
    std::cout << fim;
}


/* FUNCOES AUXILIARES */
std::string oQueImprimirLinha(int x, int y, std::vector<std::vector<std::vector<int>>> tabuleiroBom, std::vector<std::vector<std::vector<int>>> tabuleiroMau, std::string jogador) {
    std::ostringstream oss;
    // tabuleiro do player em questão
    for (int i = 0; i < SIZE; i++) {
        int valor = tabuleiroBom[x][y][i];

        // Formata cada valor com largura 3 para alinhar (como " 5 ", "10 ", etc.)
        oss << "┃" << std::setw(2) << std::setfill(' ') << valor << " ";
    }
    oss << "┃";  // Fecha a última barra
    oss << "    " + std::string(jogador.size(), ' ');
    
    //Tabuleiro do inimigo
    for (int i = 0; i < SIZE; i++) {
        int valor = tabuleiroMau[x][y][i];

        // Formata cada valor com largura 3 para alinhar (como " 5 ", "10 ", etc.)
        oss << "┃" << std::setw(2) << std::setfill(' ') << valor << " ";
    }
    oss << "┃";  // Fecha a última barra

    return oss.str();
}

std::string repetirString(const std::string& s, int n) {
    std::string resultado;for (int i = 0; i < n; ++i) resultado += s;
    return resultado;
}
