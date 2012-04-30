#ifndef GUISCREEN_H
#define GUISCREEN_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "GUIElement.h"

class GUIScreen
{
public:	
	GUIScreen(std::string name, sf::RenderWindow* appRef)
		: m_AppRef(appRef)
	{
		m_Name = name;
	}
	virtual ~GUIScreen(){}

	virtual void Startup() = 0;
	virtual void Update(float deltaTime)
	{
		for(std::vector<GUIElement*>::iterator it = m_GUIElements.begin(); it != m_GUIElements.end(); ++it){
			(*it)->Update(deltaTime);
		}
	}
	virtual void Render()
	{
		for(std::vector<GUIElement*>::iterator it = m_GUIElements.begin(); it != m_GUIElements.end(); ++it){
			(*it)->Render();
		}
	}
	virtual void Shutdown() 
	{
		for(std::vector<GUIElement*>::iterator it = m_GUIElements.begin(); it != m_GUIElements.end(); ++it){
			delete *it;
		}
		m_GUIElements.clear();
	}

	std::string GetName() const { return m_Name; }

protected:	
	std::string					m_Name;
	sf::RenderWindow*			m_AppRef;
	sf::Vector2f				m_Size;
	sf::Vector2f				m_Position;
	sf::Sprite*					m_BackgroundImage;
	std::vector<GUIElement*>	m_GUIElements;

};

#endif