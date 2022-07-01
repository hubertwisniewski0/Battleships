//
// Created by hubert25632 on 01.07.22.
//

#ifndef BATTLESHIPS_GUI_HPP
#define BATTLESHIPS_GUI_HPP

class GUI
{
private:
    Window* window = NULL;
    Timer* timer = NULL;
    SDL_Event event;
    bool quit = false;
    uint8_t victory = 0;
    Game* game;
    Enemy* enemy;
    uint8_t x,y;
    bool guiOk = true;

    void drawBoards()
    {
        int p;
        // For each board
        for(uint8_t i = 0; i < 2; i++)
        {
            // For each column
            for(uint8_t j = 0; j < 10; j++)
            {
                // For each row
                for(uint8_t k = 0; k < 10; k++)
                {
                    p = game->field(i, j, k);
                    window->updateBoards(i, j, k, (p == 1 && i == 1 && victory == 0 ? 0 : p));
                }
            }
        }
        window->draw(victory);
    }

    void reset()
    {
        game->newGame();
        enemy->reset();
        window->resetTexts();
        victory = 0;
    }

    void announceVictory(uint8_t w)
    {
        victory = w;
        drawBoards();
        window->victory(victory);
    }

public:
    GUI(Game* G, Enemy* K)
    {
        if(SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            errorMessage(std::string("SDL_Init: ") + std::string(SDL_GetError()));
            guiOk = false;
            return;
        }
        window = new Window;
        if(!window->ok())
        {
            guiOk = false;
            return;
        }
        timer = new Timer;
        if(!timer->ok())
        {
            guiOk = false;
            return;
        }
        game = G;
        enemy = K;
    }

    ~GUI()
    {
        if(timer != NULL)
            delete timer;
        if(window != NULL)
            delete window;
        if(SDL_WasInit(0) != 0)
            SDL_Quit();
    }

    bool ok()
    {
        return guiOk;
    }

    void start()
    {
        int s;
        drawBoards();
        while(!quit)
        {
            while(SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT)
                    quit = true;
                if(event.type == SDL_MOUSEMOTION)
                    window->draw(victory);
                if(event.type == SDL_MOUSEBUTTONDOWN &&
                   event.button.x - XOFFSET >= 390 && event.button.x - XOFFSET < 690 &&
                   event.button.y >= 60 && event.button.y < 360 &&
                   !victory)
                {
                    x = (event.button.x - XOFFSET) / 30 - 13;
                    y = event.button.y / 30 - 2;
                    s = game->shot(1, x, y);
                    if(s != 0 && s != 1 && s != 4 && s != 5)
                        continue;
                    window->updateTexts(0, x, y, s, false);
                    if(s == 4)
                        announceVictory(1);
                    else
                    {
                        s = enemy->move(&x, &y);
                        if(s == 7)
                            continue;
                        window->updateTexts(1, x, y, s, false);
                        if(s == 4)
                            announceVictory(2);
                    }
                    drawBoards();
                }
                if(event.type == SDL_KEYDOWN)
                {
                    switch(event.key.keysym.scancode)
                    {
                        case(SDL_SCANCODE_N):
                        {
                            reset();
                            drawBoards();
                            break;
                        }
                        case(SDL_SCANCODE_ESCAPE):
                        {
                            quit = true;
                            break;
                        }
                        default: {break;}
                    }
                }
            }
            timer->synchronize();
        }
    }
};

#endif //BATTLESHIPS_GUI_HPP
