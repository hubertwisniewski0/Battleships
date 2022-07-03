cmake_minimum_required(VERSION 3.18)
project(battleships)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(PkgConfig)
pkg_check_modules(SDL2_ttf REQUIRED SDL2_ttf)

find_file(TTF_FONT_PATH "DejaVuSans.ttf" PATHS "res" REQUIRED)

add_executable(battleships
        src/main.cpp
        src/Board.cpp
        src/Enemy.cpp
        src/Game.cpp
        src/GUI.cpp
        src/Legend.cpp
        src/Messages.cpp
        src/Text.cpp
        src/Texts.cpp
        src/Timer.cpp
        src/Window.cpp)

target_include_directories(battleships PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_ttf_INCLUDE_DIRS})
target_link_libraries(battleships PRIVATE ${SDL2_LIBRARIES} ${SDL2_ttf_LIBRARIES} "-pthread")
target_compile_definitions(battleships PRIVATE TTF_FONT_PATH="${TTF_FONT_PATH}")
