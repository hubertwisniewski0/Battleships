class CPlansza
{
    private:
        SDL_Surface* plansza = NULL;
        SDL_Rect pole;
        bool Plansza_OK = true;
    public:
        CPlansza()
        {
            plansza = SDL_CreateRGBSurface(0,302,302,24,0,0,0,0);
            if(plansza == NULL)
            {
                wiadomosc_o_bledzie(std::string("SDL_CreateRGBSurface: ") + std::string(SDL_GetError()));
                Plansza_OK = false;
                return;
            }
            pole.h = 28;
            pole.w = 28;
            SDL_FillRect(plansza,NULL,0xFFFFFF);
        }
        ~CPlansza()
        {
            if(plansza != NULL)
                SDL_FreeSurface(plansza);
        }
        bool ok()
        {
            return Plansza_OK;
        }
        void aktualizuj(uint8_t x, uint8_t y, uint8_t s)
        {
            if(x > 9 || y > 9)
                return;
            pole.x = x*(pole.w+2)+2;
            pole.y = y*(pole.h+2)+2;
            uint32_t kolor;
            switch(s)
            {
                case(0): {kolor = 0x0000FF; break;}
                case(1): {kolor = 0x00FF00; break;}
                case(2): {kolor = 0x7F7F7F; break;}
                case(3): {kolor = 0xFFFF00; break;}
                case(6): {kolor = 0xFF0000; break;}
                default: {kolor = 0x000000; break;}
            }
            SDL_FillRect(plansza,&pole,kolor);
        }
        void rysuj(SDL_Surface* cel, uint16_t x, uint16_t y)
        {
            SDL_Rect pozycja;
            pozycja.x = x;
            pozycja.y = y;
            SDL_BlitSurface(plansza,NULL,cel,&pozycja);
        }
};
