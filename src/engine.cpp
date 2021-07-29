#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLEW_STATIC

#include <iostream>

#include "graphics/Shader.h"
#include "window/Events.h"
#include "window/Window.h"

int WIDTH = 1280;
int HEIGHT = 720;

float vertices[] = {
    0.0f, 0.0f, 0.0f,

    1.0f, 0.0f, 0.0f,

    0.0f, 1.0f, 0.0f,
};

int main(int argc, char const* argv[]) {
  // инициализация окна
  Window::initialize(WIDTH, HEIGHT, "GGE Development");
  // инициализация системы Events
  Events::initialize();

  Shader* shader = LoadShader("res/main.glslv", "res/main.glslf");
  if (shader == nullptr) {
    std::cerr << "Неудалось загрузить шейдеры" << std::endl;
    Window::terminate();
    return -1;
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
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (GLvoid*)(0 * sizeof(GLfloat)));

  glEnableVertexAttribArray(0);  // включение вершинного атрибута
  glBindVertexArray(0);  // отвязываю объект

  glClearColor(0.207f, 0.59f, 0.99f, 1);

  while (!Window::isShouldClose()) {
    Events::pollEvents();
    if (Events::justPressed(GLFW_KEY_ESCAPE)) {
      Window::setShouldClose(true);
    }

    // тестирование обработки нажатия мышки
    if (Events::justClicked(GLFW_MOUSE_BUTTON_1)) {
      glClearColor(0.100f, 0.43f, 0.100f, 1);
    }

    glClear(GL_COLOR_BUFFER_BIT);

    // назначаю использование шейдера
    shader->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    Window::swapBuffers();
  }

  // Освобождение всех ресурсов
  Window::terminate();

  return 0;
}
