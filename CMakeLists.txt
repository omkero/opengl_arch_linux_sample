cmake_minimum_required(VERSION 3.10)

# Suppress OpenGL policy warning
cmake_policy(SET CMP0072 NEW)

project(OpenGLProject CXX)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

add_executable(OpenGLProject
    main.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle_mesh.cpp
)

target_include_directories(OpenGLProject PRIVATE
    ${OPENGL_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}  # Include directory where glad.h is

)

target_link_libraries(OpenGLProject
    OpenGL::GL
    GLEW::GLEW
    glfw
)
