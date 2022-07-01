class CInterfejs
{
    private:
        COkno* Okno = NULL;
        CZegar* Zegar = NULL;
        SDL_Event zdarzenie;
        bool zakoncz = false;
        uint8_t wygrana = 0;
        CGra* Gra;
        CWrog* Wrog;
        uint8_t x,y;
        bool Interfejs_OK = true;
        void rysuj_plansze()
        {
            int p;
            for(uint8_t i = 0; i < 2; i++)
            {
                for(uint8_t j = 0; j < 10; j++)
                {
                    for(uint8_t k = 0; k < 10; k++)
                    {
                        p = Gra->pole(i,j,k);
                        Okno->akt_plansze(i,j,k,(p == 1 && i == 1 && wygrana == 0 ? 0 : p));
                    }
                }
            }
            Okno->rysuj(wygrana);
        }
        void reset()
        {
            Gra->nowa_gra();
            Wrog->reset();
            Okno->reset_napisy();
            wygrana = 0;
        }
        void wygrana_s(uint8_t w)
        {
            wygrana = w;
            rysuj_plansze();
            Okno->wygrana(wygrana);
        }
    public:
        CInterfejs(CGra* G, CWrog* K)
        {
            if(SDL_Init(SDL_INIT_VIDEO) != 0)
            {
                wiadomosc_o_bledzie(std::string("SDL_Init: ") + std::string(SDL_GetError()));
                Interfejs_OK = false;
                return;
            }
            Okno = new COkno;
            if(!Okno->ok())
            {
                Interfejs_OK = false;
                return;
            }
            Zegar = new CZegar;
            if(!Zegar->ok())
            {
                Interfejs_OK = false;
                return;
            }
            Gra = G;
            Wrog = K;
        }
        ~CInterfejs()
        {
            if(Zegar != NULL)
                delete Zegar;
            if(Okno != NULL)
                delete Okno;
            if(SDL_WasInit(0) != 0)
                SDL_Quit();
        }
        bool ok()
        {
            return Interfejs_OK;
        }
        void start()
        {
            int s;
            rysuj_plansze();
            while(!zakoncz)
            {
                while(SDL_PollEvent(&zdarzenie))
                {
                    if(zdarzenie.type == SDL_QUIT)
                        zakoncz = true;
                    if(zdarzenie.type == SDL_MOUSEMOTION)
                        Okno->rysuj(wygrana);
                    if(zdarzenie.type == SDL_MOUSEBUTTONDOWN &&
                    zdarzenie.button.x -XOFFSET >= 390 && zdarzenie.button.x -XOFFSET < 690 &&
                    zdarzenie.button.y >= 60 && zdarzenie.button.y < 360 &&
                    !wygrana)
                    {
                        x = (zdarzenie.button.x -XOFFSET)/30-13;
                        y = zdarzenie.button.y/30-2;
                        s = Gra->strzal(1,x,y);
                        if(s != 0 && s != 1 && s != 4 && s != 5)
                            continue;
                        Okno->akt_napisy(0,x,y,s,false);
                        if(s == 4)
                            wygrana_s(1);
                        else
                        {
                            s = Wrog->graj(&x,&y);
                            if(s == 7)
                                continue;
                            Okno->akt_napisy(1,x,y,s,false);
                            if(s == 4)
                                wygrana_s(2);
                        }
                        rysuj_plansze();
                    }
                    if(zdarzenie.type == SDL_KEYDOWN)
                    {
                        switch(zdarzenie.key.keysym.scancode)
                        {
                            case(SDL_SCANCODE_N):
                            {
                                reset();
                                rysuj_plansze();
                                break;
                            }
                            case(SDL_SCANCODE_ESCAPE):
                            {
                                zakoncz = true;
                                break;
                            }
                            default: {break;}
                        }
                    }
                }
                Zegar->synchronizuj();
            }
        }
};
