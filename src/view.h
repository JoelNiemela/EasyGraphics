#ifndef VIEW_H
#define VIEW_H

#include "renderer.h"

#include <functional>

namespace EasyGraphics {

class View {
protected:
	const Renderer &renderer;
public:
	View(const Renderer &renderer) : renderer(renderer) {}
	virtual ~View();

	virtual void update(double delta_time) {}
	virtual void render() {}
	virtual void gui() {}
};

} // namespace EasyGraphics

#endif
