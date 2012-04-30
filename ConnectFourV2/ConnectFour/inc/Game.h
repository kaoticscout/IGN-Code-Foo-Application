#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "MessageListener.h"
#include "GameSession.h"

enum GAMESTATE
{
	MAINMENU,
	GAMEOPTIONS,
	GAME,
	ENDGAME,
	QUIT
};

class Game
	: public MessageListener
{
public:
	Game()
		: m_IsRunning(true)
	{}
	~Game(){}

	void Startup();
	void Shutdown();
	void Run();
	void ChangeState(GAMESTATE newState, GameMessage* msg = 0);
	GameMessage* ProcessMessage(GameMessage* msg);

private:
	bool m_IsRunning;
	sf::RenderWindow	*m_App;
	GAMESTATE			m_GameState;
	GameSession			*m_GameSession;
};

#endif