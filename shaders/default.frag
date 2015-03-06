#version 330 core

uniform vec3 rgb;

out vec4 color;

void main() {
    color = vec4(rgb.xyz, 1.0f);
}
