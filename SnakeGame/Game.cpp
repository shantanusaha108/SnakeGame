#include "Game.h"
#include <cstdlib>
#include <ctime>

Game::Game(int w, int h) : width(w), height(h), direction(1) {
    snake.push_back({ w / 2, h / 2 });
    srand(static_cast<unsigned>(time(0)));
    spawnFood();
}

//void Game::update() {
//    Segment newHead = snake[0];
//    if (direction == 0) newHead.y += 1;
//    else if (direction == 1) newHead.x += 1;
//    else if (direction == 2) newHead.y -= 1;
//    else if (direction == 3) newHead.x -= 1;
//
//    snake.insert(snake.begin(), newHead);
//
//    if (newHead.x == food.x && newHead.y == food.y)
//        spawnFood();
//    else
//        snake.pop_back();
//
//    checkCollision();
//}
void Game::update() {
    // Move the snake body
    for (int i = snake.size() - 1; i > 0; --i) {
        snake[i] = snake[i - 1];
    }

    // Move the head based on direction
    switch (direction) {
    case 0: snake[0].y -= 1; break; // up
    case 1: snake[0].x += 1; break; // right
    case 2: snake[0].y += 1; break; // down
    case 3: snake[0].x -= 1; break; // left
    }

    // SCREEN WRAPPING
    if (snake[0].x < 0) snake[0].x = width - 1;
    if (snake[0].x >= width) snake[0].x = 0;
    if (snake[0].y < 0) snake[0].y = height - 1;
    if (snake[0].y >= height) snake[0].y = 0;

    // Check for food collision
    if (snake[0].x == food.x && snake[0].y == food.y) {
        snake.push_back(snake.back()); // grow snake
        spawnFood();
    }

    // Optional: check self-collision here if desired
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
    if (head.x < 0 || head.y < 0 || head.x >= width || head.y >= height)
        return true;
    return false;
}
