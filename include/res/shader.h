#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <string>
#include <unordered_map>

namespace EasyGraphics {

struct Uniform;

class Shader {
private:
	GLuint id;
	std::string vertex_shader_filepath;
	std::string fragment_shader_filepath;
	mutable std::unordered_map<std::string, GLint> uniform_location_cache;
public:
	Shader() {}
	Shader(const std::string &vertex_shader_filepath, const std::string &fragment_shader_filepath);
	~Shader();

	static Shader* from_source(const char* vertex_shader_src, const char* fragment_shader_src);

	void bind() const;
	void unbind() const;

	void set_uniform(const Uniform &uniform) const;
	void set_uniform(const std::string &name, GLint value) const;
	void set_uniform(const std::string &name, GLfloat value) const;
	void set_uniform(const std::string &name, glm::vec3 vec) const;
	void set_uniform(const std::string &name, glm::vec4 vec) const;
	void set_uniform(const std::string &name, glm::mat4 mat) const;
private:
	static std::string load_file(const std::string &file_path);
	static GLuint compile_shader(GLuint type, const std::string &src);
	static GLuint create_program(const std::string &vertex_src, const std::string &fragment_src);
	GLint get_uniform_location(const std::string &name) const;
};

} // namespace EasyGraphics

#endif
