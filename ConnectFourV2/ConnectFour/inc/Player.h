#ifndef PLAYER_H
#define PLAYER_H

#include "GamePlayer.h"
#include "ImageManager.h"
#include "InputManager.h"
#include <iostream>

class Player
	: public GamePlayer, public InputListener
{
public:
	Player()
		: GamePlayer(PLAYERONE)
	{				
		if (m_MoveSoundBuffer.LoadFromFile("media/sounds/gamepiece_drop.wav"))
		{
			m_MoveSound.SetBuffer(m_MoveSoundBuffer);
			m_MoveSound.SetLoop(false);
		}
		InputManager::GetSingleton()->AddInputListener(this);
		m_ClickDelay = 25;
		m_MouseClick = false;
	}
	virtual ~Player()
	{
		InputManager::GetSingleton()->RemoveInputListener(this);
	}
	
	void MouseClick(sf::Mouse::Button) 
	{
		if(m_ClickDelay <= 0)
			m_MouseClick = true;
	}
	
	void KeyPress(sf::Key::Code) {}

	bool Update(sf::RenderWindow *appRef, float deltaTime, Gameboard *gameboard)
	{
		m_ClickDelay--;
		const int mouseX = appRef->GetInput().GetMouseX();

		if(m_MouseClick)
		{
			m_MouseClick = false;
			bool placed = gameboard->PlaceGamepiece(gameboard->GetColumnNumber(mouseX), m_PlayerType);
			if(placed) {
				m_MoveSound.Play();
			}
			return placed;
		}
		return gameboard->PlaceGamepiece(gameboard->GetColumnNumber(mouseX), m_PlayerType, true);
	}
private:
	bool	m_MouseClick;
	int		m_ClickDelay; //delay before clicks take effect
};

#endif