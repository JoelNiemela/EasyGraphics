#include "depth_view.h"

#include "buffer/quad_buffer.h"

#include "imgui/imgui.h"

#include <glm/fwd.hpp>
#include <memory>

DepthView::DepthView(const DemoApp &application) :
	EasyGraphics::View<DemoApp>(application),
	camera(0.0f, 0.0f, 0.0f),
	translation1(500.0f, 500.0f, 0.0f),
	translation2(550.0f, 550.0f, 0.0f),
	material1(application.material("depth1")),
	material2(application.material("depth2"))
{
	// make a 1000 element buffer of quads to render with
	this->buffer = std::make_unique<EasyGraphics::QuadBuffer>(
		application,
		EasyGraphics::VertexLayout{ // each element in the buffer contains 2 floats
			EasyGraphics::VertexLayout::element(GL_FLOAT, 3)
		},
		1000
	);
}

DepthView::~DepthView() {}

void DepthView::update(double delta_time) {

}

void DepthView::render() {
	int width = 2250, height = 1373;

	glm::mat4 proj = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -10.0f, 10.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
	glm::mat4 model = glm::translate(glm::mat4(1.0f), -this->camera);
	glm::mat4 mvp = proj * view * model;

	struct Quad {
		struct Vertex {
			 GLfloat x, y, z;
		} verticies[4];
	} positions1[] = {
		{{
			{-50.0f + this->translation1.x, -50.0f + this->translation1.y, this->translation1.z},
			{ 50.0f + this->translation1.x, -50.0f + this->translation1.y, this->translation1.z},
			{ 50.0f + this->translation1.x,  50.0f + this->translation1.y, this->translation1.z},
			{-50.0f + this->translation1.x,  50.0f + this->translation1.y, this->translation1.z},
		}},
	};

	this->buffer->clear_buffer();

	this->buffer->insert(positions1, sizeof(positions1));

	this->application.draw(*this->buffer, this->material1, { EasyGraphics::Uniform("mvp", mvp) });

	Quad positions2[] = {
		{{
			{-50.0f + this->translation2.x, -50.0f + this->translation2.y, this->translation2.z},
			{ 50.0f + this->translation2.x, -50.0f + this->translation2.y, this->translation2.z},
			{ 50.0f + this->translation2.x,  50.0f + this->translation2.y, this->translation2.z},
			{-50.0f + this->translation2.x,  50.0f + this->translation2.y, this->translation2.z},
		}}
	};

	this->buffer->clear_buffer();

	this->buffer->insert(positions2, sizeof(positions2));

	this->application.draw(*this->buffer, this->material2, { EasyGraphics::Uniform("mvp", mvp) });
}

void DepthView::gui() {
	ImGui::SliderFloat2("camera", glm::value_ptr(this->camera), -2250.0f, 2250.0f);
	ImGui::SliderFloat2("pos 1", glm::value_ptr(this->translation1), 0.0f, 2250.0f);
	ImGui::SliderFloat("depth 1", &this->translation1.z, -10.0f, 10.0f);
	ImGui::SliderFloat2("pos 2", glm::value_ptr(this->translation2), 0.0f, 2250.0f);
	ImGui::SliderFloat("depth 2", &this->translation2.z, -10.0f, 10.0f);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
