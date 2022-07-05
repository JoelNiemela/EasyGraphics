#include "draw_buffer.h"

namespace EasyGraphics {

DrawBuffer::DrawBuffer(VertexArray &&va, IndexBuffer &&ib) :
	va(std::move(va)),
	ib(std::move(ib))
{
}

DrawBuffer::~DrawBuffer() {}

void DrawBuffer::bind() const {
	this->va.bind();
	this->ib.bind();
}

void DrawBuffer::unbind() const {
	this->va.unbind();
	this->ib.unbind();
}

bool DrawBuffer::insert(const void* data, GLsizeiptr size) {
	return this->va.insert(data, size);
}

void DrawBuffer::clear_buffer() {
	this->va.clear_buffer();
}

} // namespace EasyGraphics
