#include "Shader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(unsigned int id) : id(id) {}

Shader::~Shader() { glDeleteProgram(id); }

void Shader::use() { glUseProgram(id); }

Shader* LoadShader(std::string vertexFile, std::string fragmentFile) {
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  vShaderFile.exceptions(std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::badbit);

  try {
    // Открываю преданные файлы шейдера
    vShaderFile.open(vertexFile);
    fShaderFile.open(fragmentFile);
    std::stringstream vShaderStream, fShaderStream;

    // Записываю данные из переданного файла шейдера
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    // Закрываю открытый файл шейдера
    vShaderFile.close();
    fShaderFile.close();

    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();

  } catch (std::ifstream::failure& e) {
    std::cerr << "ОШИБКА: файл шейдера не удалось прочитать" << std::endl;
    return nullptr;
  }

  const GLchar* vShaderCode = vertexCode.c_str();
  const GLchar* fShaderCode = fragmentCode.c_str();

  /* Компилирование шейдеров */

  GLuint vertex, fragment;
  GLint success;
  GLchar infoLog[512];

  // Создание вершинного шейдера
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, nullptr);
  glCompileShader(vertex);

  // Проверка статуса загрузки шейдера
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
    std::cerr << "Ошибка компиляции вершинного шейдера" << std::endl;
    std::cerr << infoLog << std::endl;
    return nullptr;
  }

  // Создание фрагментного шейдера
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, nullptr);
  glCompileShader(fragment);

  // Проверка статуса загрузки шейдера
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
    std::cerr << "SHADER::FRAGMENT: compilation failed" << std::endl;
    std::cerr << infoLog << std::endl;
    return nullptr;
  }

  // Создание шейдерной программы
  GLuint id = glCreateProgram();
  // Прикрепляю оба шейдера
  glAttachShader(id, vertex);
  glAttachShader(id, fragment);
  // Линкую шейдеры
  glLinkProgram(id);

  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(id, 512, nullptr, infoLog);
    std::cerr << "Ошибка линковки шейдера" << std::endl;
    std::cerr << infoLog << std::endl;

    // Удаляю шейдеры
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return nullptr;
  }

  // Удаляю шейдеры
  glDeleteShader(vertex);
  glDeleteShader(fragment);

  return new Shader(id);
}