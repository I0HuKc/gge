#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLEW_STATIC

#include <iostream>

int WIDTH = 1280;
int HEIGHT = 720;

int main(int argc, char const* argv[]) {
  glfwInit();
  // Указываю параметры окна
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  // Создаю окно
  GLFWwindow* window =
      glfwCreateWindow(WIDTH, HEIGHT, "GGE Development", nullptr, nullptr);
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
  glViewport(0, 0, WIDTH, HEIGHT);

  while (!glfwWindowShouldClose(window)) {
    // Подключаю все события
    glfwPollEvents();
    // Вызов смены буффера
    glfwSwapBuffers(window);
  }

  // Освобождение всех ресурсов
  glfwTerminate();

  return 0;
}
