class Window
{
    private:
        SDL_Window* window = NULL;
        Board* board[2] = {NULL, NULL};
        Text* text = NULL;
        Legend* legend = NULL;
        Texts* texts = NULL;
        bool windowOk = true;

    public:
        Window()
        {
            window = SDL_CreateWindow("Battleships", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
            if(window == NULL)
            {
                wiadomosc_o_bledzie(std::string("SDL_CreateWindow: ") + std::string(SDL_GetError()));
                windowOk = false;
                return;
            }
            for(uint8_t i = 0; i < 2; i++)
            {
                board[i] = new Board;
                if(!board[i]->ok())
                {
                    windowOk = false;
                    return;
                }
            }
            text = new Text;
            if(!text->ok())
            {
                windowOk = false;
                return;
            }
            legend = new Legend(text);
            if(!legend->ok())
            {
                windowOk = false;
                return;
            }
            texts = new Texts(text);
            if(!texts->ok())
            {
                windowOk = false;
                return;
            }
        }

        ~Window()
        {
            if(texts != NULL)
                delete texts;
            if(legend != NULL)
                delete legend;
            if(text != NULL)
                delete text;
            for(uint8_t i = 0; i < 2; i++)
                if(board[i] != NULL)
                    delete board[i];
            if(window != NULL)
                SDL_DestroyWindow(window);
        }
        bool ok()
        {
            return windowOk;
        }

        void draw(uint8_t victory)
        {
            SDL_FillRect(SDL_GetWindowSurface(window), NULL, 0);
            for(uint8_t i = 0; i < 2; i++)
                board[i]->draw(SDL_GetWindowSurface(window), 29 + 360 * i + XOFFSET, 59);
            legend->draw(SDL_GetWindowSurface(window), 389 + XOFFSET, 374);
            texts->draw(SDL_GetWindowSurface(window));
            SDL_UpdateWindowSurface(window);
        }

        void updateBoards(uint8_t i, uint8_t x, uint8_t y, uint8_t s)
        {
            board[i]->update(x, y, s);
        }

        void resetTexts()
        {
            texts->updateTexts(0, 0, 0, 0, true);
        }

        void updateTexts(uint8_t i, uint8_t x, uint8_t y, uint8_t s, bool reset)
        {
            texts->updateTexts(i, x, y, s, reset);
        }

        void victory(uint8_t w)
        {
            if(w == 1)
                wiadomosc_o_wygranej(std::string("Player's victory"), window);
            else
                wiadomosc_o_wygranej(std::string("Enemy's victory"), window);
        }
};
