#version 330 core

in vec2 position;

uniform mat4 mvp;

void main() {
	gl_Position = mvp * vec4(position, 0.0, 1.0);
};
