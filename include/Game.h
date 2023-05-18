#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <vector>

#ifndef GAME_H
#define GAME_H

class Bullet; // Forward Decleration of Bullet
class Game {
  private:
    sf::RenderWindow window; // Window for game to be played in 
  
    int score;
    int wave;

    sf::Clock clock;
    sf::Font asteroidFont; 
    sf::Font regularTextFont;
    sf::Font pressKeyFont;
    sf::Texture starPattern;
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

    void fireBullet(Bullet* bullet); 
};
#endif //GAME_H
