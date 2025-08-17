#include "Game.h"
#include <cstdlib>
#include <ctime>

Game::Game(int w, int h) : width(w), height(h), direction(1) {
    snake.push_back({ w / 2, h / 2 });
    srand(static_cast<unsigned>(time(0)));
    spawnFood();
}

bool Game::update() {
    // Move the snake body
    for (int i = snake.size() - 1; i > 0; --i) {
        snake[i] = snake[i - 1];
    }

    // Move the head
    switch (direction) {
    case 0: snake[0].y -= 1; break; 
    case 1: snake[0].x += 1; break; 
    case 2: snake[0].y += 1; break; 
    case 3: snake[0].x -= 1; break; 
    }

    // SCREEN WRAPPING
    if (snake[0].x < 0) snake[0].x = width - 1;
    if (snake[0].x >= width) snake[0].x = 0;
    if (snake[0].y < 0) snake[0].y = height - 1;
    if (snake[0].y >= height) snake[0].y = 0;

    // Check self-collision before growing
    if (checkCollision()) return true;

    // Check for food collision and grow
    if (snake[0].x == food.x && snake[0].y == food.y) {
        snake.push_back(snake.back()); 
        spawnFood();
    }

    return false; 
}


void Game::changeDirection(int dir) {
    if ((direction + 2) % 4 != dir)
        direction = dir;
}

void Game::spawnFood() {
    food.x = rand() % width;
    food.y = rand() % height;
}

bool Game::checkCollision() {
    Segment head = snake[0];
    for (size_t i = 1; i < snake.size(); ++i)
        if (snake[i].x == head.x && snake[i].y == head.y)
            return true;
    return false;
}
