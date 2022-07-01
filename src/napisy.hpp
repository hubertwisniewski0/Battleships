class CNapisy
{
    private:
        SDL_Surface* napisy[8] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
        SDL_Surface* litery[10] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
        SDL_Surface* liczby[10] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
        SDL_Surface* wzkazania[10][10] = {
        {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}};
        SDL_Surface* wzk_gracz = NULL;
        SDL_Surface* wzk_wrog = NULL;
        SDL_Surface* s_gracz = NULL;
        SDL_Surface* s_wrog = NULL;
        Text* Tekst = NULL;
        int min_odstep;
        bool Napisy_OK = true;
    public:
        CNapisy(Text* T)
        {
            Tekst = T;
            min_odstep = Tekst->getMinOffset();
            napisy[0] = Tekst->renderText("Morze gracza");
            napisy[1] = Tekst->renderText("Morze wroga");
            napisy[2] = Tekst->renderText("Gracz");
            napisy[3] = Tekst->renderText("Wróg");
            napisy[4] = Tekst->renderText("Zwycięstwo");
            napisy[5] = Tekst->renderText("Pudło");
            napisy[6] = Tekst->renderText("Trafiony");
            napisy[7] = Tekst->renderText("Zatopiony");
            for(uint8_t i = 0; i < 8; i++)
            {
                if(napisy[i] == NULL)
                {
                    wiadomosc_o_bledzie(std::string("Render tekstu n") + std::to_string((int)i) + std::string(": ") + std::string(TTF_GetError()));
                    Napisy_OK = false;
                    return;
                }
            }
            char t[2];
            char c[3];
            char w[4];
            for(uint8_t i = 0; i < 10; i++)
            {
                t[0] = 0x41+i;
                t[1] = 0;
                litery[i] = Tekst->renderText(t);
                for(uint8_t j = 0; j < 10; j++)
                {
                    if(j < 9)
                    {
                        c[0] = 0x31+j;
                        c[1] = 0;
                    }
                    else
                    {
                        c[0] = '1';
                        c[1] = '0';
                        c[2] = 0;
                    }
                    if(i == 0)
                    {
                        liczby[j] = Tekst->renderText(c);
                        if(liczby[j] == NULL)
                        {
                            wiadomosc_o_bledzie(std::string("Render tekstu c") + std::to_string((int)j) + std::string(": ") + std::string(TTF_GetError()));
                            Napisy_OK = false;
                            return;
                        }
                    }
                    w[0] = 0;
                    strcat(w,t);
                    strcat(w,c);
                    wzkazania[i][j] = Tekst->renderText(w);
                    if(wzkazania[i][j] == NULL)
                    {
                        wiadomosc_o_bledzie(std::string("Render tekstu w") + std::to_string((int)i) + std::to_string((int)j) + std::string(": ") + std::string(TTF_GetError()));
                        Napisy_OK = false;
                        return;
                    }
                }
                if(litery[i] == NULL)
                {
                    wiadomosc_o_bledzie(std::string("Render tekstu t") + std::to_string((int)i) + std::string(": ") + std::string(TTF_GetError()));
                    Napisy_OK = false;
                    return;
                }
            }
        }
        ~CNapisy()
        {
            for(uint8_t i = 0; i < 10; i++)
            {
                if(litery[i] != NULL)
                    SDL_FreeSurface(litery[i]);
                if(liczby[i] != NULL)
                    SDL_FreeSurface(liczby[i]);
                for(uint8_t j = 0; j < 10; j++)
                    if(wzkazania[i][j] != NULL)
                        SDL_FreeSurface(wzkazania[i][j]);
            }
            for(uint8_t i = 0; i < 8; i++)
                if(napisy[i] != NULL)
                    SDL_FreeSurface(napisy[i]);
        }
        bool ok()
        {
            return Napisy_OK;
        }
        void rysuj(SDL_Surface* cel, uint8_t wygrana)
        {
            Tekst->drawText(napisy[0], cel, 180 - napisy[0]->w / 2 + XOFFSET, 15 - napisy[0]->h / 2);
            Tekst->drawText(napisy[1], cel, 540 - napisy[1]->w / 2 + XOFFSET, 15 - napisy[1]->h / 2);
            Tekst->drawText(napisy[2], cel, 30 + XOFFSET, 375 - napisy[2]->h / 2);
            Tekst->drawText(napisy[3], cel, 30 + XOFFSET, 375 - napisy[3]->h / 2 + min_odstep);
            if(wzk_gracz != NULL)
                Tekst->drawText(wzk_gracz, cel, 90 + XOFFSET, 375 - wzk_gracz->h / 2);
            if(wzk_wrog != NULL)
                Tekst->drawText(wzk_wrog, cel, 90 + XOFFSET, 375 - wzk_wrog->h / 2 + min_odstep);
            if(s_gracz != NULL)
                Tekst->drawText(s_gracz, cel, 150 + XOFFSET, 375 - s_gracz->h / 2);
            if(s_wrog != NULL)
                Tekst->drawText(s_wrog, cel, 150 + XOFFSET, 375 - s_wrog->h / 2 + min_odstep);
/*            Tekst->rysuj_tekst(napisy[4],cel,30 +XOFFSET,375 - napisy[4]->h/2 + 32);
            if(wygrana == 1)
                Tekst->rysuj_tekst(napisy[2],cel,330 - napisy[2]->w +XOFFSET,375 - napisy[2]->h/2 + 32);
            if(wygrana == 2)
                Tekst->rysuj_tekst(napisy[3],cel,330 - napisy[3]->w +XOFFSET,375 - napisy[3]->h/2 + 32);*/
            for(uint8_t i = 0; i < 10; i++)
            {
                Tekst->drawText(litery[i], cel, 45 + (30 * i) - litery[i]->w / 2 + XOFFSET, 45 - litery[i]->h / 2);
                Tekst->drawText(litery[i], cel, 405 + (30 * i) - litery[i]->w / 2 + XOFFSET, 45 - litery[i]->h / 2);
                Tekst->drawText(liczby[i], cel, 15 - liczby[i]->w / 2 + XOFFSET, 75 + (30 * i) - liczby[i]->h / 2);
                Tekst->drawText(liczby[i], cel, 375 - liczby[i]->w / 2 + XOFFSET, 75 + (30 * i) - liczby[i]->h / 2);
            }
        }
        void akt_napisy(uint8_t i, uint8_t x, uint8_t y, uint8_t s, bool reset)
        {
            if(reset)
            {
                wzk_gracz = NULL;
                wzk_wrog = NULL;
                s_gracz = NULL;
                s_wrog = NULL;
                return;
            }
            if(i == 0)
            {
                wzk_gracz = wzkazania[x][y];
                switch(s)
                {
                    case(0): {s_gracz = napisy[5];break;}
                    case(1): {s_gracz = napisy[6];break;}
                    case(4): {s_gracz = napisy[4];break;}
                    case(5): {s_gracz = napisy[7];break;}
                }
            }
            else
            {
                wzk_wrog = wzkazania[x][y];
                switch(s)
                {
                    case(0): {s_wrog = napisy[5];break;}
                    case(1): {s_wrog = napisy[6];break;}
                    case(4): {s_wrog = napisy[4];break;}
                    case(5): {s_wrog = napisy[7];break;}
                }
            }
        }
};
