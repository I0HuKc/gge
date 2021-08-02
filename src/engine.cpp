#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLEW_STATIC

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

#include "graphics/Mesh.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "loaders/PNGLoading.h"
#include "window/Camera.h"
#include "window/Events.h"
#include "window/Window.h"

int WIDTH = 1280;
int HEIGHT = 720;

float vertices[] = {
    -1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f, -1.0f, 0.0f,
    1.0f,  0.0f,  -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

    1.0f,  -1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 1.0f,  0.0f,
    1.0f,  1.0f,  -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
};

int attrs[] = {3, 2, 0};

int main(int argc, char const* argv[]) {
  // инициализация окна
  Window::initialize(WIDTH, HEIGHT, "GGE Development");
  // инициализация системы Events
  Events::initialize();

  // загрузка шейдеров (тест)
  Shader* shader = LoadShader("res/main.glslv", "res/main.glslf");
  if (shader == nullptr) {
    std::cerr << "Неудалось загрузить шейдеры" << std::endl;
    Window::terminate();
    return 1;
  }

  // загрузка текстуры (тест)
  Texture* texture = LoadTexture("res/img.png");
  if (texture == nullptr) {
    std::cerr << "Ошибка загрузки текстуры" << std::endl;
    delete shader;
    Window::terminate();
    return 1;
  }

  // создаю объекты вершинных массивов
  Mesh* mesh = new Mesh(vertices, 6, attrs);

  glClearColor(0.6f, 0.62f, 0.65f, 1);

  // включаю смешивание для корректной прозрачности
  // glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  // glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // создаю камеру
  Camera* camera = new Camera(glm::vec3(0, 0, 1), glm::radians(90.0f));

  glm::mat4 model(1.0f);
  model = glm::translate(model, glm::vec3(0.5f, 0, 0));

  // дельта времени (время прошедшее с предыдущего кадра)
  float lastTime = glfwGetTime();
  float delta = 0.0f;

  float camX = 0.0f;
  float camY = 0.0f;

  while (!Window::isShouldClose()) {
    // стабилизация FPS
    float currentTime = glfwGetTime();
    delta = currentTime - lastTime;
    lastTime = currentTime;

    if (Events::justPressed(GLFW_KEY_ESCAPE)) {
      Window::setShouldClose(true);
    }

    if (Events::justPressed(GLFW_KEY_TAB)) {
      Events::toogleCursor();
    }

    // управление камерой с клавиатуры
    if (Events::isPressed(GLFW_KEY_W)) {
      camera->position += camera->front * delta * 20.0f;
    }
    if (Events::isPressed(GLFW_KEY_S)) {
      camera->position -= camera->front * delta * 20.0f;
    }
    if (Events::isPressed(GLFW_KEY_D)) {
      camera->position += camera->right * delta * 3.0f;
    }
    if (Events::isPressed(GLFW_KEY_A)) {
      camera->position -= camera->right * delta * 3.0f;
    }

    if (Events::_cursor_locked) {
      camY += -Events::deltaY / Window::height * 2;
      camX += -Events::deltaX / Window::height * 2;

      if (camY < -glm::radians(89.0f)) {
        camY = -glm::radians(89.0f);
      }
      if (camY > glm::radians(89.0f)) {
        camY = glm::radians(89.0f);
      }

      camera->rotation = glm::mat4(1.0f);
      camera->rotate(camY, camX, 0);
    }

    glClear(GL_COLOR_BUFFER_BIT);

    // назначаю использование шейдера
    shader->use();
    // передача матрицы в шейдер
    shader->uniformMatrix("model", model);
    // передача в шейдер projview
    shader->uniformMatrix("projview",
                          camera->getProjection() * camera->getView());
    // привязываю текстуру
    texture->bind();

    mesh->draw(GL_TRIANGLES);

    Window::swapBuffers();
    Events::pollEvents();
  }

  // Освобождение всех ресурсов
  delete shader;
  delete texture;
  delete mesh;

  Window::terminate();
  return 0;
}
