#version 330 core

// fragment.glsl

in vec3 fragmentColor;

out vec4 screenColor;

void main() {
    screenColor = vec4(fragmentColor, 1.0);
}