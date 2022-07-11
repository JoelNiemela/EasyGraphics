#ifndef APPLICATION_H
#define APPLICATION_H

#include "buffer/vertex_buffer.h"
#include "renderer.h"
#include "view.h"

namespace EasyGraphics {

class Application {
private:
	double current_time;
	double delta_time;

	std::unordered_map<std::string, Shader> shaders;
	std::unordered_map<std::string, Texture> textures;
	std::unordered_map<std::string, Material> materials;

	std::unique_ptr<Shader> null_shader;
	std::unique_ptr<Texture> null_texture;
	std::unique_ptr<Material> null_material;

	mutable GLuint vertex_array;
	mutable GLuint vertex_buffer;
	mutable GLuint index_buffer;
protected:
	ViewInterface *view;
public:
	Renderer renderer;

	Application();
	virtual ~Application();

	void run();

	template <std::derived_from<ViewInterface> ViewClass>
	void set_view(ViewClass* view) {
		this->view = static_cast<ViewInterface*>(view);
	}

	void use(const DrawBuffer &buffer) const;
	void use(const VertexArray &vertex_array) const;
	void use(const IndexBuffer &index_buffer) const;
	void use(const VertexBuffer &vertex_buffer) const;

	const Shader& load_shader(const std::string &name, const std::string &vertex_path, const std::string &fragment_path);
	const Shader& shader(const std::string &name) const;

	const Texture& load_texture(const std::string &name, const std::string &path);
	const Texture& texture(const std::string &name) const;

	const Material& make_material(const std::string &name, const Shader &shader, std::initializer_list<Uniform> uniforms);
	const Material& make_material(const std::string &name, const Shader &shader, std::initializer_list<Uniform> uniforms, const Texture &texture);
	const Material& material(const std::string &name) const;
private:
	virtual void update();
	void render();
	bool running() const;
};

} // namespace EasyGraphics

#endif
