//
// Created by hubert25632 on 01.07.22.
//

#include "Enemy.hpp"

Enemy::Enemy(Game *game) : game(game), rng(rd()) {}

// Invert the shooting direction and restore the last shot field as the first one (to be called after missing when interested)
Enemy::ShootingDirection Enemy::getInverseDirection(Enemy::ShootingDirection shootingDirection) {
    return static_cast<ShootingDirection>((~static_cast<unsigned>(shootingDirection)) & 0x3);
}

// Set the field to be offset by 'direction' from 'rel'
Game::Position Enemy::getRelativeTo(ShootingDirection shootingDirection, Game::Position rel) {
    Game::Position newPosition = rel;
    switch (shootingDirection) {
        case ShootingDirection::Left: {
            newPosition.x -= 1;
            break;
        }
        case ShootingDirection::Right: {
            newPosition.x += 1;
            break;
        }
        case ShootingDirection::Up: {
            newPosition.y -= 1;
            break;
        }
        case ShootingDirection::Down: {
            newPosition.y += 1;
            break;
        }
    }
    return newPosition;
}

// Check whether shooting the give field makes sense (if there is no known ships around)
bool Enemy::sensibleField(Game::Position position) {
    if (game->getFieldObscured(Game::BoardOwner::Player, position) != Game::FieldType::Empty)
        return false;

    for (uint8_t j = position.x - (position.x > 0); j <= position.x + 1; j++) {
        for (uint8_t k = position.y - (position.y > 0); k <= position.y + 1; k++) {
            Game::FieldType fieldType = game->getFieldObscured(Game::BoardOwner::Player, {j, k});
            if (fieldType != Game::FieldType::Empty && fieldType != Game::FieldType::Miss)
                return false;
        }
    }

    return true;
}

std::tuple<Game::Position, Game::ShootingResult> Enemy::move() {
    Game::Position position;
    Game::ShootingResult shootingResult;
    while (true) {
        // If not interested, choose random coordinates and shoot
        if (!interested) {
            position.x = rng() % 10;
            position.y = rng() % 10;

            if (sensibleField(position)) {
                shootingResult = game->shot(Game::BoardOwner::Player, position);
                // If hit, remember the position and become interested
                if (shootingResult == Game::ShootingResult::Hit) {
                    lastHitPosition = position;
                    interested = true;
                }
                break;
            }
            else
                continue;
        }
        else {
            // If there is no shooting direction determined (interested and hit once)
            if (lastShootingDirection == ShootingDirection::None) {
                // Choose a random direction and shoot the last hit position's neighbour
                auto shootingDirection = static_cast<ShootingDirection>(rng() % 4);
                position = getRelativeTo(shootingDirection, lastHitPosition);
                if (Game::positionWithinLimits(position))
                    shootingResult = game->shot(Game::BoardOwner::Player, position);
                else
                    continue;

                // If unable to shoot, retry
                if (shootingResult == Game::ShootingResult::Invalid)
                    continue;
                    // If missed, end move
                else if (shootingResult == Game::ShootingResult::Miss)
                    break;
                    // If hit, remember this position and direction
                else if (shootingResult == Game::ShootingResult::Hit) {
                    lastHitPosition = position;
                    lastShootingDirection = shootingDirection;
                    break;
                }
                    // If sunk, stop being interested (return to random shooting)
                else if (shootingResult == Game::ShootingResult::Sunk) {
                    interested = false;
                    break;
                }
            }
                // If there is a shooting direction determined (interested and hit at least twice)
            else {
                // Move to the next field following the determined direction. If the next field has already been hit, continue (try to find the next field after the known ship edge).
                position = lastHitPosition;
                do {
                    position = getRelativeTo(lastShootingDirection, position);
                } while (game->getFieldObscured(Game::BoardOwner::Player, position) == Game::FieldType::Hit);

                if (Game::positionWithinLimits(position))
                    shootingResult = game->shot(Game::BoardOwner::Player, position);
                else {
                    lastShootingDirection = getInverseDirection(lastShootingDirection);
                    continue;
                }

                // If unable to shoot, invert direction and retry
                if (shootingResult == Game::ShootingResult::Invalid) {
                    lastShootingDirection = getInverseDirection(lastShootingDirection);
                    continue;
                }
                    // If missed, invert direction and end move
                else if (shootingResult == Game::ShootingResult::Miss) {
                    lastShootingDirection = getInverseDirection(lastShootingDirection);
                    break;
                }
                    // If hit, remember this position
                else if (shootingResult == Game::ShootingResult::Hit) {
                    lastHitPosition = position;
                    break;
                }
                    // If sunk, stop being interested and forget the direction
                else if (shootingResult == Game::ShootingResult::Sunk) {
                    interested = false;
                    lastShootingDirection = ShootingDirection::None;
                    break;
                }
            }
        }
    }

    return {position, shootingResult};
}

void Enemy::reset() {
    interested = false;
    lastShootingDirection = ShootingDirection::None;
}
