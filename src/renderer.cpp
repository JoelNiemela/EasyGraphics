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

void Renderer::set_clear_color(float r, float g, float b, float a) const {
	glClearColor(r, g, b, a);
}

void Renderer::clear() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0);
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
