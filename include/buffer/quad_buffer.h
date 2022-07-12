#ifndef QUAD_BUFFER_H
#define QUAD_BUFFER_H

#include "static_draw_buffer.h"
#include "vertex_layout.h"

namespace EasyGraphics {

class QuadBuffer : public StaticDrawBuffer {
public:
	QuadBuffer(const Application &application, VertexLayout layout, GLuint count);
	~QuadBuffer();

	GLuint draw_count() const override;
};

} // namespace EasyGraphics

#endif
