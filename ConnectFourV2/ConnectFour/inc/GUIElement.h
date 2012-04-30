#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include <SFML/Graphics.hpp>

class GUIElement
{
public:
	GUIElement(sf::RenderWindow* appRef)
		: m_AppRef(appRef)
	{}

	virtual void Startup() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Shutdown() = 0;
	virtual void Render() = 0;

protected:
	sf::RenderWindow*	m_AppRef;
};

#endif