#ifndef DRAW_BUFFER_H
#define DRAW_BUFFER_H

#include "vertex_array.h"
#include "index_buffer.h"

#include <memory>

namespace EasyGraphics {

class DrawBuffer {
private:
	VertexArray va;
	IndexBuffer ib;
protected:
	const Application &application;
public:
	DrawBuffer(const Application &application, VertexArray &&va, IndexBuffer &&ib);
	virtual ~DrawBuffer();

	void bind() const;
	void unbind() const;

	bool insert(const void* data, GLsizeiptr size);
	void clear_buffer();

	inline const VertexArray& get_vertex_array() const { return this->va; }
	inline const IndexBuffer& get_index_buffer() const { return this->ib; }
};

} // namespace EasyGraphics

#endif
