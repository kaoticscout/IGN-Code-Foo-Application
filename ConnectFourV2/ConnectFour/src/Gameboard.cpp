#include "Gameboard.h"
#include <iostream>

Gameboard::Gameboard(sf::RenderWindow* const appRef)
	: m_AppRef(appRef)
{		
	m_HeaderSprite = new sf::Sprite(ImageManager::GetSingleton()->GetImage("gamepiece_Player.png"), sf::Vector2f(0, 0));
	m_GameboardBGSprite = new sf::Sprite(ImageManager::GetSingleton()->GetImage("gameplayBG.png"), sf::Vector2f(0, 0));
	m_GameboardSprite = new sf::Sprite(ImageManager::GetSingleton()->GetImage("connect4board.png"), sf::Vector2f(0, 26));
	m_IsDropping = false;
	m_Winner = NONE;
	m_DisplayingWinner = false;
}

void Gameboard::ClearGameboard()
{	
	delete m_HeaderSprite;
	delete m_GameboardBGSprite;
	delete m_GameboardSprite;

	//clear gameboard state
	for(std::vector<std::vector<Gamepiece*>>::iterator it = m_GameboardState.begin(); it != m_GameboardState.end(); ++it)
	{
		std::vector<Gamepiece*> *column = &(*it);
		for(std::vector<Gamepiece*>::iterator innerIt = column->begin(); innerIt != column->end(); ++innerIt) {
			delete *innerIt;
		}
		column->empty();
	}
	m_GameboardState.empty();
}

void Gameboard::InitializeGameboard()
{
	//initialize
	for(int i = 0; i < Width; ++i)
	{
		std::vector<Gamepiece*> column;
		for(int j = 0; j < Height; ++j) {
			column.push_back(new Gamepiece(NONE));
		}
		m_GameboardState.push_back(column);
	}
	//initialize sprites
	for(int i = 0; i < Width; ++i)
	{
		std::vector<sf::Sprite> column;
		for(int j = 0; j < Height; ++j) {
			column.push_back(sf::Sprite());
		}
		m_GameboardSprites.push_back(column);
	}
}

bool Gameboard::PlaceGamepiece(int columnNumber, PLAYERTYPE playerType, bool hover)
{
	if(!m_IsDropping)
	{
		if(hover == true)
		{
			m_HeaderSprite->SetPosition(GetGamepieceLocation(-1,columnNumber));
			m_HeaderSprite->SetColor(sf::Color(255, 255, 255, 255));
			return false;
		}
		
		m_HeaderSprite->SetColor(sf::Color(255, 255, 255, 0));
		
		const int row = GetValidRow(columnNumber);
		if(row != -1) {
			m_GameboardState[columnNumber][row]->SetOwner(playerType);
			if(playerType == PLAYERONE)
				m_GameboardSprites[columnNumber][row] = sf::Sprite(ImageManager::GetSingleton()->GetImage("gamepiece_Player.png"),  sf::Vector2f(GetGamepieceLocation(-1, columnNumber)));
			else
				m_GameboardSprites[columnNumber][row] = sf::Sprite(ImageManager::GetSingleton()->GetImage("gamepiece_Computer.png"), sf::Vector2f(GetGamepieceLocation(-1, columnNumber)));
			//set fall info
			m_FallLocation = GetGamepieceLocation(row, columnNumber).y;
			m_DroppingSprite = &m_GameboardSprites[columnNumber][row];
			m_IsDropping = true;
			return true;
		}
	}
	return false;
}
		
void Gameboard::Update(float deltaTime)
{
	//update falling gamepiece
	if(m_IsDropping)
	{
		sf::Vector2f pos = m_DroppingSprite->GetPosition();
		if(pos.y + FallAmt * deltaTime >= m_FallLocation)
		{
			m_DroppingSprite->SetPosition(pos.x, m_FallLocation);
			m_IsDropping = false;
		}
		else  {
			m_DroppingSprite->SetPosition(pos.x, pos.y + FallAmt);
		}
	}	

	//flash winning pieces
	if(m_DisplayingWinner && m_DisplayTime > 0)
	{
		m_DisplayTime-= deltaTime;
		if(static_cast<int>(m_DisplayTime) % 100 == 0)
		{
			for(int i = 0; i < 4; ++i)
			{
				if(m_WinningPieces[i]->GetColor() == sf::Color(255, 255, 255, 255))
					m_WinningPieces[i]->SetColor(sf::Color(255, 255, 255, 0));
				else
					m_WinningPieces[i]->SetColor(sf::Color(255, 255, 255, 255));
			}
		}
	}
	else if(m_DisplayTime <= 0) {
		m_DisplayingWinner = false;
	}
}

void Gameboard::Render()
{
	m_AppRef->Draw(*m_GameboardBGSprite);
	m_AppRef->Draw(*m_HeaderSprite);

	//draw gamepieces
	for(std::vector<std::vector<sf::Sprite>>::iterator it = m_GameboardSprites.begin(); it != m_GameboardSprites.end(); ++it)
	{
		std::vector<sf::Sprite> *column = &(*it);
		for(std::vector<sf::Sprite>::iterator innerIt = column->begin(); innerIt != column->end(); ++innerIt) {
			m_AppRef->Draw(*innerIt);
		}
	}
	m_AppRef->Draw(*m_GameboardSprite);
}

sf::Vector2f Gameboard::GetGamepieceLocation(const int row, const int column)
{
	const int xLoc = HorizPadding + HorizSpacing+5 + ((HorizSpacing*2 + ImgWidth) * column);
	const int yLoc = VertPadding + VertSpacing + ((VertSpacing + ImgHeight) * row); 
	return sf::Vector2f(xLoc, yLoc);
}

const int Gameboard::GetColumnNumber(int mouseX)
{
	int currentCol = (mouseX - HorizPadding) / (ImgWidth+HorizSpacing*2);		
	if(currentCol < 0)
		currentCol = 0;
	else if(currentCol > Width-1)
		currentCol = Width-1;
	return currentCol;
}

bool Gameboard::CheckTie()
{
	bool tie = true;
	for(int i = 0; i < Width; ++i){
		if(m_GameboardState[i][0]->GetOwner() == NONE)
			tie = false;
	}

	return tie;
}

PLAYERTYPE Gameboard::CheckWinAllDirections()
{
	bool playerOneWin = true;
	bool playerTwoWin = true;
	for(int column = 0; column < Width; column++)
	{
		for(int row = 0; row < Height; row++)
		{
			//Check Horiz Win
			if(column < Width-3) {
				for(int i = 0; i < 4; i++)
				{
					if(m_GameboardState[column+i][row]->GetOwner() != PLAYERONE) { playerOneWin = false; }
					if(m_GameboardState[column+i][row]->GetOwner() != PLAYERTWO) { playerTwoWin = false; }
					m_WinningPieces[i] = &m_GameboardSprites[column+i][row];
				}
				if(playerOneWin){ return PLAYERONE; }
				if(playerTwoWin){ return PLAYERTWO; }
			}
			
			//Check Vert Win				
			playerOneWin = true;
			playerTwoWin = true;		
			if(row < Height-3) {
				for(int i = 0; i < 4; i++)
				{
					if(m_GameboardState[column][row+i]->GetOwner() != PLAYERONE) { playerOneWin = false; }
					if(m_GameboardState[column][row+i]->GetOwner() != PLAYERTWO) { playerTwoWin = false; }
					m_WinningPieces[i] = &m_GameboardSprites[column][row+i];
				}
				if(playerOneWin){ return PLAYERONE; }
				if(playerTwoWin){ return PLAYERTWO; }
			}

			//Check Down-Right Win	
			playerOneWin = true;
			playerTwoWin = true;		
			if(row < Height-3 && column < Width-3) {
				for(int i = 0; i < 4; i++)
				{
					if(m_GameboardState[column+i][row+i]->GetOwner() != PLAYERONE) { playerOneWin = false; }
					if(m_GameboardState[column+i][row+i]->GetOwner() != PLAYERTWO) { playerTwoWin = false; }
					m_WinningPieces[i] = &m_GameboardSprites[column+i][row+i];
				}
				if(playerOneWin){ return PLAYERONE; }
				if(playerTwoWin){ return PLAYERTWO; }
			}

			//Check Down-Left Win
			playerOneWin = true;
			playerTwoWin = true;		
			if(row < Height-3 && column > 2) {
				for(int i = 0; i < 4; i++)
				{
					if(m_GameboardState[column-i][row+i]->GetOwner() != PLAYERONE) { playerOneWin = false; }
					if(m_GameboardState[column-i][row+i]->GetOwner() != PLAYERTWO) { playerTwoWin = false; }
					m_WinningPieces[i] = &m_GameboardSprites[column-i][row+i];
				}
				if(playerOneWin){ return PLAYERONE; }
				if(playerTwoWin){ return PLAYERTWO; }
			}
		}
	}
	return NONE;
}

PLAYERTYPE Gameboard::CheckWin()
{
	//if no game pieces have an owner playertype of none, there are no valid spaces left, game is a tie
	bool tie = CheckTie();
	PLAYERTYPE winner = CheckWinAllDirections();
	if(winner != NONE && !tie) {
		m_DisplayingWinner = true;
		m_Winner = winner;
		m_DisplayTime = DefaultDisplayTicks;
	}

	if(tie) {
		m_Winner = TIE;
		return TIE;
	}
	else
		return winner;
}

const int Gameboard::GetValidRow(const int columnNumber)
{
	std::vector<Gamepiece*> column = m_GameboardState[columnNumber];
	for(int i = 5; i >= 0; --i)
	{
		if(column[i]->GetOwner() == NONE) {
			return i;
		}
	}
	return -1;
}


Gameboard Gameboard::ApplyMove(Gameboard gameboard, int column)
{
	return Gameboard(m_AppRef);
}

std::vector<int> Gameboard::GetMoves()
{
	std::vector<int> moves;
	for(int col = 0; col < Width; ++col)
	{
		if(m_GameboardState[col][0]->GetOwner() == NONE)
			moves.push_back(col);
	}

	return moves;
}