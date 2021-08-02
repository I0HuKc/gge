#ifndef WINDOW_CAMERA_H
#define WINDOW_CAMERA_H

#include <glm/glm.hpp>
using namespace glm;

class Camera {
  void updateVectors();

 public:
  // векторы направления камеры
  vec3 front;
  vec3 up;
  vec3 right;

  vec3 position;
  float fov;
  mat4 rotation;
  Camera(vec3 position, float fov);

  // метод вращения векторов в обратном порядке
  void rotate(float x, float y, float z);

  // получить матрицу проекции
  mat4 getProjection();
  // получить матрицу вида
  mat4 getView();
};

#endif
