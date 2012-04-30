#ifndef COMPUTER_H
#define COMPUTER_H

#include "GamePlayer.h"

enum DIFFICULTY
{
	EASY,
	MEDIUM,
	HARD
};

class Computer
	: public GamePlayer
{
public:
	Computer(DIFFICULTY difficulty)
		: GamePlayer(PLAYERTWO), m_Difficulty(difficulty)
	{}

	bool Update(sf::RenderWindow *appRef, float deltaTime, Gameboard *gameboard);
	void DetermineMove(Gameboard *gameboard);
	int BlockOrWin(Gameboard* gameboard);

	void MoveEasy(Gameboard *gameboard);	//No intelligence, just select random locations
	void MoveMedium(Gameboard *gameboard);
	void MoveHard(Gameboard *gameboard);


private:
	DIFFICULTY m_Difficulty;
};

#endif