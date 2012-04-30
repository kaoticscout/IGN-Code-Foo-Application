#include "ImageManager.h"
#include <iostream>
ImageManager* ImageManager::p_Instance = NULL;

void ImageManager::Shutdown()
{
	DestroyAllImages();
	delete p_Instance;
}

void ImageManager::DestroyAllImages()
{
	//clear all memory from the image manager
	for(std::map<std::string, sf::Image*>::iterator it = m_ImageMap.begin(); it != m_ImageMap.end(); ++it){
		delete it->second; 
	}
	m_ImageMap.clear();
}

void ImageManager::DestroyImage(std::string filename)
{
	//clear a specific image from image manager if it is never going to be used again
	std::map<std::string, sf::Image*>::iterator it;
	it = m_ImageMap.find(filename);
	if(it != m_ImageMap.end()){
		delete it->second;
		m_ImageMap.erase(it);
	}
}

sf::Image& ImageManager::GetImage(std::string filename)
{    
	sf::Image* Image = new sf::Image();
	std::map<std::string, sf::Image*>::iterator it;
	it = m_ImageMap.find(filename);
	//See if image already exists in image map
	if(it != m_ImageMap.end()){
		Image = it->second;
	}
	//otherwise, create a new image and put it in the image map
	else{
		if(Image->LoadFromFile("media/" + filename)){
			m_ImageMap.insert(std::pair<std::string, sf::Image*>(filename, Image));
		}
		else
		{
			std::cout << "Could not find image(\"" << filename << "\")" << std::endl;
		}
	}

	return (*Image);
}

ImageManager* ImageManager::GetSingleton()
{
  if(p_Instance == NULL){
	  p_Instance = new ImageManager();
  }
  return p_Instance;
}