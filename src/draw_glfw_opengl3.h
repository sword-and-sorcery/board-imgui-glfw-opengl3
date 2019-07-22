
#pragma once

#include <string>
#include "board_game/layer.h"
#include <map>

class Draw {
public:
    Draw() {};
    ~Draw() {};

    void draw(const std::string &tileset, const std::string &tile, const tile_position &position);
public:
    std::map<std::string, float> units;
};
