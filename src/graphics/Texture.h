#ifndef GRAPHICS_TEXTURE_H
#define GRAPHICS_TEXTURE_H

#include <string>

class Texture {
 public:
  unsigned int id;
  int width;
  int height;
  Texture(unsigned int id, int width, int height);
  ~Texture();

  void bind();
};

// Метод загрузки текстуры
extern Texture* LoadTexture(std::string filename);

#endif
