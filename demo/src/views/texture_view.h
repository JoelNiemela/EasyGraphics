#ifndef TEXTURE_VIEW_H
#define TEXTURE_VIEW_H

#include "demo_app.h"

#include "view.h"

#include <glm/glm.hpp>

#include "buffer/quad_buffer.h"

#include <memory>

class TextureView : public EasyGraphics::View<DemoApp> {
private:
	std::unique_ptr<EasyGraphics::QuadBuffer> buffer;
	glm::vec3 camera;

	const EasyGraphics::Material &texture_material;
public:
	TextureView(const DemoApp &application);
	~TextureView();

	void update(double delta_time) override;
	void render() override;
	void gui() override;
};

#endif
