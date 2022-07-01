class CLegenda
{
    private:
        SDL_Surface* legenda = NULL;
        SDL_Surface* legenda_kolory = NULL;
        Text* Tekst = NULL;
        SDL_Surface* napisy[8] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
        bool Legenda_OK = true;
    public:
        CLegenda(Text* T)
        {
            legenda = SDL_CreateRGBSurface(0,300,180,24,0,0,0,0);
            if(legenda == NULL)
            {
                wiadomosc_o_bledzie(std::string("SDL_CreateRGBSurface: ") + std::string(SDL_GetError()));
                Legenda_OK = false;
                return;
            }
            legenda_kolory = SDL_CreateRGBSurface(0,32,152,24,0,0,0,0);
            if(legenda_kolory == NULL)
            {
                wiadomosc_o_bledzie(std::string("SDL_CreateRGBSurface: ") + std::string(SDL_GetError()));
                Legenda_OK = false;
                return;
            }
            Tekst = T;
            SDL_Rect pole;
            pole.w = 28;
            pole.h = 28;
            pole.x = 2;
            uint32_t kolory[5];
            kolory[0] = 0x0000FF;
            kolory[1] = 0x00FF00;
            kolory[2] = 0x7F7F7F;
            kolory[3] = 0xFFFF00;
            kolory[4] = 0xFF0000;
            SDL_FillRect(legenda_kolory,NULL,0xFFFFFF);
            for(uint8_t i = 0; i < 5; i++)
            {
                pole.y = i*(pole.h+2)+2;
                SDL_FillRect(legenda_kolory,&pole,kolory[i]);
            }
            napisy[0] = Tekst->renderText("Legenda:");
            napisy[1] = Tekst->renderText("Puste/nieznane pole");
            napisy[2] = Tekst->renderText("Statek");
            napisy[3] = Tekst->renderText("Pudło");
            napisy[4] = Tekst->renderText("Trafiony");
            napisy[5] = Tekst->renderText("Zatopiony");
            napisy[6] = Tekst->renderText("N = Nowa gra");
            napisy[7] = Tekst->renderText("ESC = Wyjście");
            for(uint8_t i = 0; i < 6; i++)
                Tekst->drawText(napisy[i], legenda, 45, 13 - napisy[i]->h / 2 + 30 * i);
            Tekst->drawText(napisy[6], legenda, 300 - napisy[6]->w, 180 - napisy[7]->h - napisy[6]->h);
            Tekst->drawText(napisy[7], legenda, 300 - napisy[7]->w, 180 - napisy[7]->h);
            SDL_Rect legenda_kolory_pozycja;
            legenda_kolory_pozycja.x = 0;
            legenda_kolory_pozycja.y = 28;
            SDL_BlitSurface(legenda_kolory,NULL,legenda,&legenda_kolory_pozycja);
        }
        ~CLegenda()
        {
            if(legenda != NULL)
                SDL_FreeSurface(legenda);
            if(legenda_kolory != NULL)
                SDL_FreeSurface(legenda_kolory);
            for(uint8_t i = 0; i < 8; i++)
                if(napisy[i] != NULL)
                    SDL_FreeSurface(napisy[i]);
        }
        bool ok()
        {
            return Legenda_OK;
        }
        void rysuj(SDL_Surface* cel, uint16_t x, uint16_t y)
        {
            SDL_Rect pozycja;
            pozycja.x = x;
            pozycja.y = y;
            SDL_BlitSurface(legenda,NULL,cel,&pozycja);
        }

};
