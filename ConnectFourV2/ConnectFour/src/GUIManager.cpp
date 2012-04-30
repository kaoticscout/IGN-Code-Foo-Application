#include "GUIManager.h"
#include <iostream>
GUIManager* GUIManager::pInstance = NULL;

void GUIManager::Shutdown()
{
	ClearScreens();
	delete pInstance;
	pInstance = NULL;
}

GUIManager* GUIManager::GetSingleton()
{
  if(pInstance == NULL){
    pInstance = new GUIManager();
  }
  return pInstance;
}

void GUIManager::ClearScreens()
{
	for(std::vector<GUIScreen*>::iterator it = m_Screens.begin(); it != m_Screens.end(); ++it){
		(*it)->Shutdown();
		delete *it;
	}
	m_Screens.clear();
}

void GUIManager::PushScreen(GUIScreen* newScreen)
{
	newScreen->Startup();
	m_Screens.push_back(newScreen);
}

void GUIManager::PopScreen()
{
	if(m_Screens.size() > 0){
		m_Screens.at(m_Screens.size()-1)->Shutdown();
		delete m_Screens.at(m_Screens.size()-1);
		m_Screens.pop_back();
	}
}

void GUIManager::UpdateScreens(float deltaTime)
{
	for(std::vector<GUIScreen*>::iterator it = m_Screens.begin(); it != m_Screens.end(); ++it){
		(*it)->Update(deltaTime);
		(*it)->Render();
	}
}

void  GUIManager::Debug_PrintScreenStack()
{
}