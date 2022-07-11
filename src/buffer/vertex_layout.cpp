#include "buffer/vertex_layout.h"

#include <cassert>
#include <iostream>
#include <numeric>

namespace EasyGraphics {

GLuint VertexLayout::Element::get_size_of_type(GLuint type) {
	switch (type) {
		case GL_FLOAT: return sizeof(GLfloat);
		case GL_UNSIGNED_INT: return sizeof(GLuint);
		case GL_UNSIGNED_BYTE: return sizeof(GLbyte);
		default:
			std::cerr << "Error in LayoutElement::get_size_of_type: unsupported GL type (" << type << ")" << std::endl;
			assert(false);
	}
}

GLuint VertexLayout::Element::size(Element element) {
	return element.count * Element::get_size_of_type(element.type);
}

VertexLayout::VertexLayout(std::initializer_list<Element> elements) :
	elements(elements),
	stride(std::accumulate(elements.begin(), elements.end(), 0, [](int sum, const Element& e) { return sum + Element::size(e); }))
{

}

VertexLayout::Element VertexLayout::element(GLuint type, GLuint count) {
	GLboolean normalized;

	switch (type) {
		case GL_FLOAT:
		case GL_UNSIGNED_INT:
			normalized = GL_FALSE;
			break;
		case GL_UNSIGNED_BYTE:
			normalized = GL_TRUE;
			break;
		default:
			std::cerr << "Error in VertexBufferLayout::push: unsupported GL type (" << type << ")" << std::endl;
			assert(false);
	}

	return Element{type, count, normalized};
}

} // namespace EasyGraphics
