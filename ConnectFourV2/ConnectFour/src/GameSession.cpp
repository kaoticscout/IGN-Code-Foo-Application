#include "GameSession.h"
#include "MessageSystem.h"
#include "Game.h"

GameSession::GameSession(sf::RenderWindow *appRef, DIFFICULTY difficulty, int firstMove)
	: m_AppRef(appRef)
{
	m_Gameboard = new Gameboard(appRef);
	m_Gameboard->InitializeGameboard();
	m_PlayerOne = new Player();
	m_PlayerTwo = new Computer(difficulty); 
	if(firstMove == 1)
		m_ActivePlayer = m_PlayerOne;
	else
		m_ActivePlayer = m_PlayerTwo;
}

void GameSession::Update(sf::RenderWindow *appRef, float deltaTime)
{
	if(!m_Gameboard->IsWinnerDisplaying())
	{
		//check if game should end
		if(m_Gameboard->GetWinner() != NONE) {
			EndGame(m_Gameboard->GetWinner());
			return;
		}

		//if game isn't over, get player's move
		PLAYERTYPE winner = m_Gameboard->CheckWin();
		if(winner == NONE)
		{
			if(m_ActivePlayer->Update(appRef, deltaTime, m_Gameboard)){
				SwitchPlayer();
			}
		}
	}

	m_Gameboard->Update(deltaTime);
	Render();
}

void GameSession::EndGame(PLAYERTYPE winner)
{
	//display win, reset game state
	GameMessage* msgEndGame = new GameMessage(GameMessage::STATECHANGE);
	msgEndGame->TargetState = ENDGAME;
	MessageSystem::GetSingleton()->QueueMessage(msgEndGame);

	std::cout << "Winner: " << winner << std::endl;

	m_Gameboard->ClearGameboard();
	delete m_Gameboard;
	delete m_PlayerOne;
	delete m_PlayerTwo;
}

void GameSession::Render()
{
	m_Gameboard->Render();
}

void GameSession::SwitchPlayer()
{
	if(m_ActivePlayer == m_PlayerOne) {
		m_ActivePlayer = m_PlayerTwo;
	}
	else {
		m_ActivePlayer = m_PlayerOne;
	}
}
