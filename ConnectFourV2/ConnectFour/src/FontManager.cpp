#include "FontManager.h"
#include <iostream>
FontManager* FontManager::p_Instance = NULL;

void FontManager::Shutdown()
{
	DestroyAllFonts();
	delete p_Instance;
}

void FontManager::DestroyAllFonts()
{
	//clear all memory from the image manager
	for(std::map<std::string, sf::Font*>::iterator it = m_FontMap.begin(); it != m_FontMap.end(); ++it){
		delete it->second; 
	}
	m_FontMap.clear();
}

void FontManager::DestroyFont(std::string filename)
{
	//clear a specific image from image manager if it is never going to be used again
	std::map<std::string, sf::Font*>::iterator it;
	it = m_FontMap.find(filename);
	if(it != m_FontMap.end()){
		delete it->second;
		m_FontMap.erase(it);
	}
}

sf::Font& FontManager::GetFont(std::string filename)
{    
	sf::Font* Font = new sf::Font();
	std::map<std::string, sf::Font*>::iterator it;
	it = m_FontMap.find(filename);
	//See if image already exists in image map
	if(it != m_FontMap.end()){
		Font = it->second;
	}
	//otherwise, create a new image and put it in the image map
	else{
		if(Font->LoadFromFile("media/fonts/" + filename)){
			m_FontMap.insert(std::pair<std::string, sf::Font*>(filename, Font));
		}
		else {
			std::cout << "Could not find font(\"" << filename << "\")" << std::endl;
		}
	}

	return (*Font);
}

FontManager* FontManager::GetSingleton()
{
  if(p_Instance == NULL){
	  p_Instance = new FontManager();
  }
  return p_Instance;
}