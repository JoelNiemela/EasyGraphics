#include "buffer/vertex_array.h"

#include "application.h"

#include <memory>

namespace EasyGraphics {

VertexArray::VertexArray(const Application &application, GLuint count, const VertexLayout layout) :
	application(application),
	vb(VertexBuffer(application, nullptr, count * layout.get_stride())),
	id(new_vertex_array()),
	count(count),
	layout(layout)
{
	this->application.use(*this);

	const auto& elements = layout.get_elements();
	size_t offset = 0;
	for (size_t i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];

		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized,
				layout.get_stride(), (const void*)offset);
		offset += element.count * VertexLayout::Element::get_size_of_type(element.type);
	}
}

VertexArray::VertexArray(VertexArray &&other) noexcept : 
	application(other.application),
	vb(std::move(other.vb)),
	id(other.id),
	count(other.count),
	layout(other.layout)
{
	std::destroy_at(&other.id);
	std::construct_at(&other.id, 0);
}

VertexArray::~VertexArray() {
	this->application.disable_vertex_array();
	glDeleteVertexArrays(1, &this->id);
}

GLuint VertexArray::new_vertex_array() {
	GLuint id;
	glGenVertexArrays(1, &id);

	return id;
}

bool VertexArray::insert(const void *data, GLsizeiptr size) {
	return this->vb.insert(data, size);
}

void VertexArray::clear_buffer() {
	this->vb.clear();
}

GLuint VertexArray::get_used_count() const {
	return this->vb.get_offset() / this->layout.get_stride();
}

} // namespace EasyGraphics
