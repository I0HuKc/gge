#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLEW_STATIC

#include <iostream>

#include "window/Events.h"
#include "window/Window.h"

int WIDTH = 1280;
int HEIGHT = 720;

int main(int argc, char const* argv[]) {
  // инициализация окна
  Window::initialize(WIDTH, HEIGHT, "GGE Development");
  // инициализация системы Events
  Events::initialize();

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

    Window::swapBuffers();
  }

  // Освобождение всех ресурсов
  Window::terminate();

  return 0;
}
