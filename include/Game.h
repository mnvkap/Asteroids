#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <vector>

#ifndef GAME_H
#define GAME_H

class Bullet; // Forward Decleration of Bullet
class Ship; // Forward Decleration of ship
class Game {
  private:
    int score;
    int wave;
    Ship* ship;

    sf::Clock clock;
    sf::Font asteroidFont; 
    sf::Font pressKeyFont;
    sf::Sprite background;
    sf::Sprite* shipSprite;
    sf::Texture backgroundTexture;
    sf::RenderWindow window; // Window for game to be played in 
    std::vector<sf::Text*> text; // Vector to hold text
    std::vector<Bullet*> liveBullets; // Vector to hold bullets
    void setUp(); // Used to setup game
  public:
    static const float RESHEIGHT;
    static const float RESWIDTH;

    Game();
    
    void run(); // Displays title screen
    void start();
    void stop(); 

    void cleanLiveBullets(); 
};
#endif //GAME_H
