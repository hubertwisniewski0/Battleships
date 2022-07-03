#include "Game.hpp"
#include "Enemy.hpp"
#include "GUI.hpp"
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[]) {
    srand(time(NULL));
    Game game;
    Enemy enemy(&game);
    GUI gui(&game, &enemy);
    if (!gui.ok())
        return 1;
    gui.start();
    return 0;
}
