#include "TextureManager.h"


unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::SetOriginToCenter(sf::Sprite& sprite) {

	sf::FloatRect rect = sprite.getLocalBounds();
	sprite.setOrigin(rect.width / 2, rect.height / 2);
}
sf::Texture& TextureManager::GetTexture(string textureName) {

	if (textures.find(textureName) == textures.end()) { 
		LoadTexture(textureName);
	}

	return textures[textureName];
}
void TextureManager::Clear() {
	textures.clear();    
}

void TextureManager::LoadTexture(string filename) {
	string path = "Images/";
	path += filename + ".png";

	textures[filename].loadFromFile(path);  
}
