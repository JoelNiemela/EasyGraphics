#version 330 core

out vec4 color;

in vec2 v_tex_coord;

uniform sampler2D u_texture;

void main() {
	color = texture(u_texture, v_tex_coord);
};
