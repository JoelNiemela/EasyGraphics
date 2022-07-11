#include "demo_view.h"

#include "buffer/quad_buffer.h"

#include "imgui/imgui.h"

#include <glm/fwd.hpp>
#include <memory>

DemoView::DemoView(const DemoApp &application) :
	EasyGraphics::View<DemoApp>(application),
	camera(0.0f, 0.0f, 0.0f),
	translation1(0.0f, 0.0f, 0.0f),
	translation2(0.0f, 0.0f, 0.0f),
	basic_material(application.material("basic")) // reqeust the material "basic" from the application
{
	// make a 1000 element buffer of quads to render with
	this->buffer = std::make_unique<EasyGraphics::QuadBuffer>(
		EasyGraphics::VertexLayout{ // each element in the buffer contains 2 floats
			EasyGraphics::VertexLayout::element(GL_FLOAT, 2)
		},
		1000
	);
}

DemoView::~DemoView() {}

void DemoView::update(double delta_time) {

}

void DemoView::render() {
	int width = 2250, height = 1373;

	glm::mat4 proj = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

	struct Quad {
		struct Vertex {
			 GLfloat x, y;
		} verticies[4];
	} positions[] = {
		{{
			{-50.0f + this->translation1.x, -50.0f + this->translation1.y},
			{ 50.0f + this->translation1.x, -50.0f + this->translation1.y},
			{ 50.0f + this->translation1.x,  50.0f + this->translation1.y},
			{-50.0f + this->translation1.x,  50.0f + this->translation1.y},
		}},

		{{
			{ 50.0f + this->translation2.x,  50.0f + this->translation2.y},
			{150.0f + this->translation2.x,  50.0f + this->translation2.y},
			{150.0f + this->translation2.x, 150.0f + this->translation2.y},
			{ 50.0f + this->translation2.x, 150.0f + this->translation2.y},
		}}
	};

	this->buffer->clear_buffer();

	this->buffer->bind();
	this->buffer->insert(positions, sizeof(positions));

	glm::mat4 model = glm::translate(glm::mat4(1.0f), -this->camera);
	glm::mat4 mvp = proj * view * model;

	this->application.renderer.draw(*this->buffer, this->basic_material, { EasyGraphics::Uniform("mvp", mvp) });
}

void DemoView::gui() {
	ImGui::SliderFloat2("camera", glm::value_ptr(this->camera), -2250.0f, 2250.0f);
	ImGui::SliderFloat2("1", glm::value_ptr(this->translation1), 0.0f, 2250.0f);
	ImGui::SliderFloat2("2", glm::value_ptr(this->translation2), 0.0f, 2250.0f);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
