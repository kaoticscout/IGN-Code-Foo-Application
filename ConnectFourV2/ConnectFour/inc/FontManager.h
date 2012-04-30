#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class FontManager
{
public:
	sf::Font& GetFont(std::string filename);
	static FontManager* GetSingleton();
	void Shutdown();
	void DestroyAllFonts();
	void DestroyFont(std::string filename);

private:
	FontManager(){}
	std::map<std::string, sf::Font*> m_FontMap;
	static FontManager* p_Instance;
};

#endif