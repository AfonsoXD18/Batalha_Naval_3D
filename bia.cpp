#include <iostream>
#include <windows.h>
#include <mmsystem.h>
using namespace std;

void tocarMusicaFundo(const char* caminho) {
    PlaySoundA(caminho, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void pararMusica() {
    PlaySoundA(NULL, 0, 0);
}

int main() {
    cout << "A tocar musica de fundo...\n";
    tocarMusicaFundo("som2.wav");

    cout << "Pressiona ENTER para parar a música.\n";
    cin.get();

    pararMusica();
    return 0;
}

#include <cstdlib>

void tocarSom(){
#ifdef _WIN32
    system("powershell -c (New-Object Media.SoundPlayer 'som.wav').PlaySync();");
#elif __APPLE__
    system("afplay som.wav");
#else
    std::cout << "Sistema operativo não suportado.\n";
#endif
}