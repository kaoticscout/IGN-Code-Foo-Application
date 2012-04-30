#ifndef GUISLIDER_H
#define GUISLIDER_H

#include "GUIElement.h"
#include "ImageManager.h"
#include "FontManager.h"
#include <iostream>
#include "Utility.h"
#include <stdlib.h>

class GUISlider
	: public GUIElement
{
public:
	//TODO: This should have more than 1 constructor
	GUISlider(sf::RenderWindow* appRef, sf::Vector2f offset, float length, int numOptions)
		: GUIElement(appRef)
	{
		m_Font = FontManager::GetSingleton()->GetFont("TCCEB.ttf");

		m_ButtonDown = false;
		m_Position = offset;
		m_Length = length;
		m_Dimensions = sf::Vector2f(10, 30);
		m_CurrentOption = 0;
		m_NumOptions = numOptions;
		m_Text = NULL;

		m_OptionSpaceWidth = length / (numOptions-1);
		m_SliderBounds = sf::FloatRect(m_Position.x, m_Position.y - m_Dimensions.y, m_Position.x + length, m_Position.y + m_Dimensions.y);
	}
	virtual ~GUISlider()
	{
		delete m_Text;
	}
	void Update(float deltaTime)
	{
		int mouseX = m_AppRef->GetInput().GetMouseX();
		int mouseY = m_AppRef->GetInput().GetMouseY();

		if(m_SliderBounds.Contains(static_cast<float>(mouseX), static_cast<float>(mouseY))){
			if(m_AppRef->GetInput().IsMouseButtonDown(sf::Mouse::Left)) {
				m_ButtonDown = true;
			}
		}
		if(!m_AppRef->GetInput().IsMouseButtonDown(sf::Mouse::Left)) {
			m_ButtonDown = false;
		}

		//detect closest option to mouse
		if(m_ButtonDown)
		{
			int option = Round((mouseX-m_Position.x) / (m_OptionSpaceWidth));

			if(option < 0)
				option = 0;
			if(option > m_NumOptions-1)
				option = m_NumOptions-1;

			m_CurrentOption = option;
		} 
		
		char buffer [33];
		_itoa_s(m_CurrentOption+1,buffer,10);
		if(m_Text != NULL)
			delete m_Text;
		m_Text = new sf::String(buffer);
		m_Text->SetFont(m_Font);
		m_Text->SetPosition(sf::Vector2f(m_Position.x + m_Length + 20, m_Position.y - 20));
		m_Text->SetColor(sf::Color(0, 0, 0));
		m_SliderPosition = sf::FloatRect((m_Position.x + m_CurrentOption*m_OptionSpaceWidth), (m_Position.y-m_Dimensions.y/2), (m_Position.x + m_CurrentOption*m_OptionSpaceWidth), (m_Position.y+m_Dimensions.y/2));
	}

	virtual void Startup() {}
	virtual void Shutdown() {}

	void Render() 
	{
		sf::Shape Line = sf::Shape::Line(sf::Vector2f(m_Position.x, m_Position.y), sf::Vector2f(m_Position.x + m_Length, m_Position.y), 4.0f, sf::Color(0, 0, 0, 255));
		sf::Shape OptionLine =  sf::Shape::Line(sf::Vector2f(m_SliderPosition.Left, m_SliderPosition.Top), sf::Vector2f(m_SliderPosition.Right, m_SliderPosition.Bottom), 2.0f, sf::Color(0, 0, 0));
		m_AppRef->Draw(Line);
		m_AppRef->Draw(OptionLine);
		m_AppRef->Draw(*m_Text);
	}

	int GetOption() const { return m_CurrentOption+1; }

private:
	sf::Font		m_Font;
	sf::String*		m_Text;

	bool			m_ButtonDown;
	sf::FloatRect	m_SliderBounds;
	sf::FloatRect	m_SliderPosition;
	sf::Vector2f	m_Position;
	sf::Vector2f	m_Dimensions;
	float			m_Length;

	int				m_NumOptions;
	int				m_CurrentOption;
	float			m_OptionSpaceWidth;
};

#endif