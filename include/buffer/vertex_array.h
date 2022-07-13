#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "vertex_buffer.h"
#include "vertex_layout.h"

namespace EasyGraphics {

class VertexArray {
private:
	const Application &application;
	VertexBuffer vb;
public:
	const GLuint id;
	// number of verticies in the VertexBuffer
	const GLuint count;
	const VertexLayout layout;
public:
	VertexArray(const Application &application, GLuint count, VertexLayout layout);
	VertexArray(const VertexArray &other) = delete;
	VertexArray(VertexArray &&other) noexcept;
	~VertexArray();

	[[nodiscard]]
	static GLuint new_vertex_array();

	bool insert(const void* data, GLsizeiptr size);
	void clear_buffer();

	GLuint get_used_count() const;
	inline const VertexBuffer& get_buffer() const { return this->vb; }
};

} // namespace EasyGraphics

#endif
