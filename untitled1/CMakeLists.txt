cmake_minimum_required(VERSION 3.17)
project(untitled1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)

add_executable(untitled1 main.cpp Src/Game.cpp Src/Game.h Src/State.cpp Src/State.h Src/GameState.cpp Src/GameState.h Src/Entity.cpp Src/Entity.h Src/MainMenuState.cpp Src/MainMenuState.h Src/Button.cpp Src/Button.h Src/Player.cpp Src/Player.h Src/AnimationComponent.cpp Src/AnimationComponent.h Src/HitboxComponent.cpp Src/HitboxComponent.h Src/Tile.cpp Src/Tile.h Src/Enemy.cpp Src/Enemy.h Src/Turret.cpp Src/Turret.h Src/Bullet.cpp Src/Bullet.h Src/TileMap.cpp Src/TileMap.h)

set(SFML_DIR "C:\\Users\\Kirill\\CLionProjects\\lib\\GCC 7.3.0 MinGW (SEH) - 64-bit\\SFML-2.5.1\\lib\\cmake\\SFML")

target_link_libraries(untitled1 sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5 REQUIRED graphics network audio window system)