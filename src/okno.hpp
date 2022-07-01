class COkno
{
    private:
        SDL_Window* okno = NULL;
        CPlansza* Plansza[2] = {NULL,NULL};
        CTekst* Tekst = NULL;
        CLegenda* Legenda = NULL;
        CNapisy* Napisy = NULL;
        bool Okno_OK = true;
    public:
        COkno()
        {
            okno = SDL_CreateWindow("Statki",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,0);
            if(okno == NULL)
            {
                wiadomosc_o_bledzie(std::string("SDL_CreateWindow: ") + std::string(SDL_GetError()));
                Okno_OK = false;
                return;
            }
            for(uint8_t i = 0; i < 2; i++)
            {
                Plansza[i] = new CPlansza;
                if(!Plansza[i]->ok())
                {
                    Okno_OK = false;
                    return;
                }
            }
            Tekst = new CTekst;
            if(!Tekst->ok())
            {
                Okno_OK = false;
                return;
            }
            Legenda = new CLegenda(Tekst);
            if(!Legenda->ok())
            {
                Okno_OK = false;
                return;
            }
            Napisy = new CNapisy(Tekst);
            if(!Napisy->ok())
            {
                Okno_OK = false;
                return;
            }
        }
        ~COkno()
        {
            if(Napisy != NULL)
                delete Napisy;
            if(Legenda != NULL)
                delete Legenda;
            if(Tekst != NULL)
                delete Tekst;
            for(uint8_t i = 0; i < 2; i++)
                if(Plansza[i] != NULL)
                    delete Plansza[i];
            if(okno != NULL)
                SDL_DestroyWindow(okno);
        }
        bool ok()
        {
            return Okno_OK;
        }
        void rysuj(uint8_t wygrana)
        {
            SDL_FillRect(SDL_GetWindowSurface(okno),NULL,0);
            for(uint8_t i = 0; i < 2; i++)
                Plansza[i]->rysuj(SDL_GetWindowSurface(okno),29+360*i +XOFFSET,59);
            Legenda->rysuj(SDL_GetWindowSurface(okno),389 +XOFFSET,374);
            Napisy->rysuj(SDL_GetWindowSurface(okno),wygrana);
            SDL_UpdateWindowSurface(okno);
        }
        void akt_plansze(uint8_t i, uint8_t x, uint8_t y, uint8_t s)
        {
            Plansza[i]->aktualizuj(x,y,s);
        }
        void reset_napisy()
        {
            Napisy->akt_napisy(0,0,0,0,true);
        }
        void akt_napisy(uint8_t i, uint8_t x, uint8_t y, uint8_t s, bool reset)
        {
            Napisy->akt_napisy(i,x,y,s,reset);
        }
        void wygrana(uint8_t w)
        {
            if(w == 1)
                wiadomosc_o_wygranej(std::string("Zwycięstwo gracza"),okno);
            else
                wiadomosc_o_wygranej(std::string("Zwycięstwo wroga"),okno);
        }
};
