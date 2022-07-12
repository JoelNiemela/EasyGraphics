#include "buffer/draw_buffer.h"

#include "application.h"

namespace EasyGraphics {

DrawBuffer::DrawBuffer(const Application &application, VertexArray &&va, IndexBuffer &&ib) :
	va(std::move(va)),
	ib(std::move(ib)),
	application(application)
{
}

DrawBuffer::~DrawBuffer() {}

void DrawBuffer::bind() const {
	this->application.use(*this);
}

void DrawBuffer::unbind() const {
	this->application.disable_draw_buffer();
}

bool DrawBuffer::insert(const void* data, GLsizeiptr size) {
	return this->va.insert(data, size);
}

void DrawBuffer::clear_buffer() {
	this->va.clear_buffer();
}

} // namespace EasyGraphics
