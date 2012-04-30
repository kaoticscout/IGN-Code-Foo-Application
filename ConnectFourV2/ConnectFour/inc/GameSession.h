#ifndef GAMESESSION_H
#define GAMESESSION_H

#include "Player.h"
#include "Computer.h"

class GameSession
{
public:
	GameSession(sf::RenderWindow *appRef, DIFFICULTY difficulty, int firstMove);
	void Update(sf::RenderWindow *appRef, float deltaTime);
	void Render();
	void EndGame(PLAYERTYPE winner);

	inline int GetPlayerTurn() const { return m_ActivePlayer->Type(); }
	inline int GetWinner() const { return static_cast<int>(m_Gameboard->GetWinner()); }
	Gameboard* GetGameboard() const { return m_Gameboard; }

private:
	void SwitchPlayer();

	sf::RenderWindow	*m_AppRef;
	GamePlayer			*m_ActivePlayer, *m_PlayerOne, *m_PlayerTwo;
	Gameboard			*m_Gameboard;
};

#endif