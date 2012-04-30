#ifndef INPUTLISTENER_H
#define INPUTLISTENER_H

#include <SFML\Graphics.hpp>

class InputListener
{
public:
	virtual void MouseClick(sf::Mouse::Button) = 0;
	virtual void KeyPress(sf::Key::Code) = 0;
};

#endif