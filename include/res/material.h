#ifndef MATERIAL_H
#define MATERIAL_H

#include "shader.h"
#include "texture.h"

#include <string>
#include <vector>
#include <variant>
#include <initializer_list>

namespace EasyGraphics {

struct Uniform {
	const std::string name;
	std::variant<GLint, GLfloat, glm::vec3, glm::vec4, glm::mat4> data;

	Uniform(const std::string &name, GLint i) : name(name), data(i) {}
	Uniform(const std::string &name, GLfloat f) : name(name), data(f) {}
	Uniform(const std::string &name, glm::vec3 v3) : name(name), data(v3) {}
	Uniform(const std::string &name, glm::vec4 v4) : name(name), data(v4) {}
	Uniform(const std::string &name, glm::mat4 m4) : name(name), data(m4) {}
};

class Material {
public:
	const Shader &shader;
	const std::vector<Uniform> uniforms;
	const Texture* texture;

	Material(const Shader &shader, std::initializer_list<Uniform> uniforms);
	Material(const Shader &shader, std::initializer_list<Uniform> uniforms, const Texture* texture);
	~Material();

	void bind() const;
	void bind_with(std::initializer_list<Uniform> uniforms) const;
	void unbind() const;
};

} // namespace EasyGraphics

#endif
