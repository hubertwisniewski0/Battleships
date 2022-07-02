//
// Created by hubert25632 on 01.07.22.
//

#ifndef BATTLESHIPS_ENEMY_HPP
#define BATTLESHIPS_ENEMY_HPP

#include "Game.hpp"
#include <cstdint>
#include <tuple>

class Enemy {
private:
    Game *game;
    int8_t first_field[2] = {0, 0};
    int8_t prev_field[2] = {0, 0};
    int8_t direction[2] = {0, 0};
    int8_t prev_direction[2] = {0, 0};
    bool interested = false;

    // Memorize the last field, shooting direction and its effect (to be called after hitting a ship)
    void memorize(int8_t *field);

    void forgetDirection();

    // Reset memory (to be called after sinking a ship)
    void forget();

    // Invert the shooting direction and restore the last shot field as the first one (to be called after missing when interested)
    void invertDirection();

    // Set the field to be offset by 'direction' from 'rel'
    void setRelativeTo(int8_t *field, int8_t *direction, int8_t *rel);

    // Check whether shooting the give field makes sense (if there is no known ships around)
    bool sensibleField(int8_t *field);

public:
    explicit Enemy(Game *game);

    std::tuple<uint8_t, uint8_t, Game::ShootingResult> move();

    void reset();
};

#endif //BATTLESHIPS_ENEMY_HPP
