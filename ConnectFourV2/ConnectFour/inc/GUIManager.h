#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <vector>
#include "GUIScreen.h"

#include "Screen_MainMenu.h"
#include "Screen_GameOptions.h"
#include "Screen_GamePlay.h"
#include "Screen_EndGame.h"

class GUIManager
{
public:
	void PushScreen(GUIScreen* newScreen);
	void PopScreen();
	void ClearScreens();
	void UpdateScreens(float deltaTime);
	void Debug_PrintScreenStack();

	static GUIManager* GetSingleton();
	void Shutdown();

private:
	GUIManager(){}
	std::vector<GUIScreen*> m_Screens;
	static GUIManager* pInstance;
};

#endif