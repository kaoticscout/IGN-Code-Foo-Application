#ifndef GAMEBOARD_H
#define GAMEBORAD_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Gamepiece.h"
#include "ImageManager.h"

/*
enum PLAYERWIN
{
	NOWIN = 0,
	PLAYERONEWIN,
	PLAYERTWOWIN,
	TIE
};
*/

static const int Width = 7;
static const int Height = 6;

class Gameboard
{

public:
	Gameboard(sf::RenderWindow* const appRef);
	
	void InitializeGameboard();
	void ClearGameboard();

	bool PlaceGamepiece(int columnNumber, PLAYERTYPE playerType, bool hover = false);
	sf::Vector2f GetGamepieceLocation(const int row, const int column);
	
	const int GetColumnNumber(int mouseX);
	const int GetValidRow(const int columnNumber);

	Gameboard ApplyMove(Gameboard gameboard, int column);
	std::vector<int> GetMoves();
		
	void Update(float deltaTime);
	void Render();
	PLAYERTYPE CheckWin();

	inline PLAYERTYPE GetWinner() const { return m_Winner; }
	inline bool IsGamepieceDropping() const { return m_IsDropping; }
	inline bool IsWinnerDisplaying() const { return m_DisplayingWinner; }
	inline std::vector<std::vector<Gamepiece*>> GetGameboardState() const { return	m_GameboardState; }

private:
	static const int VertPadding = 80;
	static const int VertSpacing = 11;
	static const int HorizPadding = 163;
	static const int HorizSpacing = 9;
	static const int ImgWidth = 54;
	static const int ImgHeight = 54;
	static const int DefaultDisplayTicks = 2500; //change this to time
	static const int FallAmt = 4;

	bool			m_IsDropping;	
	float			m_FallLocation;
	sf::Sprite*		m_DroppingSprite;

	bool			m_DisplayingWinner;
	float			m_DisplayTime; //in milliseconds
	sf::Sprite*		m_WinningPieces[4];

	PLAYERTYPE		m_Winner;

	bool CheckTie();
	PLAYERTYPE CheckWinAllDirections();

	sf::Sprite*								m_HeaderSprite;
	std::vector<std::vector<sf::Sprite>>	m_GameboardSprites;
	std::vector<std::vector<Gamepiece*>>	m_GameboardState;
	sf::RenderWindow*						m_AppRef;
	sf::Sprite*								m_GameboardBGSprite;
	sf::Sprite*								m_GameboardSprite;
};

#endif