#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <Ship.h>

#ifndef GAME_H
#define GAME_H

class Game {
  private:
    sf::RenderWindow window; // Window for game to be played in 
  
    Ship* ship;
    int score;
    int wave;

    sf::Font asteroidFont; 
    sf::Font regularTextFont;
    sf::Font pressKeyFont;
    std::vector<sf::Text*> text; // Vector to hold text
    void setUpText(); // Used to create text objects
  public:
    static const float RESHEIGHT;
    static const float RESWIDTH;

    Game();
    
    void run(); // Displays title screen
    void start();
    void stop(); 
};
#endif //GAME_H
