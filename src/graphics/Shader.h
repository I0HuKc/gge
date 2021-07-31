#ifndef GRAPHICS_SHADER_H
#define GRAPHICS_SHADER_H

#include <glm/glm.hpp>
#include <string>

class Shader {
 public:
  unsigned int id;
  Shader(unsigned int id);
  ~Shader();

  void use();
  // метод для отправки матрицы шейдеру
  void uniformMatrix(std::string name, glm::mat4 matrix);
};

// Метод загрузки шейдера
extern Shader* LoadShader(std::string vertexFile, std::string fragmentFile);

#endif