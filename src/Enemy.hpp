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

    bool interested = false;
    Game::Position lastHitPosition;
    ShootingDirection lastShootingDirection = ShootingDirection::None;

    std::random_device rd;
    std::minstd_rand rng;

    // Invert the shooting direction and restore the last shot field as the first one (to be called after missing when interested)
    static ShootingDirection getInverseDirection(Enemy::ShootingDirection shootingDirection);

    // Get the field offset by 'shootingDirection' from 'rel'
    static Game::Position getRelativeTo(ShootingDirection shootingDirection, Game::Position rel);

    // Check whether shooting the give field makes sense (if there is no known ships around)
    bool sensibleField(Game::Position position);

public:
    explicit Enemy(Game *game);

    std::tuple<Game::Position, Game::ShootingResult> move();

    void reset();
};

#endif //BATTLESHIPS_ENEMY_HPP
