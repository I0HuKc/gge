#ifndef WINDOW_CAMERA_H
#define WINDOW_CAMERA_H

#include <glm/glm.hpp>

class Camera {
  void updateVectors();

 public:
  // векторы направления камеры
  glm::vec3 front;
  glm::vec3 up;
  glm::vec3 right;

  glm::vec3 position;
  float fov;
  glm::mat4 rotation;
  Camera(glm::vec3 position, float fov);

  // метод вращения векторов в обратном порядке
  void rotate(float x, float y, float z);

  // получить матрицу проекции
  glm::mat4 getProjection();
  // получить матрицу вида
  glm::mat4 getView();
};

#endif
