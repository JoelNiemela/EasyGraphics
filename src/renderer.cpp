#include "renderer.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "buffer/vertex_array.h"
#include "buffer/index_buffer.h"
#include "res/shader.h"

#include <iostream>
#include <stdexcept>

namespace EasyGraphics {

Renderer::Renderer() {
	this->initGL();
	this->initImGui();

	this->null_shader = std::make_unique<Shader>(*Shader::from_source(
		"#version 330 core\n"
		"in vec2 position;\n"
		"uniform mat4 mvp;\n"
		"void main() {\n"
		"    gl_Position = mvp * vec4(position, 0.0, 1.0);\n"
		"};",
		"#version 330 core\n"
		"out vec4 color;\n"
		"void main() {\n"
		"    color = vec4(1.0, 1.0, 1.0, 1.0);\n"
		"};"
	));

	unsigned char bytes[] = {
		0,     0,   0, 255,
		255,   0, 255, 255,
		255,   0, 255, 255,
		0,     0,   0, 255
	};
	this->null_texture = std::make_unique<Texture>(*Texture::from_bytes(bytes, 2, 2, GL_NEAREST, GL_NEAREST));

	this->null_material = std::make_unique<Material>(*this->null_shader, std::initializer_list<Uniform>{});
}

Renderer::~Renderer() {
	ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

	glfwTerminate();
}

bool Renderer::running() const {
	return !glfwWindowShouldClose(this->window);
}

void Renderer::draw(const DrawBuffer &buffer, const Material &material, std::initializer_list<Uniform> uniforms, GLsizei count) const {
	material.bind_with(uniforms);

	buffer.bind();

	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
};

void Renderer::draw(const StaticDrawBuffer &buffer, const Material &material, std::initializer_list<Uniform> uniforms) const {
	material.bind_with(uniforms);

	buffer.bind();

	glDrawElements(GL_TRIANGLES, buffer.draw_count(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::set_clear_color(float r, float g, float b, float a) const {
	glClearColor(r, g, b, a);
}

void Renderer::clear() const {
	glClear(GL_COLOR_BUFFER_BIT);
}

const Shader& Renderer::load_shader(const std::string &name, const std::string &vertex_path, const std::string &fragment_path) {
	this->shaders.try_emplace(name, vertex_path, fragment_path);

	return this->shaders.at(name);
}

const Shader& Renderer::shader(const std::string &name) const {
	if (this->shaders.contains(name)) {
		return this->shaders.at(name);
	} else {
		return *this->null_shader;
	}
}

const Texture& Renderer::load_texture(const std::string &name, const std::string &path) {
	this->textures.try_emplace(name, path);

	return this->textures.at(name);
}

const Texture& Renderer::texture(const std::string &name) const {
	if (this->textures.contains(name)) {
		return this->textures.at(name);
	} else {
		return *this->null_texture;
	}
}

const Material& Renderer::make_material(const std::string &name, const Shader &shader, std::initializer_list<Uniform> uniforms) {
	this->materials.try_emplace(name, shader, uniforms);

	return this->materials.at(name);
}

const Material& Renderer::make_material(const std::string &name, const Shader &shader, std::initializer_list<Uniform> uniforms, const Texture &texture) {
	this->materials.try_emplace(name, shader, uniforms, &texture);

	return this->materials.at(name);
}

const Material& Renderer::material(const std::string &name) const {
	if (this->materials.contains(name)) {
		return this->materials.at(name);
	} else {
		return *this->null_material;
	}
}

void Renderer::initGLFW() {
	if (!glfwInit()) {
		throw std::runtime_error("[Error] Failed to initialize GLFW");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(2250, 1373, "Grapher", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		throw std::runtime_error("[Error] Failed to create GLFW window]");
	}

	glfwMakeContextCurrent(window);
}

void Renderer::initGLEW() const {
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::string error_str((char*)glewGetErrorString(err)); 
		std::string msg = "[Error] Failed to initialize GLEW: \"" + error_str + "\"";

		glfwTerminate();

		throw std::runtime_error(msg);
	}
}

void Renderer::initGL() {
	this->initGLFW();
	this->initGLEW();

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(debugCallback, nullptr);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::initImGui() const {
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 430 core");

	ImGui::StyleColorsDark();
}

#ifdef WINDOWS
__stdcall
#endif
void debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, int length, const char *message, const void *userParam) {
	std::cerr << "[GL Error] " << message << std::endl;
}

} // namespace EasyGraphics
