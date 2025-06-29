
// glew.h must be included before glfw3.h
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string> 
#include <vector>
#include "src/triangle_mesh.h"

unsigned int make_module(const std::string &filePath, unsigned int moduleType);
unsigned int make_shader(const std::string& vertex_path, const std::string& fragment_path);
int main() {

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // ✅ Initialize GLEW Or GLad
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW init failed\n";
        return -1;
    }
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    unsigned int shader = make_shader(
        "../src/shaders/vertex.glsl",
        "../src/shaders/fragment.glsl"
    );

    TriangleMesh* triangle = new TriangleMesh();

    while (!glfwWindowShouldClose(window)) {
        // Render loop

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader);

        triangle->draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteShader(shader);
    glfwTerminate();
    return 0;
}

unsigned int make_shader(const std::string& vertex_path, const std::string& fragment_path) {
    std::vector<unsigned int> shader_modules;
    shader_modules.push_back(make_module(vertex_path, GL_VERTEX_SHADER));
    shader_modules.push_back(make_module(fragment_path, GL_FRAGMENT_SHADER));

    // create shader program
    unsigned int shader = glCreateProgram();
    for (auto& module : shader_modules) {
        glAttachShader(shader, module);
    }

    // and link it to the shader program
    glLinkProgram(shader);

    int status;
    glGetProgramiv(shader, GL_LINK_STATUS, &status);

    if (!status) {
        char errLog[1024];
        glGetProgramInfoLog(shader, 1024, NULL, errLog);
    }

    // after we compile and link them together we delete because we dont need them
    for (auto& module : shader_modules) {
        glDeleteShader(module);
    }

    return shader;
}

unsigned int make_module(const std::string &filePath, unsigned int moduleType) {
    std::ifstream file(filePath);
    std::stringstream shaderStringBuffer;
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error Shader file not loaded." << std::endl;
    }

    while (std::getline(file, line))
    {
        shaderStringBuffer << line << "\n";
    }

    // convert string stream into one string
    std::string shaderSource = shaderStringBuffer.str();

    // convert string int c_string 
    const char* shaderSrc = shaderSource.c_str();

    // clearing and closing file 
    shaderStringBuffer.str("");
    file.close();

    // create shader and compile it
    unsigned int shaderModule = glCreateShader(moduleType);
    glShaderSource(shaderModule, 1, &shaderSrc, NULL);
    glCompileShader(shaderModule);

    // verify if shader is compiled successfully
    int compile_status;
    glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &compile_status);

    if (!compile_status) {
        char errLog[1024];
        glGetShaderInfoLog(shaderModule, 1024, NULL, errLog);
        std::cerr << "Failed to compile shader \n" << errLog <<std::endl;
    }
    
    return shaderModule;
}