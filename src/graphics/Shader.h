#ifndef GRAPHICS_SHADER_H
#define GRAPHICS_SHADER_H

#include <string>

class Shader {
 public:
  unsigned int id;
  Shader(unsigned int id);
  ~Shader();

  void use();
};

// Метод загрузки шейдера
extern Shader* LoadShader(std::string vertexFile, std::string fragmentFile);

#endif