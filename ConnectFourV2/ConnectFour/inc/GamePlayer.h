#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H

#include "Gameboard.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class GamePlayer
{
public:
	virtual ~GamePlayer(){}
	virtual bool Update(sf::RenderWindow *appRef, float deltaTime, Gameboard *gameboard)
	{			
		return true;
	}
	int Type() { return m_PlayerType; }
protected:
	GamePlayer(PLAYERTYPE playerType)
		: m_PlayerType(playerType)
	{}
	PLAYERTYPE	m_PlayerType; 
	sf::Sound	m_MoveSound;
	sf::SoundBuffer m_MoveSoundBuffer;

};

#endif