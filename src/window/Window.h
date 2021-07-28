#ifndef WINDOW_WINDOW_H
#define WINDOW_WINDOW_H

class GLFWwindow;

class Window {
 public:
  static GLFWwindow* window;

  static int initialize(int width, int height, const char* title);
  static void terminate();

  // Прослушивание события закрытия окна
  static bool isShouldClose();

  // Вызов смены буффера
  static void swapBuffers();

  // Закрыть окно
  static void setShouldClose(bool flag);
};

#endif