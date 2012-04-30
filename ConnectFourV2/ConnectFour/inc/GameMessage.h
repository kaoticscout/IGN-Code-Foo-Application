#ifndef GAME_MESSAGE_H
#define GAME_MESSAGE_H

enum GAMESTATE;
enum DIFFICULTY;

class GameMessage
{
public:

	// currently using enum for message type
	enum MSG_TYPE
	{
		STATECHANGE
	};

	GameMessage(MSG_TYPE msgType)
		: TimeDelay(0), MsgType(msgType)
	{}

	float TimeDelay; //in seconds		
	int firstMove;
	DIFFICULTY difficulty;
	GAMESTATE TargetState;
	MSG_TYPE MsgType;
};

#endif