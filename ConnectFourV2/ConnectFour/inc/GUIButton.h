#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include "GUIElement.h"
#include "ImageManager.h"
#include "FontManager.h"
#include <iostream>

class GUIButton
	: public GUIElement
{
public:
	//TODO: This should have more than 1 constructor
	GUIButton(sf::RenderWindow* appRef, std::string filename = "", std::string text = "", sf::Color fontColor = sf::Color(255,255,255,255),
				float offsetX = 0, float offsetY = 0, float sizeX = 0, float sizeY = 0)
		: GUIElement(appRef)
	{
		m_CurrentSprite = NULL;
		m_Text = NULL;
		m_Pressed = false;
		m_Selected = false;
		m_Position = sf::Vector2f(offsetX,offsetY);

		SetBGImage(filename);
		SetText(text, offsetX, offsetY, fontColor);

		if(sizeX != 0 && sizeY != 0) {
			m_Dimensions = sf::Vector2f(sizeX, sizeY);
		}
	}

	virtual ~GUIButton()
	{
		if(m_CurrentSprite != NULL)
			delete m_CurrentSprite;
		if(m_Text != NULL)
			delete m_Text;
	}

	void Update(float deltaTime)
	{
		int mouseX = m_AppRef->GetInput().GetMouseX();
		int mouseY = m_AppRef->GetInput().GetMouseY();

		m_ButtonBounds = sf::FloatRect(m_Position.x, m_Position.y, (m_Position.x + m_Dimensions.x), (m_Position.y + m_Dimensions.y));
		if(m_ButtonBounds.Contains(static_cast<float>(mouseX), static_cast<float>(mouseY))){
			OnActive();
		}
		else{
			if(m_CurrentSprite != NULL) 
				m_CurrentSprite->SetColor(sf::Color(255, 255, 255));
		}
	}

	virtual void Startup() {}
	virtual void Shutdown() {}

	bool IsPressed() const { return m_Pressed; }
	
	void SetSelected(bool value) 
	{
		m_Pressed = false;
		m_Selected = value; 	
		if(m_Selected) {
			m_Text->SetScale(1.2f, 1.2f);
			m_Text->SetColor(sf::Color(81, 146, 202, 255));
		}
		else{
			m_Text->SetScale(1.0f, 1.0f);
			m_Text->SetColor(sf::Color(0, 0, 0, 255));
		}
	}

	void Render() 
	{
		if(m_CurrentSprite != NULL)
			m_AppRef->Draw(*m_CurrentSprite);
		if(m_Text != NULL)
			m_AppRef->Draw(*m_Text);
	}

protected:
	void OnPress() 
	{
		m_Pressed = true;
	}

	void OnActive()
	{
		m_Active = true;
		if(m_CurrentSprite != NULL)
			m_CurrentSprite->SetColor(sf::Color(255, 195, 0));
		if(m_AppRef->GetInput().IsMouseButtonDown(sf::Mouse::Left))
		{
			if(m_CurrentSprite != NULL)
				m_CurrentSprite->SetColor(sf::Color(75, 75, 75));
			OnPress();
		}
	}

	void SetText(std::string text, float offsetX, float offsetY, sf::Color fontColor)
	{		
		if(text != "")
		{			
			m_Text = new sf::String(text);
			m_Text->SetFont(FontManager::GetSingleton()->GetFont("TCCEB.ttf"));
			m_Text->Move(offsetX, offsetY);
			m_Text->SetColor(fontColor);
		}
	}
	
	void SetBGImage(std::string imgLoc)
	{		
		if(imgLoc != "")
		{
			m_BGImage = ImageManager::GetSingleton()->GetImage(imgLoc);
			m_CurrentSprite = new sf::Sprite();
			m_CurrentSprite->SetPosition(m_Position.x, m_Position.y);
			m_CurrentSprite->SetImage(m_BGImage);
			m_Dimensions =  sf::Vector2f(static_cast<float>(m_BGImage.GetWidth()), static_cast<float>(m_BGImage.GetHeight()));
		}
	}

	sf::Font*			m_Font;
	sf::String*			m_Text;
	sf::Image			m_BGImage;
	sf::Sprite*			m_CurrentSprite;

	sf::FloatRect		m_ButtonBounds;
	sf::Vector2f		m_Dimensions;
	sf::Vector2f		m_Position;
	bool				m_Pressed; //click
	bool				m_Active; //rollover
	bool				m_Selected; //clicked
};

#endif