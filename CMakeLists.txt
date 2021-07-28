cmake_minimum_required(VERSION 3.0)
project(gge VERSION 1.0)

find_package(PkgConfig REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(GL REQUIRED glew)

include_directories(${GLFW_INCLUDE_DIRS})

file(GLOB
        CPPS "src/*.cpp")

add_executable(
    ${PROJECT_NAME} src/engine.cpp 
    ${CPPS}
)

target_link_libraries(${PROJECT_NAME} ${GLFW_STATIC_LIBRARIES} ${GL_STATIC_LIBRARIES})