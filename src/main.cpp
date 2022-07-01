#include<iostream>
#include<ctime>
#include<pthread.h>
#include<SDL.h>
#include<SDL_ttf.h>
#define XOFFSET 40
void wiadomosc_o_bledzie(std::string tresc)
{
    if(SDL_WasInit(SDL_INIT_VIDEO))
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Błąd",tresc.c_str(),NULL);
    else
        std::cerr << tresc << "\n";
}
void wiadomosc_o_wygranej(std::string tresc, SDL_Window* okno)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Statki",tresc.c_str(),okno);
}
#include"statki.hpp"
#include"tekst.hpp"
#include"legenda.hpp"
#include"napisy.hpp"
#include"plansza.hpp"
#include"zegar.hpp"
#include"okno.hpp"
#include"interfejs.hpp"
int main(int argc, char* argv[])
{
    srand(time(NULL));
    CGra Gra;
    CWrog Wrog(&Gra);
    CInterfejs Interfejs(&Gra,&Wrog);
    if(!Interfejs.ok())
        return 1;
    Interfejs.start();
    return 0;
}
