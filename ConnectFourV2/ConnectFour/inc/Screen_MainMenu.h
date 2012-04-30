#ifndef SCREEN_MAIN_MENU_H
#define SCREEN_MAIN_MENU_H

#include "GUIScreen.h"
#include "GUIImage.h"
#include "GUIButton.h"
#include "MessageSystem.h"
#include "Game.h"

class Screen_MainMenu
	: public GUIScreen
{
public:
	void Startup()
	{
		m_GUIElements.push_back(new GUIImage(m_AppRef, "ConnectFourBG.png"));
		m_playButton = new GUIButton(m_AppRef, "", "Play", sf::Color(255,255,255,255), 300, 410, 100, 30);
		m_exitButton = new GUIButton(m_AppRef, "", "Exit", sf::Color(255,255,255,255), 450, 410, 100, 30);
		m_GUIElements.push_back(m_playButton);
		m_GUIElements.push_back(m_exitButton);
	}
	void Update(float deltaTime)
	{
		GUIScreen::Update(deltaTime);

		if(m_playButton->IsPressed())
		{	
			GameMessage* msgPlay = new GameMessage(GameMessage::STATECHANGE);
			msgPlay->TargetState = GAMEOPTIONS;
			MessageSystem::GetSingleton()->QueueMessage(msgPlay);
		}
		if(m_exitButton->IsPressed())
		{
			GameMessage* msgExit = new GameMessage(GameMessage::STATECHANGE);
			msgExit->TargetState = QUIT;
			MessageSystem::GetSingleton()->QueueMessage(msgExit);	
		}
	}

	Screen_MainMenu(std::string name, sf::RenderWindow* appRef)
		: GUIScreen(name, appRef)
	{}
	virtual ~Screen_MainMenu(){}

private:
	GUIButton* m_playButton;
	GUIButton* m_exitButton;
};

#endif