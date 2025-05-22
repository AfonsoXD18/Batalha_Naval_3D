#include "Jukebox.h"
#include "Constantes.h"
#include <string>


Jukebox::Jukebox() {
    // Constructor implementation (can be empty or add initialization code)
}

void Jukebox::tocarSom(std::string &som){
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