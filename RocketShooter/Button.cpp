#include "Button.h"

Button::Button() {

}
Button::Button(sf::Vector2f _position, string textureName, function<void(void)> _clickFunction) {
	setTexture(TextureManager::GetTexture(textureName));
	setPosition(_position);
	clickFunction = _clickFunction;
}

void Button::OnClick() {
	clickFunction();
}
bool Button::WasClickedAt(sf::Vector2f clickedPos) {
	if (getGlobalBounds().contains(clickedPos)) {
		return true;
	}
	return false;
}