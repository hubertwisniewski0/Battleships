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
    // Order is important here - direction can be inverted by bitwise negation
    enum class ShootingDirection {
        Left,
        Up,
        Down,
        Right,
        None
    };

    Game *game;
    Game::Position firstField;
    Game::Position prevField;
    ShootingDirection direction;
    ShootingDirection prevDirection;
    bool interested = false;

    // Memorize the last field, shooting direction and its effect (to be called after hitting a ship)
    void memorize(Game::Position position);

    void forgetDirection();

    // Reset memory (to be called after sinking a ship)
    void forget();

    // Invert the shooting direction and restore the last shot field as the first one (to be called after missing when interested)
    void invertDirection();

    // Get the field offset by 'shootingDirection' from 'rel'
    Game::Position getRelativeTo(ShootingDirection shootingDirection, Game::Position rel);

    // Check whether shooting the give field makes sense (if there is no known ships around)
    bool sensibleField(Game::Position position);

public:
    explicit Enemy(Game *game);

    std::tuple<uint8_t, uint8_t, Game::ShootingResult> move();

    void reset();
};

#endif //BATTLESHIPS_ENEMY_HPP
