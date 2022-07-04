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
    gui.initialize();
    gui.start();
    return 0;
}
