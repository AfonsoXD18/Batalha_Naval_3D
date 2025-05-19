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
 - Manegeamento de pontos --> posso colocar no cabeçalho à frente de cada tabuleiro o total de pontos 
*/


#include <sstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>


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
bool colocarNave(int x, int y, int z, int tamanho, int orientacao, std::vector<std::vector<std::vector<int>>>& tabuleiro);
void colocarNaveMae(int x, int y, int z, std::vector<std::vector<std::vector<int>>>& tabuleiro);
void randomizeNaves(std::vector<std::vector<std::vector<int>>>& tabuleiro);
void jogar();
void shoot(std::vector<std::vector<std::vector<int>>>& tabuleiro, int x, int y, int z, int& pontuacao);
std::string oQueImprimirLinha(int x, std::vector<std::vector<std::vector<int>>> tabuleiroBom, std::vector<std::vector<std::vector<int>>> tabuleiroMau, std::string jogador, int camada);
std::string repetirString(const std::string& s, int n);
void lerInputString(std::string& s);
void lerInputInt(int& x);
void tocarSom(const std::string& som);


/* FUNÇÕES PRÉ-JOGO */
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

    //perguntar se quer jogar automatico ou manual
    std::cout << "╼Quer colocar as Naves de forma automatica? (1 - Sim, 0 - Não): ";
    int automatico;
    lerInputInt(automatico);
    bool automatic = false;
    if (automatico == 1){
        automatic = true;
    }

    if (automatic){
        // Colocar naves automaticamente
        std::cout << "Colocando naves automaticamente...\n";
        randomizeNaves(tabuleiro1);
        gameUI(jogador1, tabuleiro1, tabuleiro2, 0);
    }else{
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
            std::cout << "\nInsira a orientacao \n ╼0: +z\n ╼1: -z\n ╼2: +y\n ╼3: -y\n ╼4: +x\n ╼5: -x\nOrientacao: ";
            lerInputInt(orientacao);

            colocarNave(x, y, z, nave, orientacao, tabuleiro1);
            std::cout << "\nNave colocada com sucesso!\n";
            gameUI(jogador1, tabuleiro1, tabuleiro2, camada);
        }

        //Colocar nave mãe
        std::cout << "\nNave: Mãe (3*3*3)\n";
        std::cout << "\n╼Insira a Camada que pretende ver z (0 - 9): ";
        lerInputInt(camada);
        std::cout << "\n╼Insira a coordenadas (x y z): ";
        lerInputInt(x);
        lerInputInt(y);
        lerInputInt(z);
        colocarNaveMae(x, y, z, tabuleiro1);
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

    // Perguntar se quer colocar naves de forma automatica ou manual
    std::cout << "╼Quer colocar as Naves de forma automatica? (1 - Sim, 0 - Não): ";
    int automatico2;
    lerInputInt(automatico2);
    bool automatic2 = false;
    if (automatico2 == 1){
        automatic2 = true;
    }

    if (automatic2){
        // Colocar naves automaticamente
        std::cout << "Colocando naves automaticamente...\n";
        randomizeNaves(tabuleiro2);
        gameUI(jogador2, tabuleiro2, tabuleiro1, 0);
    }else{

        // Colocar naves automaticamente
        std::cout << "Colocando naves automaticamente...\n";
        randomizeNaves(tabuleiro2);
        gameUI(jogador2, tabuleiro2, tabuleiro1, 0);

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


            //Colocar nave mãe
        std::cout << "\nNave: Mãe (3*3*3)\n";
        std::cout << "\n╼Insira a Camada que pretende ver z (0 - 9): ";
        lerInputInt(camada);
        std::cout << "\n╼Insira a coordenadas (x y z): ";
        lerInputInt(x);
        lerInputInt(y);
        lerInputInt(z);
        colocarNaveMae(x, y, z, tabuleiro2);
        std::cout << "\nNave colocada com sucesso!\n";
        gameUI(jogador1, tabuleiro2, tabuleiro1, camada);
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

bool colocarNave(int x, int y, int z, int tamanho, int orientacao, std::vector<std::vector<std::vector<int>>>& tabuleiro) {
    int dx = 0, dy = 0, dz = 0;

    // Determina o vetor de deslocamento com base na orientação
    switch (orientacao) {
        case 0: dz = 1; break;  // +z
        case 1: dz = -1; break; // -z
        case 2: dy = 1; break;  // +y
        case 3: dy = -1; break; // -y
        case 4: dx = 1; break;  // +x
        case 5: dx = -1; break; // -x
        default:
            std::cout << "Orientação inválida!\n";
            return false;
    }

    int nx = tabuleiro.size();
    int ny = tabuleiro[0].size();
    int nz = tabuleiro[0][0].size();

    // Verifica se a nave cabe e não sobrepõe outras naves
    for (int i = 0; i < tamanho; i++) {
        int xi = x + dx * i;
        int yi = y + dy * i;
        int zi = z + dz * i;

        // Verificação de limites
        if (xi < 0 || xi >= nx || yi < 0 || yi >= ny || zi < 0 || zi >= nz)
            return false;

        // Verifica sobreposição
        if (tabuleiro[xi][yi][zi] != 0)
            return false;
    }

    // Coloca a nave
    for (int i = 0; i < tamanho; i++) {
        int xi = x + dx * i;
        int yi = y + dy * i;
        int zi = z + dz * i;
        tabuleiro[xi][yi][zi] = 1;
    }

    return true;
}

void colocarNaveMae(int x, int y, int z, std::vector<std::vector<std::vector<int>>>& tabuleiro) {
    // Coloca a nave no tabuleiro 3*3*3 à volta do ponto (x,y,z)
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            for (int k = -1; k <= 1; k++) {
                if (x + i >= 0 && x + i < SIZE && y + j >= 0 && y + j < SIZE && z + k >= 0 && z + k < SIZE) {
                    tabuleiro[x + i][y + j][z + k] = 1;
                }
            }
        }
    }
}

void randomizeNaves(std::vector<std::vector<std::vector<int>>>& tabuleiro) {
    // Coloca naves aleatoriamente no tabuleiro
    // 4 naves tamanho 1, 3 naves tamanho 2, 2 naves tamanho 3, 1 nave tamanho 4 e nave mae 3*3*3
    int j = 0;

    // Colocar 4 Caças
    while (j < 4){
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        int z = rand() % SIZE;
        int orientacao = 0;
        if (colocarNave(x, y, z, 1, orientacao, tabuleiro)){
            j++;
        }
    }

    // Colocar 3 Fragatas
    j = 0;
    while (j < 3){
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        int z = rand() % SIZE;
        int orientacao = rand() % 6;
        if (colocarNave(x, y, z, 2, orientacao, tabuleiro)){
            j++;
        }
    }

    // Colocar 2 Contratorpedeiros
    j = 0;
    while (j < 2){
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        int z = rand() % SIZE;
        int orientacao = rand() % 6;
        if (colocarNave(x, y, z, 3, orientacao, tabuleiro)){
            j++;
        }
    }

    while (j < 1){
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        int z = rand() % SIZE;
        int orientacao = rand() % 6;
        if (colocarNave(x, y, z, 4, orientacao, tabuleiro)){
            j++;
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

            // Verifica se acertou ou não
            shoot(tabuleiro2, x, y, z, pontuacao1);
            if (pontuacao1 >= 10){
                std::cout << "Parabéns " + player1 + "! Ganhou o jogo!\n";
                std::cout << "╼A sua pontuação é: " + std::to_string(pontuacao1) + "\n";
                std::cout << "╼A pontuação do " + player2 + " é: " + std::to_string(pontuacao2) + "\n";
                std::cout << "O jogo acabou!\n";
                std::cout << "A voltar ao Menu inicial......\n";
                break;
            }

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

            //Verifica se acertou ou não
            shoot(tabuleiro1, x, y, z, pontuacao2);
            if (pontuacao2 >= 10){
                std::cout << "Parabéns " + player2 + "! Ganhou o jogo!\n";
                std::cout << "╼A sua pontuação é: " + std::to_string(pontuacao2) + "\n";
                std::cout << "╼A pontuação do " + player1 + " é: " + std::to_string(pontuacao1) + "\n";
                std::cout << "O jogo acabou!\n";
                std::cout << "A voltar ao Menu inicial......\n";
                break;
        }
        player = !player; // muda o proximo jogador
        }
    }
}

void shoot(std::vector<std::vector<std::vector<int>>>& tabuleiro, int x, int y, int z, int& pontuacao){
    bool acertou = false; // Flag para saber se houve pelo menos um acerto na linha
    // Se x == 0, o ataque percorre o eixo X (i varia em X, y e z fixos)
    if (x == 0){
        for (int i = 0; i < 10; ++i){
            // Se atingir uma nave, marca com 'X' e aumenta a pontuação
            if (tabuleiro[i][y][z] == 1){
                tocarSom("som2");
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
                tocarSom("som2");
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
                tocarSom("som2");
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

void tocarSom(const std::string& som){
    #ifdef _WIN32
        std::string comando = "powershell -c (New-Object Media.SoundPlayer '" + som + ".wav').PlaySync();";
        system(comando.c_str());
    #elif __APPLE__
        std::string comando = "afplay " + som + ".wav";
        system(comando.c_str());
    #else
        std::cout << "Sistema operativo não suportado para tocar som.\n";
    #endif
}