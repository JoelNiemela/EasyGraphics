#ifndef APPLICATION_H
#define APPLICATION_H

#include "renderer.h"
#include "view.h"

namespace EasyGraphics {

class Application {
private:
	double current_time;
	double delta_time;
protected:
	View *view;
public:
	Renderer renderer;

	Application();
	virtual ~Application();

	void run();
private:
	virtual void update();
	void render();
	bool running() const;
};

} // namespace EasyGraphics

#endif
