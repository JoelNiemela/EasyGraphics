#include "application.h"

#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace EasyGraphics {

Application::Application() : view(nullptr) {}

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
