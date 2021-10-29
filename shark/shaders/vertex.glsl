#version 330 core

layout (location = 0) in vec3 position;

uniform vec2 offset;

void main() {
    gl_Position = vec4(offset.x + position.x, offset.y + position.y, position.z, 1.0f);
};