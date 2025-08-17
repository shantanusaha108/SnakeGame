#pragma once
#ifndef GAME_H
#define GAME_H

#include <vector>

struct Segment {
    int x, y;
};

class Game {
public:
    int width, height;
    std::vector<Segment> snake;
    Segment food;
    int direction; // 0=up,1=right,2=down,3=left

    Game(int w, int h);
    void update();
    void changeDirection(int dir);
    void spawnFood();
    bool checkCollision();
};

#endif
