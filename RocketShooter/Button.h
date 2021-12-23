#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include "TextureManager.h"

using std::string;
using std::function;

class Button : public sf::Sprite
{

	sf::Vector2f position;
	function<void(void)> clickFunction;

public:
	Button();
	Button(sf::Vector2f _position, string textureName, function<void(void)> _clickFunction);

	void OnClick();
	bool WasClickedAt(sf::Vector2f clickedPos);

};

