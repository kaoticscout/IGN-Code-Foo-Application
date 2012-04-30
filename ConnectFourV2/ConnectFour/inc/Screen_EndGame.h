#ifndef SCREEN_ENDGAME_H
#define SCREEN_ENDGAME_H

#include "GUIScreen.h"
#include "GUIImage.h"
#include "GUIButton.h"
#include "MessageSystem.h"
#include "Game.h"

class Screen_EndGame
	: public GUIScreen
{
public:
	void Startup()
	{
		m_GUIElements.push_back(new GUIImage(m_AppRef, "GameOverBG.png"));
	}
	void Update(float deltaTime)
	{

	}
	Screen_EndGame(std::string name, sf::RenderWindow* appRef)
		: GUIScreen(name, appRef)
	{}
	virtual ~Screen_EndGame(){}
};

#endif