#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <string>
using std::unordered_map;
using std::string;


class TextureManager
{

	static unordered_map<string, sf::Texture> textures;

public:
	static void SetOriginToCenter(sf::Sprite& sprite);
	static sf::Texture& GetTexture(string textureName);
	static void Clear(); 


private:
	static void LoadTexture(string filename);
};


