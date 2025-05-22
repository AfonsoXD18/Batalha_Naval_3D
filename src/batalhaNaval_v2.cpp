// Compilar com: chcp 65001; g++ -std=c++14 batalhaNaval.cpp -o batalhaNaval; ./batalhaNaval
// g++ -std=c++17 batalhaNaval_V2.cpp Tabuleiro.cpp GameUI.cpp Constantes.cpp -o batalhaNaval_V2; batalhaNaval_V2.exe

/* 
Índice:
    - Tabuleiro:
        - 0 ---> vazio
        - 1 ---> nave
        - 2 ---> nave abatida
        - 3 ---> falhou
        - outro ---> erro no tabuleiro
*/


#include <sstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <deque>
//POO
#include "Tabuleiro.h"
#include "GameUI.h"
#include "Constantes.h"
#include "Jukebox.h"

// Constantes + Variáveis globais
const bool READ_FROM_FILE = false;
std::ifstream inputFile("entrada.txt");
const int MAX_HISTORICO = 100;
Tabuleiro tabuleiro1; // --> Tabuleiro Player 1
Tabuleiro tabuleiro2; // --> Tabuleiro Player 2
std::string player1;
std::string player2;
GameUI GameUI1;
GameUI GameUI2;

//Settings
bool somLigado = true;

//Declarar funções
int menu();
void prepJogo();
void randomizeNaves(Tabuleiro& tabuleiro);
void jogar();
void lerInputString(std::string& s);
void lerInputInt(int& x);
void configuracoes();
void subMenuExplosao();
void adicionarHistorico(std::string& j1, std::string& j2, int p1, int p2);
void mostrarHistorico();

/* FUNÇÕES PRÉ-JOGO */
int main() {
    srand(time(NULL));  // Isto serve para não ser os mesmos números aleatórios sempre
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
            configuracoes();
        } else if (opcao == "3"){
            std::cout << "\n\n\n";
            mostrarHistorico();
        } else if (opcao == "4"){
            return 0;
        } else {
            std::cout << "\n\n⚠️ Opção inválida! Tente novamente.⚠️\n";
        }
    }
}

void prepJogo(){

    // Pedir input do Player1
    std::cout << "🚢🚢🚢 Começar jogo!!!🚢🚢🚢\n\n╼Insira o nome do jogador 1: ";
    lerInputString(player1);

    // Pedir input para colocar as naves do Player1
    GameUI1.setup(player1, &tabuleiro1, &tabuleiro2, 0);
    GameUI1.printGameUI();
    std::string phrase = player1 + " vamos colocar as tuas naves!\n";
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
        GameUI1.printGameUI();
    }else{
        // vars para guardar input
        // ...dentro do else do if (automatic) em prepJogo()...

        int x, y, z, nave, orientacao, camada;

        // Nave Caça (4 naves, tamanho 1)
        for (int i = 0; i < 4; i++) {
            bool colocada = false;
            while (!colocada) {
                std::cout << "Nave: Caça (1)\n";
                nave = 1;
                std::cout << "\n╼Insira a Camada que pretende ver z (0 - 9): ";
                lerInputInt(camada);
                std::cout << "\n╼Insira as coordenadas (x y): ";
                lerInputInt(x);
                lerInputInt(y);
                z = camada;
                orientacao = 0;
                if (tabuleiro1.colocarNave(x, y, z, nave, orientacao)) {
                    std::cout << "\nNave colocada com sucesso!\n";
                    GameUI1.setCamadaZ(z);
                    GameUI1.printGameUI();
                    colocada = true;
                } else {
                    std::cout << "\n⚠️ Não foi possível colocar a nave nessas coordenadas. Tente novamente.\n";
                }
            }
        }

        // Nave Fragata (3 naves, tamanho 2)
        for (int i = 0; i < 3; i++) {
            bool colocada = false;
            while (!colocada) {
                std::cout << "Nave: Fragata (2)\n";
                nave = 2;
                std::cout << "\n╼Insira a Camada que pretende ver z (0 - 9): ";
                lerInputInt(camada);
                std::cout << "\n╼Insira as coordenadas (x y): ";
                lerInputInt(x);
                lerInputInt(y);
                z = camada;
                std::cout << "\n╼Insira a orientacao \n  ╼0: +z\n  ╼1: -z\n  ╼2: +y\n  ╼3: -y\n  ╼4: +x\n  ╼5: -x\nOrientacao: ";
                lerInputInt(orientacao);
                if (tabuleiro1.colocarNave(x, y, z, nave, orientacao)) {
                    std::cout << "\nNave colocada com sucesso!\n";
                    GameUI1.setCamadaZ(z);
                    GameUI1.printGameUI();
                    colocada = true;
                } else {
                    std::cout << "\n⚠️ Não foi possível colocar a nave nessas coordenadas. Tente novamente.\n";
                }
            }
        }

        // Nave Contratorpedeiro (2 naves, tamanho 3)
        for (int i = 0; i < 2; i++) {
            bool colocada = false;
            while (!colocada) {
                std::cout << "Nave: Contratorpedeiro (3)\n";
                nave = 3;
                std::cout << "\n╼Insira a Camada que pretende ver z (0 - 9): ";
                lerInputInt(camada);
                std::cout << "\n╼Insira as coordenadas (x y): ";
                lerInputInt(x);
                lerInputInt(y);
                z = camada;
                std::cout << "\n╼Insira a orientacao \n  ╼0: +z\n  ╼1: -z\n  ╼2: +y\n  ╼3: -y\n  ╼4: +x\n  ╼5: -x\nOrientacao: ";
                lerInputInt(orientacao);
                if (tabuleiro1.colocarNave(x, y, z, nave, orientacao)) {
                    std::cout << "\nNave colocada com sucesso!\n";
                    GameUI1.setCamadaZ(z);
                    GameUI1.printGameUI();
                    colocada = true;
                } else {
                    std::cout << "\n⚠️ Não foi possível colocar a nave nessas coordenadas. Tente novamente.\n";
                }
            }
        }

        // Nave Cruzador (1 nave, tamanho 4)
        for (int i = 0; i < 1; i++) {
            bool colocada = false;
            while (!colocada) {
                std::cout << "Nave: Cruzador (4)\n";
                nave = 4;
                std::cout << "\n╼Insira a Camada que pretende ver z (0 - 9): ";
                lerInputInt(camada);
                std::cout << "\n╼Insira as coordenadas (x y): ";
                lerInputInt(x);
                lerInputInt(y);
                z = camada;
                std::cout << "\n╼Insira a orientacao \n  ╼0: +z\n  ╼1: -z\n  ╼2: +y\n  ╼3: -y\n  ╼4: +x\n  ╼5: -x\nOrientacao: ";
                lerInputInt(orientacao);
                if (tabuleiro1.colocarNave(x, y, z, nave, orientacao)) {
                    std::cout << "\nNave colocada com sucesso!\n";
                    GameUI1.setCamadaZ(z);
                    GameUI1.printGameUI();
                    colocada = true;
                } else {
                    std::cout << "\n⚠️ Não foi possível colocar a nave nessas coordenadas. Tente novamente.\n";
                }
            }
        }

        // Nave Mãe (1 nave especial)
        bool colocada = false;
        while (!colocada) {
            std::cout << "Nave: Mãe (3x3x3)\n";
            std::cout << "\n╼Insira a Camada que pretende ver z (0 - 9): ";
            lerInputInt(camada);
            std::cout << "\n╼Insira as coordenadas (x y): ";
            lerInputInt(x);
            lerInputInt(y);
            z = camada;
            if (tabuleiro1.colocarNaveMae(x, y, z)) {
                std::cout << "\nNave colocada com sucesso!\n";
                GameUI1.setCamadaZ(z);
                GameUI1.printGameUI();
                colocada = true;
            } else {
                std::cout << "\n⚠️ Não foi possível colocar a nave nessas coordenadas. Tente novamente.\n";
            }
        }
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
    lerInputString(player2);

    GameUI2.setup(player2, &tabuleiro2, &tabuleiro1, 0);

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
        GameUI2.printGameUI();
    }else{
        // vars para guardar input
        int x, y, z, nave, orientacao, camada;

        // Pedir input para colocar as naves do Player2
        GameUI2.printGameUI();
        phrase = player2 + " vamos colocar as tuas naves!\n";
        std::cout << phrase;

        // Nave Caça (4 naves, tamanho 1)
        for (int i = 0; i < 4; i++) {
            bool colocada = false;
            while (!colocada) {
                std::cout << "Nave: Caça (1)\n";
                nave = 1;
                std::cout << "\n╼Insira a Camada que pretende ver z (0 - 9): ";
                lerInputInt(camada);
                std::cout << "\n╼Insira as coordenadas (x y): ";
                lerInputInt(x);
                lerInputInt(y);
                z = camada;
                orientacao = 0;
                if (tabuleiro2.colocarNave(x, y, z, nave, orientacao)) {
                    std::cout << "\nNave colocada com sucesso!\n";
                    GameUI2.setCamadaZ(z);
                    GameUI2.printGameUI();
                    colocada = true;
                } else {
                    std::cout << "\n⚠️ Não foi possível colocar a nave nessas coordenadas. Tente novamente.\n";
                }
            }
        }

        // Nave Fragata (3 naves, tamanho 2)
        for (int i = 0; i < 3; i++) {
            bool colocada = false;
            while (!colocada) {
                std::cout << "Nave: Fragata (2)\n";
                nave = 2;
                std::cout << "\n╼Insira a Camada que pretende ver z (0 - 9): ";
                lerInputInt(camada);
                std::cout << "\n╼Insira as coordenadas (x y): ";
                lerInputInt(x);
                lerInputInt(y);
                z = camada;
                std::cout << "\n╼Insira a orientacao \n  ╼0: +z\n  ╼1: -z\n  ╼2: +y\n  ╼3: -y\n  ╼4: +x\n  ╼5: -x\nOrientacao: ";
                lerInputInt(orientacao);
                if (tabuleiro2.colocarNave(x, y, z, nave, orientacao)) {
                    std::cout << "\nNave colocada com sucesso!\n";
                    GameUI2.setCamadaZ(z);
                    GameUI2.printGameUI();
                    colocada = true;
                } else {
                    std::cout << "\n⚠️ Não foi possível colocar a nave nessas coordenadas. Tente novamente.\n";
                }
            }
        }

        // Nave Contratorpedeiro (2 naves, tamanho 3)
        for (int i = 0; i < 2; i++) {
            bool colocada = false;
            while (!colocada) {
                std::cout << "Nave: Contratorpedeiro (3)\n";
                nave = 3;
                std::cout << "\n╼Insira a Camada que pretende ver z (0 - 9): ";
                lerInputInt(camada);
                std::cout << "\n╼Insira as coordenadas (x y): ";
                lerInputInt(x);
                lerInputInt(y);
                z = camada;
                std::cout << "\n╼Insira a orientacao \n  ╼0: +z\n  ╼1: -z\n  ╼2: +y\n  ╼3: -y\n  ╼4: +x\n  ╼5: -x\nOrientacao: ";
                lerInputInt(orientacao);
                if (tabuleiro2.colocarNave(x, y, z, nave, orientacao)) {
                    std::cout << "\nNave colocada com sucesso!\n";
                    GameUI2.setCamadaZ(z);
                    GameUI2.printGameUI();
                    colocada = true;
                } else {
                    std::cout << "\n⚠️ Não foi possível colocar a nave nessas coordenadas. Tente novamente.\n";
                }
            }
        }

        // Nave Cruzador (1 nave, tamanho 4)
        for (int i = 0; i < 1; i++) {
            bool colocada = false;
            while (!colocada) {
                std::cout << "Nave: Cruzador (4)\n";
                nave = 4;
                std::cout << "\n╼Insira a Camada que pretende ver z (0 - 9): ";
                lerInputInt(camada);
                std::cout << "\n╼Insira as coordenadas (x y): ";
                lerInputInt(x);
                lerInputInt(y);
                z = camada;
                std::cout << "\n╼Insira a orientacao \n  ╼0: +z\n  ╼1: -z\n  ╼2: +y\n  ╼3: -y\n  ╼4: +x\n  ╼5: -x\nOrientacao: ";
                lerInputInt(orientacao);
                if (tabuleiro2.colocarNave(x, y, z, nave, orientacao)) {
                    std::cout << "\nNave colocada com sucesso!\n";
                    GameUI2.setCamadaZ(z);
                    GameUI2.printGameUI();
                    colocada = true;
                } else {
                    std::cout << "\n⚠️ Não foi possível colocar a nave nessas coordenadas. Tente novamente.\n";
                }
            }
        }

        // Nave Mãe (1 nave especial)
        bool colocada = false;
        while (!colocada) {
            std::cout << "Nave: Mãe (3x3x3)\n";
            std::cout << "\n╼Insira a Camada que pretende ver z (0 - 9): ";
            lerInputInt(camada);
            std::cout << "\n╼Insira as coordenadas (x y): ";
            lerInputInt(x);
            lerInputInt(y);
            z = camada;
            if (tabuleiro2.colocarNaveMae(x, y, z)) {
                std::cout << "\nNave colocada com sucesso!\n";
                GameUI2.setCamadaZ(z);
                GameUI2.printGameUI();
                colocada = true;
            } else {
                std::cout << "\n⚠️ Não foi possível colocar a nave nessas coordenadas. Tente novamente.\n";
            }
        }
        // OK! Prontos para efetivamente começar a jogar!
    }
}

// Função randomizeNaves movida para fora de prepJogo
void randomizeNaves(Tabuleiro& tabuleiro) {
    int x, y, z, orientacao;
    int j = 0;

    // Caças
    j = 0;
    while (j < 4) {
        x = rand() % SIZE;
        y = rand() % SIZE;
        z = rand() % SIZE;
        orientacao = 0;
        if (tabuleiro.colocarNave(x, y, z, 1, orientacao)) j++;
    }

    // Fragatas
    j = 0;
    while (j < 3) {
        x = rand() % SIZE;
        y = rand() % SIZE;
        z = rand() % SIZE;
        orientacao = rand() % 6;
        if (tabuleiro.colocarNave(x, y, z, 2, orientacao)) j++;
    }

    // Contratorpedeiros
    j = 0;
    while (j < 2) {
        x = rand() % SIZE;
        y = rand() % SIZE;
        z = rand() % SIZE;
        orientacao = rand() % 6;
        if (tabuleiro.colocarNave(x, y, z, 3, orientacao)) j++;
    }

    // Cruzador
    j = 0;
    while (j < 1) {
        x = rand() % SIZE;
        y = rand() % SIZE;
        z = rand() % SIZE;
        orientacao = rand() % 6;
        if (tabuleiro.colocarNave(x, y, z, 4, orientacao)) j++;
    }

    // Nave Mãe
    j = 0;
    while (j < 1) {
        x = rand() % SIZE;
        y = rand() % SIZE;
        z = rand() % SIZE;
        if (tabuleiro.colocarNaveMae(x, y, z)) j++;
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
            std::cout << player1 + "! és tu a jogar! --> Pontos: " + std::to_string(pontuacao1) + "\n";
            std::cout << "╼Insira a Camada que pretende ver z (0 - 9): ";
            lerInputInt(z);
            GameUI1.setCamadaZ(z);
            GameUI1.printGameUI();
            std::cout << "╼Insira a coordenadas do ataque(x y z) ---> uma das coordenadas tem que ser 0: ";
            lerInputInt(x);
            lerInputInt(y);
            lerInputInt(z);
            if (x != 0 && y != 0 && z != 0){
                std::cout << "╼Coordenadas inválidas! Tente novamente.\n";
                continue;
            }
            player = !player; // muda o proximo jogador


            // Verifica se acertou ou não
            tabuleiro2.disparar(x, y, z, pontuacao1);
            if (pontuacao1 >= 10){
                std::cout << "Parabéns " + player1 + "! Ganhou o jogo!\n";
                std::cout << "╼A sua pontuação é: " + std::to_string(pontuacao1) + "\n";
                std::cout << "╼A pontuação do " + player2 + " é: " + std::to_string(pontuacao2) + "\n";
                std::cout << "O jogo acabou!\n";
                std::cout << "A voltar ao Menu inicial......\n";
                //Adicionar ao hisotrico
                adicionarHistorico(player1, player2, pontuacao1, pontuacao2);
                break;
            }

        }else{
            std::cout << player2 + "! és tu a jogar! --> Pontos: " + std::to_string(pontuacao2) + "\n";
            // perguntar a camada de z que quer ver
            std::cout << "╼Insira a Camada que pretende ver z (0 - 9): ";
            lerInputInt(z);
            GameUI2.setCamadaZ(z);
            GameUI2.printGameUI();
            std::cout << "╼Insira a coordenadas do ataque(x y z) ---> uma das coordenadas tem que ser 0: ";
            lerInputInt(x);
            lerInputInt(y);
            lerInputInt(z);
            if (x != 0 && y != 0 && z != 0){
                std::cout << "╼Coordenadas inválidas! Tente novamente.\n";
                continue;
            }
            player = !player; // muda o proximo jogador

            //Verifica se acertou ou não
            tabuleiro1.disparar(x, y, z, pontuacao2);
            if (pontuacao2 >= 10){
                std::cout << "Parabéns " + player2 + "! Ganhou o jogo!\n";
                std::cout << "╼A sua pontuação é: " + std::to_string(pontuacao2) + "\n";
                std::cout << "╼A pontuação do " + player1 + " é: " + std::to_string(pontuacao1) + "\n";
                std::cout << "O jogo acabou!\n";
                std::cout << "A voltar ao Menu inicial......\n";
                adicionarHistorico(player1, player2, pontuacao1, pontuacao2);
                break;
            }
        }
    }
}

/* FUNÇÕES DE CONFIGURAÇÔES */
void configuracoes(){
    while (true){
        std::cout << "╒═══════════════════════════════════════════════╕\n";
        std::cout << "│ 1. Ligar/Desligar Som                         │\n";
        std::cout << "│ 2. Mudar o som da explosão                    │\n";
        std::cout << "│ 3. Sair                                       │\n";
        std::cout << "╘═══════════════════════════════════════════════╛\n";
        std::cout << "╼Escolha uma opção: ";
        int opcao;
        lerInputInt(opcao);
        if (opcao == 1){
            somLigado = !somLigado;
            if (somLigado){
                std::cout << "\n\n\n\n\n\n\nSom ligado!";
            }else{
                std::cout << "\n\n\n\n\n\n\nSom desligado!";
            }
        }else if (opcao == 2){
            subMenuExplosao();
        }else if (opcao == 3){
            break;
        }else{
            std::cout << "\n\n\n\n\n\n\nOpção inválida! Tente novamente.\n";
        }
    }
}

void subMenuExplosao(){
    while (true){
        std::cout << "╒═══════════════════════════════════════════════╕\n";
        std::cout << "│ 1. Som de explosão padrão                     │\n";
        std::cout << "│ 2. Som de explosão alternativo                │\n";
        std::cout << "│ 3. Sair                                       │\n";
        std::cout << "╘═══════════════════════════════════════════════╛\n";
        std::cout << "╼Escolha uma opção: ";
        int opcao;
        lerInputInt(opcao);
        if (opcao == 1){
            somExplosao = "BOOOM";
            std::cout << "\n\n\n\n\n\n\nSom de explosão alterado para padrão.\n";
            break;
        }else if (opcao == 2){
            somExplosao = "BOOOM2";
            std::cout << "\n\n\n\n\n\n\nSom de explosão alterado para alternativo.\n";
            break;
        }else if (opcao == 3){
            break;
        }else{
            std::cout << "\n\n\n\n\n\n\nOpção inválida! Tente novamente.\n";
        }
    }
}


/* FUNÇÕES AUXILIARES */
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

void adicionarHistorico(std::string& j1, std::string& j2, int p1, int p2) {
    std::ofstream file("historico.txt");
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o ficheiro de histórico.\n";
        return;
    }
    //escrever no ficheiro
    file << j1 << " --> " << p1 << "; " << j2 << " --> " << p2 << "\n";
    file.close();
}

void mostrarHistorico() {
    //deve imprimir apenas as ultimas 100 linhas
    std::ifstream file("historico.txt");
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o ficheiro de histórico.\n";
        return;
    }
    std::deque<std::string> historico;
    std::string line;
    while (std::getline(file, line)) {
        historico.push_back(line);
        if (historico.size() > MAX_HISTORICO) {
            historico.pop_front();
        }
    }
    file.close();
    std::cout << "╒═══════════════════════════════════════════════╕\n";
    std::cout << "│                 HISTÓRICO                     │\n";
    std::cout << "╘═══════════════════════════════════════════════╛\n";
    for (const auto& entry : historico) {
        std::cout << "│ " << entry << "\n";
    }
   
}