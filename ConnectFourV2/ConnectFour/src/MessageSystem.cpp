#include "MessageSystem.h"
#include "MessageListener.h"

MessageSystem* MessageSystem::p_Instance =  NULL;


MessageSystem* MessageSystem::GetSingleton()
{
	if(p_Instance == NULL){
		p_Instance = new MessageSystem();
	}
	return p_Instance;
}

void MessageSystem::Shutdown()
{
	ClearMessages();
	ClearListeners();
	delete p_Instance;
	p_Instance = NULL;
}

void MessageSystem::Update(float deltaTime)
{
	//read all messages back to front, so messages can be removed
	for(std::vector<GameMessage*>::iterator it = m_MsgQueue.begin(); it != m_MsgQueue.end(); ++it)
	{
		GameMessage* msg = *it;
		if(msg != NULL && msg->TimeDelay <= 0)
		{
			//process message by sending a reference to all listeners
			for(int listCounter = 0; listCounter < m_Listeners.size(); ++listCounter){
				m_Listeners.at(listCounter)->ProcessMessage(msg);
			}
		}
	}

	m_MsgQueue.clear();
}

void MessageSystem::RemoveListener(MessageListener* msgListener)
{
	for(std::vector<MessageListener*>::iterator it = m_Listeners.begin(); it != m_Listeners.end(); ++it)
	{
		if((*it) == msgListener)
		{
			m_Listeners.erase(it);
			break;
		}
	}
}

void MessageSystem::QueueMessage(GameMessage* msg)
{ 
	m_MsgQueue.push_back(msg);
}

void MessageSystem::ClearMessages() 
{
	for(std::vector<GameMessage*>::iterator it = m_MsgQueue.begin(); it != m_MsgQueue.end(); ++it){
		delete *it;
	}
	m_MsgQueue.clear();
}