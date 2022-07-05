#ifndef TEST_VIEW_H
#define TEST_VIEW_H

#include "view.h"

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "buffer/quad_buffer.h"
#include "res/shader.h"
#include "res/material.h"
#include "renderer.h"

#include <memory>

class DemoView : public EasyGraphics::View {
private:
	std::unique_ptr<EasyGraphics::StaticDrawBuffer> buffer;
	glm::vec3 camera;
	glm::vec3 translation1;
	glm::vec3 translation2;

	const EasyGraphics::Material &basic_material;
public:
	DemoView(const EasyGraphics::Renderer &renderer);
	~DemoView();

	void update(double delta_time) override;
	void render() override;
	void gui() override;
};

#endif