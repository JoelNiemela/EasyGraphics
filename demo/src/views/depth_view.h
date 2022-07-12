#ifndef DEPTH_VIEW_H
#define DEPTH_VIEW_H

#include "demo_app.h"

#include "view.h"

#include "buffer/quad_buffer.h"

#include <glm/glm.hpp>

#include <memory>

class DepthView : public EasyGraphics::View<DemoApp> {
private:
	std::unique_ptr<EasyGraphics::QuadBuffer> buffer;
	glm::vec3 camera;
	glm::vec3 translation1;
	glm::vec3 translation2;

	const EasyGraphics::Material &material1;
	const EasyGraphics::Material &material2;
public:
	DepthView(const DemoApp &application);
	~DepthView();

	void update(double delta_time) override;
	void render() override;
	void gui() override;
};

#endif
