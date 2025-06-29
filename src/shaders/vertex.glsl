#version 330 core

// vertext.glsl

in vec2 vertexPos;
in vec3 vertexColor;

out vec3 fragmentColor;

void main() {
    gl_Position = vec4(vertexPos, 0.0,1.0);
    fragmentColor = vertexColor;
}
