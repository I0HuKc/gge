#include "Events.h"

#include <GLFW/glfw3.h>
#include <string.h>

#define _MOUSE_BUTTONS 1024

bool* Events::_keys;
unit* Events::_frames;
unit Events::_current = 0;

float Events::deltaX = 0.0f;
float Events::deltaY = 0.0f;
float Events::x = 0.0f;
float Events::y = 0.0f;

bool Events::_cursor_locked = false;
bool Events::_cursor_started = false;

// для курсора
void CursorPositionCallback(GLFWwindow* window, double Xpos, double Ypos) {
  if (Events::_cursor_started) {
    Events::deltaX += Xpos - Events::x;
    Events::deltaY += Ypos - Events::y;
  } else {
    Events::_cursor_started = true;
  }

  Events::x = Xpos;
  Events::y = Ypos;
}

// для кнопок мышки
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mode) {
  if (action == GLFW_PRESS) {
    Events::_keys[_MOUSE_BUTTONS + button] = true;
    Events::_frames[_MOUSE_BUTTONS + button] = Events::_current;
  } else if (action == GLFW_RELEASE) {
    Events::_keys[_MOUSE_BUTTONS + button] = false;
    Events::_frames[_MOUSE_BUTTONS + button] = Events::_current;
  }
}

// для клавы
void KeyCallback(GLFWwindow* window, int key, int scancode, int action,
                 int mode) {
  if (action == GLFW_PRESS) {
    Events::_keys[key] = true;
    Events::_frames[key] = Events::_current;
  } else if (action == GLFW_RELEASE) {
    Events::_keys[key] = false;
    Events::_frames[key] = Events::_current;
  }
}

int Events::initialize() {
  GLFWwindow* window = Window::window;
  _keys = new bool[1032];
  _frames = new unit[1032];

  // инициализирую массивы
  memset(_keys, false, 1032 * sizeof(bool));
  memset(_frames, 0, 1032 * sizeof(unit));

  // навешиваю колбэки рослушивания событий
  glfwSetKeyCallback(window, KeyCallback);  // клавиатура
  glfwSetMouseButtonCallback(window, MouseButtonCallback);   // мышка
  glfwSetCursorPosCallback(window, CursorPositionCallback);  // курсор

  return 0;
}

void Events::pollEvents() {
  // инкрементирую значение кадра
  _current++;
  // обновляю состояние
  deltaX = 0.0f;
  deltaY = 0.0f;

  glfwPollEvents();
}

bool Events::isPressed(int keycode) {
  // Проверяю корректность кода кнопки и что код кнопки не является кодом кнопки
  // мышки
  if (keycode < 0 || keycode >= _MOUSE_BUTTONS) {
    return false;
  }
  return _keys[keycode];
}

bool Events::justPressed(int keycode) {
  if (keycode < 0 || keycode >= _MOUSE_BUTTONS) {
    return false;
  }
  // сравниваю номер кадра записанного по этому коду кнопки и текущий кадр
  return _keys[keycode] && _frames[keycode] == _current;
}

bool Events::isClicked(int button) {
  int index = _MOUSE_BUTTONS + button;
  return _keys[index];
}

bool Events::justClicked(int button) {
  int index = _MOUSE_BUTTONS + button;
  return _keys[index] && _frames[index] == _current;
}
