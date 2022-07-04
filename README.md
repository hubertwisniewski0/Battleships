# Battleships

A Battleships game written  in C++ with GUI implemented in SDL2.
It has been originally created in 2019 as a school project and then translated and mostly rewritten in 2022.

## Description

You are playing Battleships against the computer-controlled enemy.
Click on the board described as "Enemy's sea" to take a shot.

## Dependencies

- CMake 3.18
- pkg-config
- SDL2
- SDL_ttf (for SDL2)
- C++ compiler with C++17 support

## Building and running

This project uses CMake as an automatic building system.
Simplest use case (assuming a UNIX-like environment):

    mkdir build
    cd build
    cmake ..
    make
    ./battleships
