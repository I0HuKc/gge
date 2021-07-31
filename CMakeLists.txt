cmake_minimum_required(VERSION 3.0)
project(gge VERSION 1.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

include (FindPkgConfig)
if (NOT PKG_CONFIG_FOUND)
    message (FATAL_ERROR "pkg-config не найден!")
endif ()

find_package(PkgConfig REQUIRED)
find_package(PNG REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(GL REQUIRED glew)

include_directories(${PNG_INCLUDE_DIR})
include_directories(${GLFW_INCLUDE_DIRS})

file(GLOB
        CPPS 
        "src/*.cpp" 
        "src/window/*.cpp"
        "src/graphics/*.cpp"
        "src/loaders/*.cpp"
    )

add_executable(
    ${PROJECT_NAME} src/engine.cpp 
    ${CPPS}
)

target_link_libraries(${PROJECT_NAME} ${GLFW_STATIC_LIBRARIES} ${GL_STATIC_LIBRARIES} ${PNG_LIBRARY})