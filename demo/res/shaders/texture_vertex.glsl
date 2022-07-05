#version 330 core

in vec2 position;
in vec2 tex_coord;

out vec2 v_tex_coord;

uniform mat4 mvp;

void main() {
	gl_Position = mvp * vec4(position, 0.0, 1.0);
	v_tex_coord = tex_coord;
};
