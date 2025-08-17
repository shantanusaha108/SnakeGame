#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Game.h"
#include <iostream>

const int WIDTH = 20;
const int HEIGHT = 20;

float vertices[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f
};

unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

void processInput(GLFWwindow* window, Game& game) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) game.changeDirection(2); 
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) game.changeDirection(1); 
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) game.changeDirection(0); 
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) game.changeDirection(3); 
}

int main() {
    if (!glfwInit()) { std::cout << "GLFW init failed\n"; return -1; }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "Snake OpenGL", NULL, NULL);
    if (!window) { std::cout << "Failed to create GLFW window\n"; glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n"; return -1;
    }

    Shader shader("default.vert", "default.frag");

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Game game(WIDTH, HEIGHT);

    float lastTime = 0.0f;
    float timer = 0.0f;
    float updateRate = 0.3f;

    while (!glfwWindowShouldClose(window)) {
        float currentTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        timer += deltaTime;

        glfwPollEvents();
        processInput(window, game);

        if (timer >= updateRate) {
            bool collided = game.update();
            timer = 0.0f;
            if (collided) {
                std::cout << "Game Over! Snake collided with itself.\n";
                glfwSetWindowShouldClose(window, true);
            }
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(VAO);

        // Render snake
        shader.setFloat("ourColor_r", 0.0f);
        shader.setFloat("ourColor_g", 1.0f);
        shader.setFloat("ourColor_b", 0.0f);
        for (auto& seg : game.snake) {
            float xPos = (float)seg.x / WIDTH * 2.0f - 1.0f;
            float yPos = (float)seg.y / HEIGHT * 2.0f - 1.0f;
            float xScale = 1.0f / WIDTH * 2.0f;
            float yScale = 1.0f / HEIGHT * 2.0f;
            shader.setFloat("offset_x", xPos);
            shader.setFloat("offset_y", yPos);
            shader.setFloat("scale_x", xScale);
            shader.setFloat("scale_y", yScale);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        // Render food
        shader.setFloat("ourColor_r", 1.0f);
        shader.setFloat("ourColor_g", 0.0f);
        shader.setFloat("ourColor_b", 0.0f);
        float fx = (float)game.food.x / WIDTH * 2.0f - 1.0f;
        float fy = (float)game.food.y / HEIGHT * 2.0f - 1.0f;
        float fScaleX = 1.0f / WIDTH * 2.0f;
        float fScaleY = 1.0f / HEIGHT * 2.0f;
        shader.setFloat("offset_x", fx);
        shader.setFloat("offset_y", fy);
        shader.setFloat("scale_x", fScaleX);
        shader.setFloat("scale_y", fScaleY);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}
