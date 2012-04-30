#include "Computer.h"
#include <iostream>
#include <time.h>

bool Computer::Update(sf::RenderWindow *appRef, float deltaTime, Gameboard *gameboard)
{ 
	if(!gameboard->IsGamepieceDropping())
	{
		DetermineMove(gameboard);
		return true;
	}
	return false; 
}

void Computer::DetermineMove(Gameboard *gameboard)
{
	switch(m_Difficulty)
	{
	case EASY:
		MoveEasy(gameboard);
		break;
	case MEDIUM:
		MoveMedium(gameboard);
		break;
	case HARD:
		break;
	}
}

//take win over block
int Computer::BlockOrWin(Gameboard* gameboard)
{
	std::vector<std::vector<Gamepiece*>> gameboardState = gameboard->GetGameboardState();
	int blockColumn = -1;
		
	//check horiz
	for(int row = 0; row < Height; ++row)
	{	
		for(int column = 0; column < Width-3; ++column)
		{
			int playerPieces = 0;
			int computerPieces = 0;
			int empty = 0;
			for(int i = 0; i < 4; ++i) { 
				if(gameboardState[column+i][row]->GetOwner() == PLAYERONE)
					playerPieces++;
				else if(gameboardState[column+i][row]->GetOwner() == PLAYERTWO)
					computerPieces++;
				else
					empty = column + i;
			}
			if(playerPieces == 3 || computerPieces == 3) {
				if(gameboard->GetValidRow(empty) == row) {
					if(playerPieces == 3) {
						blockColumn = empty;
						std::cout << "Block horiz" << std::endl;
					}
					else {
						std::cout << "Take horiz win" << std::endl;
						return empty;
					}
				}
			}
		}
	}

	//check vert
	for(int column = 0; column < Width; ++column)
	{	
		for(int row = 1; row < Height-3; ++row)
		{
			int playerPieces = 0;
			int computerPieces = 0;
			for(int i = 0; i < 4; ++i) { 
				if(gameboardState[column][row+i]->GetOwner() == PLAYERONE)
					playerPieces++;
				else if(gameboardState[column][row+i]->GetOwner() == PLAYERTWO)
					computerPieces++;
			}
			if(playerPieces == 3 || computerPieces == 3 ) {
				if(gameboardState[column][row]->GetOwner() == NONE) {
					if(playerPieces == 3) {
						blockColumn = column;
						std::cout << "Block vert" << std::endl;
					}
					else {
						std::cout << "Take vert win" << std::endl;
						return column;
					}
				}
			}
		}
	}

	return blockColumn;
}

//No intelligence, just select random locations
void Computer::MoveEasy(Gameboard *gameboard)
{
	bool validMove = false;
	while(!validMove)
	{
		int columnNumber = rand() % 7;
		if(gameboard->PlaceGamepiece(columnNumber, m_PlayerType) != false){ 
			validMove = true;
		}
	}
}

void Computer::MoveMedium(Gameboard *gameboard)
{
	bool validMove = false;
	while(!validMove)
	{
		int columnNumber;
		//try to block
		columnNumber = BlockOrWin(gameboard);
		//otherwise, just place randomly
		if(columnNumber == -1)
			columnNumber = rand() % 7;
		if(gameboard->PlaceGamepiece(columnNumber, m_PlayerType) != false){ 
			validMove = true;
		}
	}
}

void Computer::MoveHard(Gameboard *gameboard)
{
	std::cout << "NYI" << std::endl;
}

