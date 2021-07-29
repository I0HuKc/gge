#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLEW_STATIC

#include <iostream>

#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "loaders/PNGLoading.h"
#include "window/Events.h"
#include "window/Window.h"

int WIDTH = 1280;
int HEIGHT = 720;

float vertices[] = {
    // x    y     z     u     v
    -1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f, -1.0f, 0.0f,
    1.0f,  0.0f,  -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

    1.0f,  -1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 1.0f,  0.0f,
    1.0f,  1.0f,  -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
};

int main(int argc, char const* argv[]) {
  // инициализация окна
  Window::initialize(WIDTH, HEIGHT, "GGE Development");
  // инициализация системы Events
  Events::initialize();

  // загрузка шейдеров (тест)
  Shader* shader = LoadShader("res/main.glslv", "res/main.glslf");
  if (shader == nullptr) {
    std::cerr << "Неудалось загрузить шейдеры" << std::endl;
    Window::terminate();
    return 1;
  }

  // загрузка текстуры (тест)
  Texture* texture = LoadTexture("res/img.png");
  if (texture == nullptr) {
    std::cerr << "Ошибка загрузки текстуры" << std::endl;
    delete shader;
    Window::terminate();
    return 1;
  }

  // создаю объект вершинных массивов
  GLuint VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);  // создаю вершинный буффер

  glBindVertexArray(VAO);  // назначение вершинного массива
  glBindBuffer(GL_ARRAY_BUFFER, VBO);  // создание первого вершинного буффера
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // (index, длинна вершинного атрибута, тип данных, автоматическая
  // нормализация, длинна шака вершинных данных, сдвиг вершинного атрибутта)
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                        (GLvoid*)(0 * sizeof(GLfloat)));
  glEnableVertexAttribArray(0);  // включение вершинного атрибута

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                        (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);  // отвязываю объект

  glClearColor(0.6f, 0.62f, 0.65f, 1);

  // включаю смешивание для корректной прозрачности
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  while (!Window::isShouldClose()) {
    Events::pollEvents();
    if (Events::justPressed(GLFW_KEY_ESCAPE)) {
      Window::setShouldClose(true);
    }

    // тестирование обработки нажатия мышки
    if (Events::justClicked(GLFW_MOUSE_BUTTON_1)) {
      glClearColor(0.8f, 0.4f, 0.2f, 1);
    }

    glClear(GL_COLOR_BUFFER_BIT);

    // назначаю использование шейдера
    shader->use();
    // привязываю текстуру
    texture->bind();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    Window::swapBuffers();
  }

  // Освобождение всех ресурсов
  delete shader;
  delete texture;
  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);

  Window::terminate();
  return 0;
}
