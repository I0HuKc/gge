#include "Window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

GLFWwindow* Window::window;

// Инициализация окна
int Window::initialize(int width, int height, const char* title) {
  glfwInit();
  // Указываю параметры окна
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  // Создаю окно
  window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (window == nullptr) {
    std::cerr << "Ошибка создания GLFW окна." << std::endl;
    // Освобождение всех ресурсов
    glfwTerminate();
    return -1;
  }

  // Указываю текущий контекст
  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cerr << "Ошибка инициализации GLEW" << std::endl;
    return -1;
  }

  // Рендеринг
  glViewport(0, 0, width, height);
  return 0;
};

bool Window::isShouldClose() { return glfwWindowShouldClose(window); }

void Window::swapBuffers() { glfwSwapBuffers(window); }

void Window::setShouldClose(bool flag) {
  glfwSetWindowShouldClose(window, flag);
}

void Window::terminate() { glfwTerminate(); }