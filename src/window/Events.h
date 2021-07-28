#ifndef WINDOW_EVENTS_H
#define WINDOW_EVENTS_H

#include "Window.h"

typedef unsigned int unit;

class Events {
 public:
  // массив клавиш/кнопок
  static bool* _keys;
  // массив содержащий номера кадров
  static unit* _frames;
  // текущий кадр
  static unit _current;

  // дельта перевижения курсора
  static float deltaX;
  static float deltaY;

  // координаты курсора
  static float x;
  static float y;

  // для определения дельты мышки
  static bool _cursor_locked;  // для управления состоянием мышки (чтобы она не
                               // выходила за пределы экрана или заблокирована в
                               // одном месте)
  static bool _cursor_started;

  static int initialize();

  // Подключение всех обрабатываемых событий
  static void pollEvents();

  // нажата ли клавиша
  static bool isPressed(int keycode);

  // нажата ли клавиша только что
  static bool justPressed(int keycode);

  // зажата ли кнопка МЫШКИ
  static bool isClicked(int button);

  // зажата ли кнопка МЫШКИ только-что
  static bool justClicked(int button);
};

#endif