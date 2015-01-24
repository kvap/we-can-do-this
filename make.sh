#!/bin/sh
set -ex
g++ -o wcdt -std=c++11 main.cpp -lsfml-graphics -lsfml-window -lsfml-system -lGL
g++ -o wcdt-editor -std=c++11 editor.cpp Object.cpp Tile.cpp -lsfml-graphics -lsfml-window -lsfml-system -lGL
