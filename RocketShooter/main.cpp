#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

using namespace sf;
using namespace std;

int main()
{
    Game game;
    game.Initialize();

    RenderWindow window(VideoMode(1200, 675), "Rocket Shooter");

    while (window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

           
            if (event.type == sf::Event::KeyPressed && !game.GameOver()) {
                if (event.key.code == sf::Keyboard::Space) {
                    game.SetToInteracted();
                    game.PressSpaceKey();
                }
            }

            //check mouse clicks only if game is over or if a game hasn't been played yet (homescreen)
            if (game.GameOver() || !game.HasStarted()) {
                if (event.type == sf::Event::MouseButtonPressed) {

                    Vector2f mousePosition(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
                    game.CheckButtonClicksAt(mousePosition);
                }
            }
                
        }

        if (!game.GameOver() && game.HasStarted()) {
            game.Update();
        }
        
        window.clear();
        game.Draw(window);
        window.display();
    }


    TextureManager::Clear();
    return 0;
}

