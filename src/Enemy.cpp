//
// Created by hubert25632 on 01.07.22.
//

#include "Enemy.hpp"
#include <cstdlib>

Enemy::Enemy(Game *game) : game(game) {}

void Enemy::memorize(Game::Position position) {
    prevField = position;
    prevDirection = direction;
    if (!interested)
        firstField = position;
    interested = true;
}

void Enemy::forgetDirection() {
    direction = ShootingDirection::None;
}

// Reset memory (to be called after sinking a ship)
void Enemy::forget() {
    forgetDirection();
    prevField = {0, 0};
    firstField = {0, 0};
    prevDirection = ShootingDirection::None;
    interested = false;
}

// Invert the shooting direction and restore the last shot field as the first one (to be called after missing when interested)
void Enemy::invertDirection() {
    if (direction != ShootingDirection::None)
        direction = static_cast<ShootingDirection>((~static_cast<unsigned>(prevDirection)) & 0x3);
    prevField = firstField;
}

// Set the field to be offset by 'direction' from 'rel'
Game::Position Enemy::getRelativeTo(ShootingDirection shootingDirection, Game::Position rel) {
    Game::Position newPosition = rel;
    switch (shootingDirection) {
        case ShootingDirection::Left: {
            newPosition.x -= (rel.x > 0);
            break;
        }
        case ShootingDirection::Right: {
            newPosition.x += (rel.x < 9);
            break;
        }
        case ShootingDirection::Up: {
            newPosition.y -= (rel.y > 0);
            break;
        }
        case ShootingDirection::Down: {
            newPosition.y += (rel.y < 9);
            break;
        }
    }
    return newPosition;
}

// Check whether shooting the give field makes sense (if there is no known ships around)
bool Enemy::sensibleField(Game::Position position) {
    Game::FieldType f;
    for (uint8_t i = position.x - (position.x > 0); i <= position.x + 1; i++) {
        for (uint8_t j = position.y - (position.y > 0); j <= position.y + 1; j++) {
            if (interested && i == prevField.x && j == prevField.y)
                continue;
            f = game->getField(Game::BoardOwner::Player, {i, j});
            if (f == Game::FieldType::Hit || f == Game::FieldType::Sunk) {
                if (prevField.x == firstField.x && prevField.y == firstField.y)
                    forgetDirection();
                else
                    invertDirection();
                return false;
            }
        }
    }
    return true;
}

std::tuple<uint8_t, uint8_t, Game::ShootingResult> Enemy::move() {
    Game::ShootingResult r;
    Game::Position position;
    while (true) {
        // If the last shot was hit, check the nearby fields
        if (!interested) {
            position.x = rand() % 10;
            position.y = rand() % 10;
        } else {
            // If there is no shooting direction set, generate a random one
            if (direction == ShootingDirection::None)
                direction = static_cast<ShootingDirection>(rand() % 4);

            position = getRelativeTo(direction, prevField);
        }

        if (sensibleField(position))
            r = game->shot(Game::BoardOwner::Player, position);
        else
            continue;

        if (r == Game::ShootingResult::Miss || r == Game::ShootingResult::Invalid) {
            if (interested)
                invertDirection();
            if (r == Game::ShootingResult::Miss)
                break;
        }

        if (r == Game::ShootingResult::Hit) {
            memorize(position);
            break;
        }

        if (r == Game::ShootingResult::Sunk) {
            forget();
            break;
        }
    }
    return {position.x, position.y, r};
}

void Enemy::reset() {
    forget();
}
