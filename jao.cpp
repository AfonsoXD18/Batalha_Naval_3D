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
void gameUI(std::string jogador1, std::vector<std::vector<std::vector<int>>> tabuleiroA = tabuleiro1, std::vector<std::vector<std::vector<int>>> tabuleiroB = tabuleiro2);
void colocarNave(int x, int y, int z, int tamanho, int orientacao, std::vector<std::vector<std::vector<int>>>& tabuleiro);
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
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n🚢🚢🚢A começar jogo!!!🚢🚢🚢\n\n╼Insira o nome do jogador 1: ";
    std::string jogador1;
    std::cin >> jogador1;

    // Pedir input para colocar as naves do Player1
    gameUI(jogador1, tabuleiro1, tabuleiro2);
    std::string phrase = jogador1 + " vamos colocar as tuas naves!\n";
    std::cout << phrase;

    // vars para guardar input
    int x, y, z, nave, orientacao;

    // Nave Caça
    for (int i = 0; i < 4; i++){
        std::cout << "Nave: Caca (1)\n";
        nave=1;
        std::cout << "Insira a coordenadas (x y z): ";
        std::cin >> x >> y >> z;
        orientacao = 0;

        colocarNave(x, y, z, nave, orientacao, tabuleiro1);
        std::cout << "Nave colocada com sucesso!\n";
        gameUI(jogador1, tabuleiro1, tabuleiro2);
    }
    // Nave Fragata
    for (int i = 0; i < 3; i++){
        std::cout << "Nave: Fragata (2)\n";
        nave=2;
        std::cout << "Insira a coordenadas (x y z): ";
        std::cin >> x >> y >> z;
        std::cout << "Insira a orientacao (0: +z, 1: -z, 2: +y, 3: -y, 4: +x, 5: -x): ";
        std::cin >> orientacao;

        colocarNave(x, y, z, nave, orientacao, tabuleiro1);
        std::cout << "Nave colocada com sucesso!\n";
        gameUI(jogador1, tabuleiro1, tabuleiro2);
    }
    // Nave Contratorpedeiro
    for (int i = 0; i < 2; i++){
        std::cout << "Nave: Contratorpedeiro (3)\n";
        nave=3;
        std::cout << "Insira a coordenadas (x y z): ";
        std::cin >> x >> y >> z;
        std::cout << "Insira a orientacao (0: +z, 1: -z, 2: +y, 3: -y, 4: +x, 5: -x): ";
        std::cin >> orientacao;

        colocarNave(x, y, z, nave, orientacao, tabuleiro1);
        std::cout << "Nave colocada com sucesso!\n";
        gameUI(jogador1, tabuleiro1, tabuleiro2);
    }
    // Nave Cruzador
    for (int i = 0; i < 1; i++){
        std::cout << "Nave: Cruzador (4)\n";
        nave=4;
        std::cout << "Insira a coordenadas (x y z): ";
        std::cin >> x >> y >> z;
        std::cout << "Insira a orientacao (0: +z, 1: -z, 2: +y, 3: -y, 4: +x, 5: -x): ";
        std::cin >> orientacao;

        colocarNave(x, y, z, nave, orientacao, tabuleiro1);
        std::cout << "Nave colocada com sucesso!\n";
        gameUI(jogador1, tabuleiro1, tabuleiro2);
    }

    // Pedir input do Player2
    std::cout << "Insira o nome do jogador 2: ";
    std::string jogador2;
    std::cin >> jogador2;

    // Pedir input para colocar as naves do Player2
    gameUI(jogador2, tabuleiro2, tabuleiro1);
    phrase = jogador2 + " coloca as tuas naves: \n";
    std::cout << phrase;
}

void gameUI(std::string jogador = "Jogador", std::vector<std::vector<std::vector<int>>> tabuleiroA, std::vector<std::vector<std::vector<int>>> tabuleiroB) {
    std::string titulo = "\n\n╔════════════════════════════════════════════╣ " + jogador + " ╠════════════════════════════════════════════╗\n";
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
    std::cout << "║ X " + oQueImprimirLinha(0,0, tabuleiroA, tabuleiroB, jogador) + " X ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 1 " + oQueImprimirLinha(1,0, tabuleiroA, tabuleiroB, jogador) + " 1 ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 2 " + oQueImprimirLinha(2,0, tabuleiroA, tabuleiroB, jogador) + " 2 ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 3 " + oQueImprimirLinha(3,0, tabuleiroA, tabuleiroB, jogador) + " 3 ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 4 " + oQueImprimirLinha(4,0, tabuleiroA, tabuleiroB, jogador) + " 4 ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 5 " + oQueImprimirLinha(5,0, tabuleiroA, tabuleiroB, jogador) + " 5 ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 6 " + oQueImprimirLinha(6,0, tabuleiroA, tabuleiroB, jogador) + " 6 ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 7 " + oQueImprimirLinha(7,0, tabuleiroA, tabuleiroB, jogador) + " 7 ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 8 " + oQueImprimirLinha(8,0, tabuleiroA, tabuleiroB, jogador) + " 8 ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 9 " + oQueImprimirLinha(9,0, tabuleiroA, tabuleiroB, jogador) + " 9 ║\n";
    std::cout << tabuleiroEnd;
    std::cout << empty;
    std::cout << fim;
}

void colocarNave(int x, int y, int z, int tamanho, int orientacao, std::vector<std::vector<std::vector<int>>>& tabuleiro) {
    // Coloca a nave no tabuleiro
    for (int i = 0; i < tamanho; i++) {
        switch (orientacao) {
            case 0: // ---- mais z
                tabuleiro[x][y][z + i] = 1;
                break;
            case 1: // ---- menos z
                tabuleiro[x][y][z - i] = 1;
                break;
            case 2: // ---- mais y
                tabuleiro[x][y + i][z] = 1;
                break;
            case 3: // ---- mais y
                tabuleiro[x][y - i][z] = 1;
                break;
            case 4: // ---- mais x
                tabuleiro[x + i][y][z] = 1;
                break;
            case 5: // ---- menos x
                tabuleiro[x - i][y][z] = 1;
                break;
            default:
                std::cout << "Orientação inválida!\n";
        }
    }
}


/* FUNCOES AUXILIARES */
std::string oQueImprimirLinha(int x, int z, std::vector<std::vector<std::vector<int>>> tabuleiroBom, std::vector<std::vector<std::vector<int>>> tabuleiroMau, std::string jogador) {
    std::ostringstream oss;
    // tabuleiro do player em questão
    for (int i = 0; i < SIZE; i++) {
        int valor = tabuleiroBom[x][i][z];

        std::string placement = "";
        switch (valor){
            case 0: // vazio
                placement = " ";
                break;
            case 1: // tem nave
                placement = "🚀";
                break;
            case 2: // morreu
                placement = "💥";
                break;
            case 3: // falhou
                placement = "❌";
                break;
            default:
                return "⚠️";
                break;
        }

        // Formata cada valor com largura 3 para alinhar (como " 5 ", "10 ", etc.)
        oss << "┃" << std::setw(2) << std::setfill(' ') << placement << " ";
    }
    oss << "┃";  // Fecha a última barra
    oss << "    " + std::string(jogador.size(), ' ');
    
    //Tabuleiro do inimigo
    for (int i = 0; i < SIZE; i++) {
        int valor = tabuleiroMau[x][i][z];
        
        std::string placement = "";
        switch (valor){
            case 0: // vazio
                placement = " ";
                break;
            case 1: // tem nave
                placement = "🚀";
                break;
            case 2: // morreu
                placement = "💥";
                break;
            default:
                return "⚠️";
                break;
        }

        // Formata cada valor com largura 3 para alinhar (como " 5 ", "10 ", etc.)
        oss << "┃" << std::setw(2) << std::setfill(' ') << placement << " ";
    }
    oss << "┃";  // Fecha a última barra

    return oss.str();
}

std::string repetirString(const std::string& s, int n) {
    std::string resultado;for (int i = 0; i < n; ++i) resultado += s;
    return resultado;
}
