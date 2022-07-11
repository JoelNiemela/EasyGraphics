#include "application.h"

#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace EasyGraphics {

Application::Application() : view(nullptr) {
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

Application::~Application() {}

void Application::run() {
	while (this->running()) {
		double current_time = glfwGetTime();

		this->delta_time = this->current_time - current_time;
		this->current_time = current_time;

		this->update();

		this->render();
	}
}

const Shader& Application::load_shader(const std::string &name, const std::string &vertex_path, const std::string &fragment_path) {
	this->shaders.try_emplace(name, vertex_path, fragment_path);

	return this->shaders.at(name);
}

const Shader& Application::shader(const std::string &name) const {
	if (this->shaders.contains(name)) {
		return this->shaders.at(name);
	} else {
		return *this->null_shader;
	}
}

const Texture& Application::load_texture(const std::string &name, const std::string &path) {
	this->textures.try_emplace(name, path);

	return this->textures.at(name);
}

const Texture& Application::texture(const std::string &name) const {
	if (this->textures.contains(name)) {
		return this->textures.at(name);
	} else {
		return *this->null_texture;
	}
}

const Material& Application::make_material(const std::string &name, const Shader &shader, std::initializer_list<Uniform> uniforms) {
	this->materials.try_emplace(name, shader, uniforms);

	return this->materials.at(name);
}

const Material& Application::make_material(const std::string &name, const Shader &shader, std::initializer_list<Uniform> uniforms, const Texture &texture) {
	this->materials.try_emplace(name, shader, uniforms, &texture);

	return this->materials.at(name);
}

const Material& Application::material(const std::string &name) const {
	if (this->materials.contains(name)) {
		return this->materials.at(name);
	} else {
		return *this->null_material;
	}
}

void Application::update() {}

void Application::render() {
	this->renderer.clear();

	if (this->view) this->view->render();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	if (this->view) this->view->gui();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(this->renderer.get_window());
	glfwPollEvents();
}

bool Application::running() const {
	return this->renderer.running();
}

} // namespace EasyGraphics
