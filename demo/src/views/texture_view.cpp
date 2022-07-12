#include "texture_view.h"

#include "buffer/quad_buffer.h"

#include "imgui/imgui.h"

TextureView::TextureView(const DemoApp &application) :
	EasyGraphics::View<DemoApp>(application),
	camera(0.0f, 0.0f, 0.0f),
	texture_material(application.material("texture"))
{
	this->buffer = std::make_unique<EasyGraphics::QuadBuffer>(
		application,
		EasyGraphics::VertexLayout{
			EasyGraphics::VertexLayout::element(GL_FLOAT, 2),
			EasyGraphics::VertexLayout::element(GL_FLOAT, 2)
		},
		1000
	);
}

TextureView::~TextureView() {}

void TextureView::update(double delta_time) {

}

void TextureView::render() {
	int width = 2250, height = 1373;

	glm::mat4 proj = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

	GLfloat size = 500.0f;
	GLfloat positions[] = {
		-size, -size, 0.0f, 0.0f,
		 size, -size, 1.0f, 0.0f,
		 size,  size, 1.0f, 1.0f,
		-size,  size, 0.0f, 1.0f
	};

	this->buffer->clear_buffer();

	this->application.use(*this->buffer);
	this->buffer->insert(positions, sizeof(positions));

	glm::mat4 model = glm::translate(glm::mat4(1.0f), -this->camera);
	glm::mat4 mvp = proj * view * model;

	this->application.renderer.draw(*this->buffer, this->texture_material, { EasyGraphics::Uniform("mvp", mvp) }, 6);
}

void TextureView::gui() {
	ImGui::SliderFloat2("camera", glm::value_ptr(this->camera), -2250.0f, 2250.0f);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

}
