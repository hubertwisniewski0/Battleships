//
// Created by hubert25632 on 01.07.22.
//

#ifndef BATTLESHIPS_ENEMY_HPP
#define BATTLESHIPS_ENEMY_HPP

class Enemy {
private:
    Game *game;
    int8_t first_field[2] = {0, 0};
    int8_t prev_field[2] = {0, 0};
    int8_t direction[2] = {0, 0};
    int8_t prev_direction[2] = {0, 0};
    bool interested = false;

    // Memorize the last field, shooting direction and its effect (to be called after hitting a ship)
    void memorize(int8_t *field) {
        for (uint8_t i = 0; i < 2; i++) {
            prev_field[i] = field[i];
            prev_direction[i] = direction[i];
            if (!interested)
                first_field[i] = field[i];
        }
        interested = true;
    }

    void forgetDirection() {
        for (uint8_t i = 0; i < 2; i++) {
            direction[i] = 0;
        }
    }

    // Reset memory (to be called after sinking a ship)
    void forget() {
        forgetDirection();
        for (uint8_t i = 0; i < 2; i++) {
            prev_field[i] = 0;
            first_field[i] = 0;
            prev_direction[i] = 0;
        }
        interested = false;
    }

    // Invert the shooting direction and restore the last shot field as the first one (to be called after missing when interested)
    void invertDirection() {
        for (uint8_t i = 0; i < 2; i++) {
            direction[i] = -(prev_direction[i]);
            prev_field[i] = first_field[i];
        }
    }

    // Set the field to be offset by 'direction' from 'rel'
    void setRelativeTo(int8_t *field, int8_t *direction, int8_t *rel) {
        for (uint8_t i = 0; i < 2; i++)
            field[i] = rel[i] + direction[i];
    }

    // Check whether shooting the give field makes sense (if there is no known ships around)
    bool sensibleField(int8_t *field) {
        uint8_t p;
        for (int8_t i = field[0] - 1; i < field[0] + 2; i++) {
            for (int8_t j = field[1] - 1; j < field[1] + 2; j++) {
                if (interested && i == prev_field[0] && j == prev_field[1])
                    continue;
                p = game->field(0, i, j);
                if (p == 3 || p == 6) {
                    if (prev_field[0] == first_field[0] && prev_field[1] == first_field[1])
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
    Enemy(Game *game) : game(game) {}

    uint8_t move(uint8_t *x, uint8_t *y) {
        int8_t field[2], s;
        uint8_t tries = 0;
        while (true) {
            if (tries++ > 250) {
                forget();
                return 7;
            }

            // If the last shot was hit, check the nearby fields
            if (!interested)
                for (uint8_t i = 0; i < 2; i++)
                    field[i] = rand() % 10;
            else {
                // If there is no shooting direction set, generate a random one
                if (direction[0] == 0 && direction[1] == 0) {
                    for (int8_t i = 0; i < 2; i++) {
                        direction[i] = rand() % 3 - 1;
                        if (direction[0] != 0) {
                            direction[1] = 0;
                            break;
                        }
                    }
                }
                setRelativeTo(field, direction, prev_field);
            }

            if (sensibleField(field))
                s = game->shot(0, field[0], field[1]);
            else
                continue;

            *x = field[0];
            *y = field[1];

            if (s == 0 || s == 2 || s == 3 || s == 6) {
                if (interested)
                    invertDirection();
                if (s == 0)
                    break;
            }
            if (s == 1) {
                memorize(field);
                break;
            }
            if (s == 4)
                break;
            if (s == 5) {
                forget();
                break;
            }
        }
        return s;
    }

    void reset() {
        forget();
    }
};

#endif //BATTLESHIPS_ENEMY_HPP
