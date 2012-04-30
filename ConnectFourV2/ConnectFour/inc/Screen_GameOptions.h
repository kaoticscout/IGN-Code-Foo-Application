#ifndef SCREEN_GAMEOPTIONS_H
#define SCREEN_GAMEOPTIONS_H

#include "GUIScreen.h"
#include "GUIImage.h"
#include "GUIButton.h"
#include "MessageSystem.h"
#include "Game.h"
#include "Computer.h"

class Screen_GameOptions
	: public GUIScreen
{
public:
	void Startup()
	{
		m_GUIElements.push_back(new GUIImage(m_AppRef, "GameOptionsBG.png"));
		m_playButton = new GUIButton(m_AppRef, "", "Play", sf::Color(0,0,0,255), 600, 450, 100, 30);
		m_closeButton = new GUIButton(m_AppRef, "Btn_Close.png", "", sf::Color(0,0,0,0), 700, 82, 0, 0);
		
		m_computerOpponentButton = new GUIButton(m_AppRef, "", "Computer", sf::Color(0,0,0,255), 250, 225, 100, 30);
		m_easyButton = new GUIButton(m_AppRef, "", "Easy", sf::Color(0,0,0,255), 250, 300, 100, 30);
		m_mediumButton = new GUIButton(m_AppRef, "", "Medium", sf::Color(0,0,0,255), 380, 300, 100, 30);
		m_hardButton = new GUIButton(m_AppRef, "", "Hard", sf::Color(0,0,0,255), 550, 300, 100, 30);
		m_playerFirstButton = new GUIButton(m_AppRef, "", "Player", sf::Color(0,0,0,255), 250, 380, 100, 30);
		m_computerFirstButton = new GUIButton(m_AppRef, "", "Computer", sf::Color(0,0,0,255), 400, 380, 100, 30);
		
		m_GUIElements.push_back(m_playButton);
		m_GUIElements.push_back(m_closeButton);
		m_GUIElements.push_back(m_easyButton);
		m_GUIElements.push_back(m_mediumButton);
		m_GUIElements.push_back(m_hardButton);
		m_GUIElements.push_back(m_playerFirstButton);
		m_GUIElements.push_back(m_computerFirstButton);
		m_GUIElements.push_back(m_computerOpponentButton);

		m_computerOpponentButton->SetSelected(true);
		m_easyButton->SetSelected(true);
		m_Difficulty = EASY;
		m_playerFirstButton->SetSelected(true);
		m_FirstMove = 1;
	}
	void Update(float deltaTime)
	{
		GUIScreen::Update(deltaTime);

		if(m_playButton->IsPressed())
		{	
			GameMessage* msgPlay = new GameMessage(GameMessage::STATECHANGE);
			msgPlay->TargetState = GAME;
			msgPlay->difficulty = m_Difficulty;
			msgPlay->firstMove = m_FirstMove;
			MessageSystem::GetSingleton()->QueueMessage(msgPlay);
		}
		if(m_closeButton->IsPressed())
		{	
			GameMessage* msgPlay = new GameMessage(GameMessage::STATECHANGE);
			msgPlay->TargetState = MAINMENU;
			MessageSystem::GetSingleton()->QueueMessage(msgPlay);
		}

		if(m_easyButton->IsPressed())
		{
			m_Difficulty = EASY;
			m_easyButton->SetSelected(true);
			m_mediumButton->SetSelected(false);
			m_hardButton->SetSelected(false);
		}
		else if(m_mediumButton->IsPressed())
		{
			m_Difficulty = MEDIUM;
			m_easyButton->SetSelected(false);
			m_mediumButton->SetSelected(true);
			m_hardButton->SetSelected(false);
		}
		else if(m_hardButton->IsPressed())
		{
			m_Difficulty = HARD;
			m_easyButton->SetSelected(false);
			m_mediumButton->SetSelected(false);
			m_hardButton->SetSelected(true);
		}

		if(m_playerFirstButton->IsPressed())
		{
			m_FirstMove = 1;
			m_playerFirstButton->SetSelected(true);
			m_computerFirstButton->SetSelected(false);
		}
		else if (m_computerFirstButton->IsPressed())
		{
			m_FirstMove = 2;
			m_playerFirstButton->SetSelected(false);
			m_computerFirstButton->SetSelected(true);
		}

	}
	Screen_GameOptions(std::string name, sf::RenderWindow* appRef)
		: GUIScreen(name, appRef)
	{}
	virtual ~Screen_GameOptions(){}

private:
	GUIButton*	m_playButton;
	GUIButton*	m_closeButton;
	
	GUIButton*	m_easyButton;
	GUIButton*	m_mediumButton;
	GUIButton*	m_hardButton;

	GUIButton*	m_playerFirstButton;
	GUIButton*	m_computerFirstButton;
	
	GUIButton*	m_computerOpponentButton;

	DIFFICULTY m_Difficulty;
	int m_FirstMove;
};

#endif