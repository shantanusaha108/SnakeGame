#pragma once
#include <vector>

struct Segment {
    int x, y;
};

class Game {
public:
    int width, height;
    int direction;      
    std::vector<Segment> snake;
    Segment food;

    Game(int w, int h);

    bool update();          
    void changeDirection(int dir);
    void spawnFood();
    bool checkCollision();
};
