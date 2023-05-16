#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <Ship.h>

#ifndef GAME_H
#define GAME_H

class Game {
  private:
    // Window for game to be played in 
    sf::RenderWindow window;
    
    // Game object
    Ship* ship;

    // Vector to hold text
    std::vector<sf::Text*> text; 

    int score;
    int wave;

    // Create font objects
    sf::Font asteroidFont; 
    sf::Font regularTextFont;
    void setUpText();
  public:
    static const float RESHEIGHT;
    static const float RESWIDTH;

    Game();
    
    // Method to start Game
    void run();
    void stop(); 
};
#endif //GAME_H
