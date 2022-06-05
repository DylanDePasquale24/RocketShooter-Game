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
 //MAYBE MAKE IT SHOOT AUTOMATICALLY BASED ON TIME INSTEAD OF MANUALLY DOING IT
 //can make it so it shoots at certain intervals and can increase the intervals too.


//TO DO:
    //MAKE IT SO WAVES ALL HAPPEN FOR A CERTAIN TIME. theres a break after each wave for a bit. and you can only go onto the next wave until current enemy is killed
    // meaning new wave time doesnt start either until enemy is killed

//FOR SCORE, ADD UP ALL THE TIMES OF THE WAVES BEFORE HAND AND THE CURRENT TIME OR SOMETHING, DONT WANT THE BREAKS TO BE ACCOUNTED FOR. 

   
    
    
   
    //have distance show up in top left and have it appear on gameover screen (instead of "score" on gameover screen, make it the number of enemies killed
    //make it so can go to full screen
    //make it so bullets shoot automatically (just very infrequently so you still have to try to aim) (and space or mouse click to go up)
    //Fix up speed of rocket falling. Make it slow at first and then increase in speed, not just linear. Kinda make it like flappy bird
    //make it so rocket can be killed by enemy bullets and all asteroids
        //do an animation for rocket dying(turn red for one second)  **OPTIONAL**

    // check for memory leaks and see cpu usage. Try to make performance adjustments. 
    //need to add a bunch of stuff to the reset (like timebtwn Asteroids and enemy bullets, etc.



//allow rocket to be killed last because you want to figure out game balancing before you can be killed
    //add the side walls and be able to be killed by them
    //add animation when your ship dies for a few seconds. 
    //make it so you can be hit by bullets (have some 2 second animation before game over screen)





//seperate all your inheritance classes into seperate files, instead of just one