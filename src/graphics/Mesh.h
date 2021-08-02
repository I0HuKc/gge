#ifndef GRAPHICS_MESH_H
#define GRAPHICS_MESH_H

#include <stdlib.h>

class Mesh {
  // объект вершинных массивов
  unsigned int vao;
  unsigned int vbo;

  size_t vertices;

 public:
  Mesh(const float* buffer, size_t vertices, const int* attrs);
  ~Mesh();

  void draw(unsigned int primitive);
};

#endif