#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <vector>

#ifndef GAME_H
#define GAME_H

class Bullet; // Forward Decleration of Bullet
class Ship; // Forward Decleration of ship
class Asteroid; // Forward Decleration of asteroid
class Game {
  private:
    int score;
    int wave;
    Ship* ship;

    sf::Clock clock;    
    sf::Clock asteroidSpawnTimer;
    sf::Time timeToNextSpawn;
    sf::Font asteroidFont; 
    sf::Font pressKeyFont;
    sf::Text* scoreText; 
    sf::Sprite background;
    sf::Sprite* shipSprite;
    sf::Texture backgroundTexture;
    sf::RenderWindow window; // Window for game to be played in 
    std::vector<sf::Text*> text; // Vector to hold text
    std::vector<Bullet*> liveBullets; // Vector to hold bullets
  public:
    std::vector<Asteroid*> liveAsteroids; // Vector to hold asteroids
    static constexpr float RESHEIGHT = 1080;
    static constexpr float RESWIDTH  = 1920;

    Game();
    
    void run(); 
    void start();
    void setUp(); 
    void updateScore(); 
    void endGame(); 
    void restartGame();

    void cleanEntities(); 
    void cleanGame();
};
#endif //GAME_H
