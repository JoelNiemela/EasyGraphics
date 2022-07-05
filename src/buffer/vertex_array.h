#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "vertex_buffer.h"
#include "vertex_layout.h"

namespace EasyGraphics {

class VertexArray {
private:
	const GLuint id;
	// number of verticies in the VertexBuffer
	const GLuint count;
	VertexBuffer vb;
	const VertexLayout layout;
public:
	VertexArray(GLuint count, VertexLayout layout);
	VertexArray(const VertexArray &other) = delete;
	VertexArray(VertexArray &&other) noexcept;
	~VertexArray();

	static GLuint new_vertex_array();

	void bind() const;
	void unbind() const;

	bool insert(const void* data, GLsizeiptr size);
	void clear_buffer();

	inline GLuint get_count() const { return this->count; }
	inline const VertexBuffer& get_buffer() const { return this->vb; }
};

} // namespace EasyGraphics

#endif
