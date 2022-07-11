#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <unordered_map>
#include <string>
#include <initializer_list>
#include <memory>

#include "buffer/draw_buffer.h"
#include "buffer/static_draw_buffer.h"
#include "res/material.h"

namespace EasyGraphics {

class VertexArray;
class IndexBuffer;
class Shader;
class Texture;

class Renderer {
	GLFWwindow* window;
public:
	Renderer();
	~Renderer();

	bool running() const;

	void draw(const DrawBuffer &buffer, const Material &material, std::initializer_list<Uniform> uniforms, GLsizei count) const;
	void draw(const StaticDrawBuffer &buffer, const Material &material, std::initializer_list<Uniform> uniforms) const;

	void set_clear_color(float r, float g, float b, float a) const;
	void clear() const;

	inline GLFWwindow* get_window() const { return this->window; }
private:
	void initGLFW();
	void initGLEW() const;
	void initGL();
	void initImGui() const;
};

#ifdef WINDOWS
__stdcall
#endif
void debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, int length, const char *message, const void *userParam);

} // namespace EasyGraphics

#endif
