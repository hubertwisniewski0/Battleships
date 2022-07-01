class Game
{
    private:
        uint8_t boards[2][10][10];

        void clearBoards()
        {
            for(uint8_t i = 0; i < 2; i++)
                for(uint8_t j = 0; j < 10; j++)
                    for(uint8_t k = 0; k < 10; k++)
                        boards[i][j][k] = 0;
        }

        void generateBoards()
        {
            // For each board
            for(uint8_t i = 0; i < 2; i++)
            {
                // For each possible ship length
                for(uint8_t l = 4; l > 0;l--)
                {
                    // For each ship
                    for(uint8_t c = 0; c < 5-l;)
                    {
                        // Ship start coordinates
                        uint8_t start[2];

                        // Generate a random direction: 0 - horizontal, 1 - vertical
                        uint8_t direction;
                        direction = rand() % 2;

                        if(direction == 0)
                        {
                            start[0] = rand() % (10 - (l-1));
                            start[1] = rand() % 10;
                        }
                        else
                        {
                            start[0] = rand() % 10;
                            start[1] = rand() % (10 - (l-1));
                        }

                        // Check if there is enough space to place a ship (ignore board boundaries)
                        bool available = true;
                        for(int8_t ckx = start[0]-1; ckx < start[0]+(direction == 0 ? l + 1 : 2) && available; ckx++)
                        {
                            for(int8_t cky = start[1]-1; cky < start[1]+(direction == 0 ? 2 : l + 1) && available; cky++)
                            {
                                if(ckx < 0 || ckx > 9 || cky < 0 || cky > 9)
                                    continue;
                                if(boards[i][ckx][cky] != 0)
                                    available = false;
                            }
                        }

                        // If the searched space is available, place the ship and increase the placed ship count
                        if(available)
                        {
                            if(direction == 0)
                                for(uint8_t field = start[0]; field < start[0] + l; field++)
                                    boards[i][field][start[1]] = 1;
                            else
                                for(uint8_t field = start[1]; field < start[1] + l; field++)
                                    boards[i][start[0]][field] = 1;
                            c++;
                        }
                    }
                }
            }
        }

        bool sunk(uint8_t i, uint8_t x, uint8_t y, uint8_t p_x, uint8_t p_y, bool mark)
        {
            for(int8_t j = x-1; j < x+2; j++)
            {
                for(int8_t k = y-1; k < y+2; k++)
                {
                    if(j < 0 || j > 9 || k < 0 || k > 9 || ( j == x && k == y ) || ( j == p_x && k == p_y ) )
                        continue;
                    if(boards[i][j][k] == 1)
                        return false;
                    else if(boards[i][j][k] == 3)
                        if(!sunk(i, j, k, x, y, mark))
                            return false;
                }
            }
            if(mark)
                boards[i][x][y] = 6;
            return true;
        }

    public:
        void newGame()
        {
            clearBoards();
            generateBoards();
        }

        Game()
        {
            newGame();
        }

        uint8_t shot(uint8_t i, uint8_t x, uint8_t y)
        {
            if(x > 9 || y > 9)
                return 2;
            uint8_t prev = boards[i][x][y];
            if(prev == 0)
                boards[i][x][y] = 2;
            else if(prev == 1)
                boards[i][x][y] = 3;
            bool victory = true;
            for(uint8_t j = 0; j < 10 && victory; j++)
                for(uint8_t k = 0; k < 10 && victory; k++)
                    if(boards[i][j][k] == 1)
                        victory = false;
            if(prev != 1)
                return prev;
            else if(sunk(i, x, y, x, y, false) || victory)
            {
                sunk(i, x, y, x, y, true);
                if(victory)
                    return 4;
                else
                    return 5;
            }
            else
                return 1;
        }

        uint8_t field(uint8_t i, uint8_t x, uint8_t y)
        {
            if(x > 9 || y > 9)
                return 2;
            uint8_t p = boards[i][x][y];
            return p;
        }
};

class Enemy
{
    private:
        Game* game;
        int8_t first_field[2] = {0, 0};
        int8_t prev_field[2] = {0, 0};
        int8_t direction[2] = {0, 0};
        int8_t prev_direction[2] = {0, 0};
        bool interested = false;

        // Memorize the last field, shooting direction and its effect (to be called after hitting a ship)
        void memorize(int8_t* field)
        {
            for(uint8_t i = 0; i < 2; i++)
            {
                prev_field[i] = field[i];
                prev_direction[i] = direction[i];
                if(!interested)
                    first_field[i] = field[i];
            }
            interested = true;
        }

        void forgetDirection()
        {
            for(uint8_t i = 0; i < 2; i++)
            {
                direction[i] = 0;
            }
        }

        // Reset memory (to be called after sinking a ship)
        void forget()
        {
            forgetDirection();
            for(uint8_t i = 0; i < 2; i++)
            {
                prev_field[i] = 0;
                first_field[i] = 0;
                prev_direction[i] = 0;
            }
            interested = false;
        }

        // Invert the shooting direction and restore the last shot field as the first one (to be called after missing when interested)
        void invertDirection()
        {
            for(uint8_t i = 0; i < 2; i++)
            {
                direction[i] = -(prev_direction[i]);
                prev_field[i] = first_field[i];
            }
        }

        // Set the field to be offset by 'direction' from 'rel'
        void setRelativeTo(int8_t* field, int8_t* direction, int8_t* rel)
        {
            for(uint8_t i = 0; i < 2; i++)
                field[i] = rel[i] + direction[i];
        }

        // Check whether shooting the give field makes sense (if there is no known ships around)
        bool sensibleField(int8_t* field)
        {
            uint8_t p;
            for(int8_t i = field[0] - 1; i < field[0] + 2; i++)
            {
                for(int8_t j = field[1] - 1; j < field[1] + 2; j++)
                {
                    if(interested && i == prev_field[0] && j == prev_field[1])
                        continue;
                    p = game->field(0, i, j);
                    if(p == 3 || p == 6)
                    {
                        if(prev_field[0] == first_field[0] && prev_field[1] == first_field[1])
                            forgetDirection();
                        else
                            invertDirection();
                        return false;
                    }
                }
            }
            return true;
        }

    public:
        Enemy(Game* game) : game(game)
        {}

        uint8_t move(uint8_t *x, uint8_t *y)
        {
            int8_t field[2],s;
            uint8_t tries = 0;
            while(true)
            {
                if(tries++ > 250)
                {
                    forget();
                    return 7;
                }

                // If the last shot was hit, check the nearby fields
                if(!interested)
                    for(uint8_t i = 0; i < 2; i++)
                        field[i] = rand() % 10;
                else
                {
                    // If there is no shooting direction set, generate a random one
                    if(direction[0] == 0 && direction[1] == 0)
                    {
                        for(int8_t i = 0; i < 2; i++)
                        {
                            direction[i] = rand() % 3 - 1;
                            if(direction[0] != 0)
                            {
                                direction[1] = 0;
                                break;
                            }
                        }
                    }
                    setRelativeTo(field, direction, prev_field);
                }

                if(sensibleField(field))
                    s = game->shot(0, field[0], field[1]);
                else
                    continue;

                *x = field[0];
                *y = field[1];

                if(s == 0 || s == 2 || s == 3 || s == 6)
                {
                    if(interested)
                        invertDirection();
                    if(s == 0)
                        break;
                }
                if(s == 1)
                {
                    memorize(field);
                    break;
                }
                if(s == 4)
                    break;
                if(s == 5)
                {
                    forget();
                    break;
                }
            }
            return s;
        }
        void reset()
        {
            forget();
        }
};
