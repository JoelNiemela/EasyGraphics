#ifndef STATIC_DRAW_BUFFER_H
#define STATIC_DRAW_BUFFER_H

#include "draw_buffer.h"

namespace EasyGraphics {

class StaticDrawBuffer : public DrawBuffer {
public:
	using DrawBuffer::DrawBuffer;
	virtual ~StaticDrawBuffer();

	virtual GLuint draw_count() const = 0;
};

} // namespace EasyGraphics

#endif
