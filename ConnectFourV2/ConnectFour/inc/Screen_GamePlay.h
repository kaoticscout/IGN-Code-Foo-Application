#ifndef SCREEN_GAMEPLAY_H
#define SCREEN_GAMEPLAY_H

#include "GUIScreen.h"
#include "GameSession.h"

class Screen_GamePlay
	: public GUIScreen
{
public:
	void Startup()
	{
		m_Font = FontManager::GetSingleton()->GetFont("TCCEB.ttf");
	}
	void Update(float deltaTime)
	{
		//if no winner yet, display turn
		if(m_GameSession->GetWinner() == NONE)
		{
			if(m_GameSession->GetPlayerTurn() == PLAYERONE) {
				m_PlayerTurnText = sf::String("Player's Turn");
				m_PlayerTurnText.Move(340, 545);
			}
			else {
				m_PlayerTurnText = sf::String("Computer's Turn");
				m_PlayerTurnText.Move(330, 545);
			}
		}
		//if winner, display winner
		else {
			if(m_GameSession->GetWinner() == PLAYERONE) {
				m_PlayerTurnText = sf::String("You Won!");
				m_PlayerTurnText.Move(360, 545);
			}
			else if(m_GameSession->GetWinner()  == PLAYERTWO) {
				m_PlayerTurnText = sf::String("Computer Won");
				m_PlayerTurnText.Move(330, 545);
			}
			else {
				m_PlayerTurnText = sf::String("Tie");
				m_PlayerTurnText.Move(380, 545);
			}
		}
		m_PlayerTurnText.SetColor(sf::Color(0, 0, 0, 255));
		m_PlayerTurnText.SetFont(m_Font);
		m_AppRef->Draw(m_PlayerTurnText);
	}

	Screen_GamePlay(std::string name, sf::RenderWindow *appRef, GameSession *gameSession)
		: GUIScreen(name, appRef), m_GameSession(gameSession)
	{}
	virtual ~Screen_GamePlay(){}

private:
	sf::Font	m_Font;
	GameSession	*m_GameSession;
	sf::String	m_PlayerTurnText;
};

#endif