#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class ImageManager
{
public:
	sf::Image& GetImage(std::string filename);
	static ImageManager* GetSingleton();
	void Shutdown();
	void DestroyAllImages();
	void DestroyImage(std::string filename);

private:
	ImageManager(){}
	std::map<std::string, sf::Image*> m_ImageMap;
	static ImageManager* p_Instance;
};

#endif