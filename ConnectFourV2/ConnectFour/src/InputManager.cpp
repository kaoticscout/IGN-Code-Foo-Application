#include "InputManager.h"
#include <iostream>

InputManager* InputManager::p_Instance = NULL;

void InputManager::Shutdown()
{
	m_InputListeners.clear();
	delete p_Instance;
}

InputManager* InputManager::GetSingleton()
{
  if(p_Instance == NULL){
	  p_Instance = new InputManager();
  }
  return p_Instance;
}

void InputManager::MouseClick(sf::Mouse::Button eventref)
{	
	for(std::list<InputListener*>::iterator it = m_InputListeners.begin(); it != m_InputListeners.end(); ++it) {
		(*it)->MouseClick(eventref);
	}
}

void InputManager::KeyPress(sf::Key::Code eventref)
{	
	for(std::list<InputListener*>::iterator it = m_InputListeners.begin(); it != m_InputListeners.end(); ++it) {
		(*it)->KeyPress(eventref);
	}
}