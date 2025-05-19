// Este ficheiro é a versão do jão! please não mexam :))
// Compilar com: chcp 65001; g++ -std=c++14 jao.cpp -o jao; ./jao

/* 
Índice:

    - Tabuleiro:
        - 0 ---> vazio
        - 1 ---> nave
        - 2 ---> nave abatida
        - 3 ---> falhou
        - outro ---> erro no tabuleiro
*/


/*
TODO:
 - Escolher que Z queremos ver do tabuleiro
 - Funcao que altera o tabuleiro consoante o disparo
 - Manegeamento de pontos --> posso colocar no cabeçalho à frente de cada tabuleiro o total de pontos 
*/


#include <windows.h>
#include <mmsystem.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <fstream>

// Constantes + Variáveis globais
const int SIZE = 10;
const bool READ_FROM_FILE = false;

std::vector<std::vector<std::vector<int>>> tabuleiro1 (SIZE, std::vector<std::vector<int>>(SIZE, std::vector<int>(SIZE, 0))); // --> Tabuleiro Player 1
std::vector<std::vector<std::vector<int>>> tabuleiro2 (SIZE, std::vector<std::vector<int>>(SIZE, std::vector<int>(SIZE, 0))); // --> Tabuleiro Player 2
std::ifstream inputFile("entrada.txt");
std::string player1 = "Jogador 1";
std::string player2 = "Jogador 2";

//Declarar funções
int menu();
void prepJogo();
void gameUI(std::string jogador1, std::vector<std::vector<std::vector<int>>> tabuleiroA = tabuleiro1, std::vector<std::vector<std::vector<int>>> tabuleiroB = tabuleiro2, int camadaZ = 0);
void colocarNave(int x, int y, int z, int tamanho, int orientacao, std::vector<std::vector<std::vector<int>>>& tabuleiro);
void jogar();
void shoot(std::vector<std::vector<std::vector<int>>>& tabuleiro, int x, int y, int z, int& pontuacao);
std::string oQueImprimirLinha(int x, std::vector<std::vector<std::vector<int>>> tabuleiroBom, std::vector<std::vector<std::vector<int>>> tabuleiroMau, std::string jogador, int camada);
std::string repetirString(const std::string& s, int n);
void lerInputString(std::string& s);
void lerInputInt(int& x);


/* CÓDIGO GERAL */
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
        lerInputString (opcao);

        if (opcao == "1"){
            prepJogo();
            jogar();
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
    std::cout << "🚢🚢🚢 começar jogo!!!🚢🚢🚢\n\n╼Insira o nome do jogador 1: ";
    std::string jogador1;
    lerInputString(jogador1);

    // Pedir input para colocar as naves do Player1
    gameUI(jogador1, tabuleiro1, tabuleiro2, 0);
    std::string phrase = jogador1 + " vamos colocar as tuas naves!\n";
    std::cout << phrase;

    // vars para guardar input
    int x, y, z, nave, orientacao, camada;

    // Nave Caça
    for (int i = 0; i < 4; i++){
        std::cout << "Nave: Caca (1)\n";
        nave=1;
        std::cout << "\n╼Insira a Camada que pretende ver z (0 - 9): ";
        lerInputInt(camada);
        std::cout << "\n╼Insira a coordenadas (x y z): ";
        lerInputInt(x);
        lerInputInt(y);
        lerInputInt(z);
        orientacao = 0;

        colocarNave(x, y, z, nave, orientacao, tabuleiro1);
        std::cout << "\nNave colocada com sucesso!\n";
        gameUI(jogador1, tabuleiro1, tabuleiro2, camada);
    }
    
    // Nave Fragata
    for (int i = 0; i < 3; i++){
        std::cout << "Nave: Fragata (2)\n";
        nave=2;
        std::cout << "\n╼Insira a Camada que pretende ver z (0 - 9): ";
        lerInputInt(camada);
        std::cout << "\n╼Insira a coordenadas (x y z): ";
        lerInputInt(x);
        lerInputInt(y);
        lerInputInt(z);
        std::cout << "\n╼Insira a orientacao \n  ╼0: +z\n  ╼1: -z\n  ╼2: +y\n  ╼3: -y\n  ╼4: +x\n  ╼5: -x\nOrientacao: ";
        lerInputInt(orientacao);

        colocarNave(x, y, z, nave, orientacao, tabuleiro1);
        std::cout << "\nNave colocada com sucesso!\n";
        gameUI(jogador1, tabuleiro1, tabuleiro2, camada);
    }
    
    // Nave Contratorpedeiro
    for (int i = 0; i < 2; i++){
        std::cout << "\nNave: Contratorpedeiro (3)\n";
        nave=3;
        std::cout << "\n╼Insira a Camada que pretende ver z (0 - 9): ";
        lerInputInt(camada);
        std::cout << "\nInsira a coordenadas (x y z): ";
        lerInputInt(x);
        lerInputInt(y);
        lerInputInt(z);
        std::cout << "\n╼Insira a orientacao \n  ╼0: +z\n  ╼1: -z\n  ╼2: +y\n  ╼3: -y\n  ╼4: +x\n  ╼5: -x\nOrientacao: ";
        lerInputInt(orientacao);

        colocarNave(x, y, z, nave, orientacao, tabuleiro1);
        std::cout << "\nNave colocada com sucesso!\n";
        gameUI(jogador1, tabuleiro1, tabuleiro2, camada);
    }
    
    // Nave Cruzador
    for (int i = 0; i < 1; i++){
        std::cout << "\nNave: Cruzador (4)\n";
        nave=4;
        std::cout << "\n╼Insira a Camada que pretende ver z (0 - 9): ";
        lerInputInt(camada);
        std::cout << "\nInsira a coordenadas (x y z): ";
        lerInputInt(x);
        lerInputInt(y);
        lerInputInt(z);
        std::cout << "\nInsira a orientacao \n0: +z\n 1: -z\n 2: +y\n 3: -y\n 4: +x\n 5: -x\nOrientacao: ";
        lerInputInt(orientacao);

        colocarNave(x, y, z, nave, orientacao, tabuleiro1);
        std::cout << "\nNave colocada com sucesso!\n";
        gameUI(jogador1, tabuleiro1, tabuleiro2, camada);
    }

    // Confirmar que o jogador está OK! para passar o computador
    std::cout << "Escreve \"Y\" para passar o computador ao próximo Player: ";
    std::string resposta;
    while (true) {
        lerInputString(resposta);
        if (resposta == "Y" || resposta == "y") {
            std::cout << "Passando o computador ao próximo Player...\n";
            break;
        } else {
            std::cout << "Resposta inválida. Por favor escreve \"Y\" ou \"y\".\n";
        }
    }

    // Pedir input do Player2
    std::cout << "\n╼Insira o nome do jogador 2: ";
    std::string jogador2;
    lerInputString(jogador2);

    // Pedir input para colocar as naves do Player2
    gameUI(jogador2, tabuleiro2, tabuleiro1, 0);
    phrase = jogador2 + " vamos colocar as tuas naves!\n";
    std::cout << phrase;

    // Nave Caça
    for (int i = 0; i < 4; i++){
        std::cout << "\nNave: Caca (1)\n";
        nave=1;
        std::cout << "\n╼Insira a Camada que pretende ver z (0 - 9): ";
        lerInputInt(camada);
        std::cout << "\n╼Insira a coordenadas (x y z): ";
        lerInputInt(x);
        lerInputInt(y);
        lerInputInt(z);
        orientacao = 0;

        colocarNave(x, y, z, nave, orientacao, tabuleiro2);
        std::cout << "\nNave colocada com sucesso!\n";
        gameUI(jogador2, tabuleiro2, tabuleiro1, camada);
    }
    
    // Nave Fragata
    for (int i = 0; i < 3; i++){
        std::cout << "\nNave: Fragata (2)\n";
        nave=2;
        std::cout << "\n╼Insira a Camada que pretende ver z (0 - 9): ";
        lerInputInt(camada);
        std::cout << "\n╼Insira a coordenadas (x y z): ";
        lerInputInt(x);
        lerInputInt(y);
        lerInputInt(z);
        std::cout << "\n╼Insira a orientacao \n  ╼0: +z\n  ╼1: -z\n  ╼2: +y\n  ╼3: -y\n  ╼4: +x\n  ╼5: -x\nOrientacao: ";
        lerInputInt(orientacao);

        colocarNave(x, y, z, nave, orientacao, tabuleiro2);
        std::cout << "\nNave colocada com sucesso!\n";
        gameUI(jogador2, tabuleiro2, tabuleiro1, camada);
    }
    
    // Nave Contratorpedeiro
    for (int i = 0; i < 2; i++){
        std::cout << "\nNave: Contratorpedeiro (3)\n";
        nave=3;
        std::cout << "\n╼Insira a Camada que pretende ver z (0 - 9): ";
        lerInputInt(camada);
        std::cout << "\nInsira a coordenadas (x y z): ";
        lerInputInt(x);
        lerInputInt(y);
        lerInputInt(z);
        std::cout << "\n╼Insira a orientacao \n  ╼0: +z\n  ╼1: -z\n  ╼2: +y\n  ╼3: -y\n  ╼4: +x\n  ╼5: -x\nOrientacao: ";
        lerInputInt(orientacao);

        colocarNave(x, y, z, nave, orientacao, tabuleiro2);
        std::cout << "\nNave colocada com sucesso!\n";
        gameUI(jogador2, tabuleiro2, tabuleiro1, camada);
    }
    
    // Nave Cruzador
    for (int i = 0; i < 1; i++){
        std::cout << "\nNave: Cruzador (4)\n";
        nave=4;
        std::cout << "\n╼Insira a Camada que pretende ver z (0 - 9): ";
        lerInputInt(camada);
        std::cout << "\nInsira a coordenadas (x y z): ";
        lerInputInt(x);
        lerInputInt(y);
        lerInputInt(z);
        std::cout << "\nInsira a orientacao \n0: +z\n 1: -z\n 2: +y\n 3: -y\n 4: +x\n 5: -x\nOrientacao: ";
        lerInputInt(orientacao);

        colocarNave(x, y, z, nave, orientacao, tabuleiro2);
        std::cout << "\nNave colocada com sucesso!\n";
        gameUI(jogador2, tabuleiro2, tabuleiro1, camada);
    }

    // OK! Prontos para efetivamente começar a jogar!

}

void gameUI(std::string jogador = "Jogador", std::vector<std::vector<std::vector<int>>> tabuleiroA, std::vector<std::vector<std::vector<int>>> tabuleiroB, int camadaZ) {
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
    std::cout << "║ X " + oQueImprimirLinha(0, tabuleiroA, tabuleiroB, jogador, camadaZ) + " X ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 1 " + oQueImprimirLinha(1, tabuleiroA, tabuleiroB, jogador, camadaZ) + " 1 ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 2 " + oQueImprimirLinha(2, tabuleiroA, tabuleiroB, jogador, camadaZ) + " 2 ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 3 " + oQueImprimirLinha(3, tabuleiroA, tabuleiroB, jogador, camadaZ) + " 3 ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 4 " + oQueImprimirLinha(4, tabuleiroA, tabuleiroB, jogador, camadaZ) + " 4 ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 5 " + oQueImprimirLinha(5, tabuleiroA, tabuleiroB, jogador, camadaZ) + " 5 ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 6 " + oQueImprimirLinha(6, tabuleiroA, tabuleiroB, jogador, camadaZ) + " 6 ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 7 " + oQueImprimirLinha(7, tabuleiroA, tabuleiroB, jogador, camadaZ) + " 7 ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 8 " + oQueImprimirLinha(8, tabuleiroA, tabuleiroB, jogador, camadaZ) + " 8 ║\n"; 
    std::cout << tabuleiroStr;
    std::cout << "║ 9 " + oQueImprimirLinha(9, tabuleiroA, tabuleiroB, jogador, camadaZ) + " 9 ║\n";
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


/* FUNÇÕES DO JOGO */
void jogar(){
    // Ciclo de jogo!
    std::cout << "A começar o jogo!\n";
    bool player = true;
    int pontuacao1 = 0;
    int pontuacao2 = 0;
    int x, y, z;
    while (true){
        if (player){
            std::cout << player1 + "! és tu a jogar!\n";
            gameUI(player1, tabuleiro1, tabuleiro2, 0);
            std::cout << "╼Insira a coordenadas do ataque(x y z) ---> uma das coordenadas tem que ser 0: ";
            lerInputInt(x);
            lerInputInt(y);
            lerInputInt(z);
            if (x != 0 && y != 0 && z != 0){
                std::cout << "╼Coordenadas inválidas! Tente novamente.\n";
                continue;
            }

            //check if hit or miss
            shoot(tabuleiro2, x, y, z, pontuacao1);

        }else{
            std::cout << player2 + "! és tu a jogar!\n";
            gameUI(player2, tabuleiro2, tabuleiro1, 0);
            std::cout << "╼Insira a coordenadas do ataque(x y z) ---> uma das coordenadas tem que ser 0: ";
            lerInputInt(x);
            lerInputInt(y);
            lerInputInt(z);
            if (x != 0 && y != 0 && z != 0){
                std::cout << "╼Coordenadas inválidas! Tente novamente.\n";
                continue;
            }

            //check if hit or miss
            shoot(tabuleiro1, x, y, z, pontuacao2);
        }
        player = !player; // muda o proximo jogador
    }
}

void shoot(std::vector<std::vector<std::vector<int>>>& tabuleiro, int x, int y, int z, int& pontuacao){
    bool acertou = false; // Flag para saber se houve pelo menos um acerto na linha
    // Se x == 0, o ataque percorre o eixo X (i varia em X, y e z fixos)
    if (x == 0){
        for (int i = 0; i < 10; ++i){
            // Se atingir uma nave, marca com 'X' e aumenta a pontuação
            if (tabuleiro[i][y][z] == 1){
                tabuleiro[i][y][z] = 2;
                pontuacao++;
                acertou = true;
            }
            // Se atingir uma célula vazia, marca como falhanço com 'O'
            else if (tabuleiro[i][y][z] == 0){
                tabuleiro[i][y][z] = 3;
            }
        }
    }
    // Se y == 0, o ataque percorre o eixo Y (i varia em Y, x e z fixos)
    else if (y == 0){
        for (int i = 0; i < 10; ++i){
            if (tabuleiro[x][i][z] == 1){
                tabuleiro[x][i][z] = 2;
                pontuacao++;
                acertou = true;
            }
            else if (tabuleiro[x][i][z] == 0){
                tabuleiro[x][i][z] = 3;
            }
        }
    }
    // Se z == 0, o ataque percorre o eixo Z (i varia em Z, x e y fixos)
    else if (z == 0){
        for (int i = 0; i < 10; ++i){
            if (tabuleiro[x][y][i] == 1){
                tabuleiro[x][y][i] = 2;
                pontuacao++;
                acertou = true;
            }
            else if (tabuleiro[x][y][i] == 0){
                tabuleiro[x][y][i] = 3;
            }
        }
    }

    // Mostra ao jogador se acertou ou não em alguma nave
    if (acertou){
        std::cout << "🎯 Acertaste numa nave!\n";
    } else {
        std::cout << "💦 Não acertaste em nada...\n";
    }
}

/* FUNÇÕES AUXILIARES */
std::string oQueImprimirLinha(int x, std::vector<std::vector<std::vector<int>>> tabuleiroBom, std::vector<std::vector<std::vector<int>>> tabuleiroMau, std::string jogador, int camada) {
    std::ostringstream oss;
    // tabuleiro do player em questão
    for (int i = 0; i < SIZE; i++) {
        int valor = tabuleiroBom[x][i][camada];

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
        int valor = tabuleiroMau[x][i][camada];
        
        std::string placement = "";
        switch (valor){
            case 0: // vazio
                placement = " ";
                break;
            case 1: // tem nave mas como é inimigo não podemos ver
                placement = " ";
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

    return oss.str();
}

std::string repetirString(const std::string& s, int n) {
    std::string resultado;for (int i = 0; i < n; ++i) resultado += s;
    return resultado;
}

void lerInputString(std::string& s) {
    if (READ_FROM_FILE && inputFile.is_open()) {
        if (inputFile >> s) {
            return; // Leu com sucesso
        } else {
            // Falhou a leitura (EOF ou erro), fechamos e passamos para std::cin
            inputFile.close();
        }
    }
    std::cin >> s;
}

void lerInputInt(int& x) {
    if (READ_FROM_FILE && inputFile.is_open()) {
        if (inputFile >> x) {
            return; // Leu com sucesso
        } else {
            inputFile.close();
        }
    }
    std::cin >> x;
}