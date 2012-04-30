#ifndef GUIIMAGE_H
#define GUIIMAGE_H

#include "GUIElement.h"
#include "ImageManager.h"

class GUIImage
	: public GUIElement
{
public:
	GUIImage(sf::RenderWindow* appRef, std::string filepath, float offsetX=0, float offsetY=0)
		: GUIElement(appRef)
	{
		m_Sprite = new sf::Sprite(ImageManager::GetSingleton()->GetImage(filepath), sf::Vector2f(offsetX, offsetY));
	}
	~GUIImage()
	{

	}
	virtual void Startup(){}
	virtual void Update(float deltaTime){}
	virtual void Shutdown()
	{
		if(m_Sprite != NULL){
			delete m_Sprite;
			m_Sprite = NULL;
		}
	}

	virtual void Render()
	{
		m_AppRef->Draw(*m_Sprite);
	}

private:
	sf::Sprite* m_Sprite;
};

#endif
