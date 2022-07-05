#ifndef VERTEX_LAYOUT_H
#define VERTEX_LAYOUT_H

#include <GL/glew.h>

#include <vector>

namespace EasyGraphics {

class VertexLayout {
public:
	struct Element {
		const GLuint type;
		const GLuint count;
		const GLboolean normalized;

		static GLuint get_size_of_type(GLuint type);
		static GLuint size(Element element);
	};

	std::vector<Element> elements;
	GLuint stride;

public:
	VertexLayout() : stride(0) {}
	VertexLayout(std::initializer_list<Element> elements);

	static Element element(GLuint type, GLuint count);

	inline const std::vector<Element>& get_elements() const { return this->elements; }
	inline GLuint get_stride() const { return this->stride; }
};

} // namespace EasyGraphics

#endif
