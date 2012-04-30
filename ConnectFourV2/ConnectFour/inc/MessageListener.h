#ifndef MESSAGELISTENER_H
#define MESSAGELISTENER_H

class GameMessage;

class MessageListener
{
public:
	virtual GameMessage* ProcessMessage(GameMessage* msg){ return NULL; }
};


#endif