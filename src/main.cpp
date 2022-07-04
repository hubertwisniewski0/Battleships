#include "Game.hpp"
#include "Enemy.hpp"
#include "GUI.hpp"

int main() {
    Game game;
    Enemy enemy(&game);
    GUI gui(&game, &enemy);
    gui.initialize();
    gui.start();
    return 0;
}
