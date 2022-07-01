class CTekst
{
    private:
        TTF_Font* czcionka = NULL;
        SDL_Color kolor_tekstu;
        SDL_Color kolor_tla;
        bool Tekst_OK = true;
    public:
        CTekst()
        {
            if(TTF_Init() != 0)
            {
                wiadomosc_o_bledzie(std::string("TTF_Init: ") + std::string(TTF_GetError()));
                Tekst_OK = false;
                return;
            }
            czcionka = TTF_OpenFont(TTF_FONT_PATH,16);
            if(czcionka == NULL)
            {
                wiadomosc_o_bledzie(std::string("TTF_OpenFont: ") + std::string(TTF_GetError()));
                Tekst_OK = false;
                return;
            }
            kolor_tekstu.r = 0xFF;
            kolor_tekstu.g = 0xFF;
            kolor_tekstu.b = 0xFF;
            kolor_tekstu.a = 0xFF;
            kolor_tla.r = 0x00;
            kolor_tla.g = 0x00;
            kolor_tla.b = 0x00;
            kolor_tla.a = 0xFF;
        }
        ~CTekst()
        {
            if(czcionka != NULL)
                TTF_CloseFont(czcionka);
            if(TTF_WasInit() != 0)
                TTF_Quit();
        }
        bool ok()
        {
            return Tekst_OK;
        }
        SDL_Surface* renderuj_tekst(const char* tekst)
        {
            return TTF_RenderUTF8_Shaded(czcionka,tekst,kolor_tekstu,kolor_tla);
        }
/*        SDL_Surface* renderuj_znak(uint16_t znak)
        {
            return TTF_RenderGlyph_Solid(czcionka,znak,kolor_tekstu);
        }*/
        void rysuj_tekst(SDL_Surface* tekst, SDL_Surface* cel, uint16_t x, uint16_t y)
        {
            SDL_Rect pozycja;
            pozycja.x = x;
            pozycja.y = y;
            SDL_BlitSurface(tekst,NULL,cel,&pozycja);

        }
        int min_odstep()
        {
            return TTF_FontLineSkip(czcionka);
        }
};
