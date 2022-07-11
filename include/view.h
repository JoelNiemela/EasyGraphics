#ifndef VIEW_H
#define VIEW_H

#include <functional>

namespace EasyGraphics {

class Application;

class ViewInterface {
protected:
public:
	ViewInterface() {}
	virtual ~ViewInterface();

	virtual void update(double delta_time) {}
	virtual void render() {}
	virtual void gui() {}
};

template <std::derived_from<Application> T>
class View : public ViewInterface {
protected:
	using ApplicationType = T;

	const ApplicationType &application;
public:
	View(const ApplicationType &application) : application(application) {}
	virtual ~View() {}
};

} // namespace EasyGraphics

#endif
