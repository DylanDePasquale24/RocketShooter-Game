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

//make it so you can change window size too!!!
 //MAYBE MAKE IT SHOOT AUTOMATICALLY BASED ON TIME INSTEAD OF MANUALLY DOING IT, would get rid of the shooting error
 //can make it so it shoots at certain intervals and can increase the intervals too.


//TO DO:
    //make it so enemies take damage //turn enemy red as you do (just replace it for a second with the same image but in red)
    //add the side walls and be able to be killed by then
    //add animation when your ship dies for a few seconds. 
    //make it so you can be hit by bullets (have some 2 second animation before game over screen)
    //adjust enemy speeds and stuff
    //make it so can go to full screen
    //add power ups (shield that can take a bullet),, but battleship destroys shield
        //make it so you can increase number of bullets that get shot automaticaally
        //or damage of bullets
        // 
    //make it so score is calculated and distance is calculated
    //do functionality of stats button
    //make it so aliens get stronger and harder to kill the more you go. 
    //make sure when an enemy dies you delete all the bullets and stuff
    //keep track of scores and do end screen
    //possibly add some sounds
 