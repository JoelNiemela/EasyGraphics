#ifndef TEXTURE_VIEW_H
#define TEXTURE_VIEW_H

#include "view.h"

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "buffer/quad_buffer.h"
#include "res/shader.h"
#include "res/texture.h"
#include "renderer.h"

#include <memory>

class TextureView : public EasyGraphics::View {
private:
	std::unique_ptr<EasyGraphics::DrawBuffer> buffer;
	glm::vec3 camera;

	const EasyGraphics::Material &texture_material;
public:
	TextureView(const EasyGraphics::Renderer &renderer);
	~TextureView();

	void update(double delta_time) override;
	void render() override;
	void gui() override;
};

#endif
