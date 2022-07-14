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
    }


    TextureManager::Clear();
    return 0;
}



//TO DO:

    //make it so rocket can be killed by enemy bullets and all asteroids
        //make sure the asteroids are circular and don't kill the rocket if it doesnt fully contact it.. NO WHITE SPACE


    // check for memory leaks and see cpu usage. Try to make performance adjustments. 

//Fix up speed of rocket falling. Make it slow at first and then increase in speed, not just linear. Kinda make it like flappy bird

//TEST YOUR PROGRAM IN THE COMMAND LINE WITH COMMAND LINE COMPILING. 