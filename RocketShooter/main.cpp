#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

using namespace sf;
using namespace std; 



int main()
{
    Game game;
    game.Initialize();

    RenderWindow window(VideoMode(1200, 675), "Rocket Shooter", Style::Titlebar | Style::Close);
   
    Timing::StartFrame();

    while (window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

           //Space bar press
            if (event.type == sf::Event::KeyPressed && !game.GameOver() && game.HasStarted()) {
                if (event.key.code == sf::Keyboard::Space) {

                    if (!game.HasInteracted()) {
                        game.SetToInteracted();
                    }
                    game.PressSpaceKey();
                }
            }

            //mouse clicks
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
        Timing::UpdateLastFrame();
        Timing::StartFrame();
    }


    TextureManager::Clear();
    return 0;
}
