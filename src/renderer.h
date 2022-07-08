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

	std::unordered_map<std::string, Shader> shaders;
	std::unordered_map<std::string, Texture> textures;
	std::unordered_map<std::string, Material> materials;

	std::unique_ptr<Shader> null_shader;
	std::unique_ptr<Texture> null_texture;
	std::unique_ptr<Material> null_material;
public:
	Renderer();
	~Renderer();

	bool running() const;

	void draw(const DrawBuffer &buffer, const Material &material, std::initializer_list<Uniform> uniforms, GLsizei count) const;
	void draw(const StaticDrawBuffer &buffer, const Material &material, std::initializer_list<Uniform> uniforms) const;

	void set_clear_color(float r, float g, float b, float a) const;
	void clear() const;

	const Shader& load_shader(const std::string &name, const std::string &vertex_path, const std::string &fragment_path);
	const Shader& shader(const std::string &name) const;

	const Texture& load_texture(const std::string &name, const std::string &path);
	const Texture& texture(const std::string &name) const;

	const Material& make_material(const std::string &name, const Shader &shader, std::initializer_list<Uniform> uniforms);
	const Material& make_material(const std::string &name, const Shader &shader, std::initializer_list<Uniform> uniforms, const Texture &texture);
	const Material& material(const std::string &name) const;

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
