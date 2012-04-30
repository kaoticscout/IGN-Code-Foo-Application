#include "Game.h"
#include "GUIManager.h"
#include "InputManager.h"
#include "FontManager.h"
#include <SFML/System.hpp>
#include <time.h>

void Game::Startup()
{
	int height = 600;
	int width = 800;
	m_App = new sf::RenderWindow(sf::VideoMode(width, height, 32), "Connect Four");
	m_GameState = MAINMENU;	
	MessageSystem::GetSingleton()->AddListener(this);
	srand ( time(NULL) );
}

void Game::Shutdown()
{	
	ImageManager::GetSingleton()->Shutdown();
	FontManager::GetSingleton()->Shutdown();
	InputManager::GetSingleton()->Shutdown();
	GUIManager::GetSingleton()->Shutdown();
	delete m_App;
}

void Game::Run()
{
	ChangeState(m_GameState);
	
	while(m_IsRunning && m_App->IsOpened())
	{	
		//Process events
        sf::Event Event;
        while (m_App->GetEvent(Event))
        {
            if (Event.Type == sf::Event::Closed)
                m_App->Close();       
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
			{
				if(m_GameState == MAINMENU) 
					m_App->Close();
				else if(m_GameState == GAMEOPTIONS)
					ChangeState(MAINMENU);
				else if(m_GameState == GAME)
					ChangeState(MAINMENU);
			}
			if(Event.Type == sf::Event::KeyPressed)
				InputManager::GetSingleton()->KeyPress(Event.Key.Code);
			if(Event.Type == sf::Event::MouseButtonReleased)
				InputManager::GetSingleton()->MouseClick(Event.MouseButton.Button);
        }

		m_App->Clear();

		//Game session?
		if(m_GameState == GAME)
			m_GameSession->Update(m_App, m_App->GetFrameTime() * 1000);

		MessageSystem::GetSingleton()->Update(m_App->GetFrameTime() * 1000);
		
		GUIManager::GetSingleton()->UpdateScreens(m_App->GetFrameTime() * 1000);
		m_App->Display();

		float fps = 1.f / m_App->GetFrameTime();
	}
}

void Game::ChangeState(GAMESTATE newState, GameMessage* msg)
{
	m_GameState = newState;
	switch(newState)
	{
	case MAINMENU:
		GUIManager::GetSingleton()->PopScreen();
		GUIManager::GetSingleton()->PushScreen(new Screen_MainMenu("Main Menu", m_App));
		break;
	case GAMEOPTIONS:
		GUIManager::GetSingleton()->PopScreen();
		GUIManager::GetSingleton()->PushScreen(new Screen_GameOptions("Game Options", m_App));
		break;
	case GAME:
		m_GameSession = new GameSession(m_App, msg->difficulty, msg->firstMove);
		GUIManager::GetSingleton()->PopScreen();
		GUIManager::GetSingleton()->PushScreen(new Screen_GamePlay("Gameplay", m_App, m_GameSession));
		break;
	case ENDGAME:
		delete m_GameSession;
		GUIManager::GetSingleton()->PopScreen();
		ChangeState(GAMEOPTIONS); 
		break;
	case QUIT:
		m_App->Close();
	default:
		break;
	}
}

GameMessage* Game::ProcessMessage(GameMessage* msg)
{
	if(msg->MsgType == GameMessage::STATECHANGE){
		ChangeState(msg->TargetState, msg);
	}
	return NULL;
}