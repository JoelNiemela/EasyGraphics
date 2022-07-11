#include "buffer/quad_buffer.h"

#include "buffer/index_buffer.h"
#include "buffer/vertex_array.h"

#include <iostream>

namespace EasyGraphics {

QuadBuffer::QuadBuffer(VertexLayout layout, GLuint count) :
	StaticDrawBuffer(
			VertexArray(count * 4, layout),
			IndexBuffer::generate(IndexBuffer::QUADS, count)
	)
{
}

QuadBuffer::~QuadBuffer() {}

GLuint QuadBuffer::draw_count() const {
	GLuint vertex_count = this->get_vertex_array().get_used_count();

	if (vertex_count % 4 != 0) {
		std::cerr << "Error in QuadBuffer: Expected verticies to be multiple of 4." << std::endl;

		vertex_count -= vertex_count % 4;
	}

	return static_cast<GLuint>(vertex_count * 1.5);
}

} // namespace EasyGraphics
