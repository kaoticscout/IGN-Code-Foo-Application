#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <list>
#include "InputListener.h"

class InputManager
{
public:
	static InputManager* GetSingleton();
	void AddInputListener(InputListener* listener){ m_InputListeners.push_back(listener); }
	void RemoveInputListener(InputListener* listener){ m_InputListeners.remove(listener); }
	void MouseClick(sf::Mouse::Button);
	void KeyPress(sf::Key::Code);
	void Shutdown();

private:
	InputManager(){}
	static InputManager* p_Instance;

	std::list<InputListener*> m_InputListeners;
};

#endif