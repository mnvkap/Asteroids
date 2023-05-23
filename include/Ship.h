#include "Bullet.h"
#include "Game.h"
#include <SFML/Audio.hpp>

#ifndef SHIP_H
#define SHIP_H

class Ship {
  private:
    sf::Texture thrusterTexture;
    sf::Sprite thrusterSprite;
    sf::Texture shipTexture;
    sf::Vector2f velocity{0.0f, 0.0f};  // Declare velocity here
    
    bool showThruster; 
    float rotation = 0.0f;  // Declare rotation here
    const float ACCELERATION = 800.0f;
    const float MAX_SPEED = 400.0f;
    const float ROTATION_SPEED = 200.0f;
    const float DRAG = 0.85f;

    float getMagnitude(sf::Vector2f vector);
    sf::Vector2f normalize(sf::Vector2f vector);
    sf::SoundBuffer fireBuffer;
    sf::SoundBuffer shipEngineBuffer;
    sf::Sound shipEngineSound;
    sf::Sound fireSound;
  public:
    // Coordinates of ship
    int xPos;
    int yPos;
    int health;
    int boostTimer;
    Game& game;
    sf::Sprite shipSprite;

    // Constructor
    Ship(int centerX, int centerY, Game& curGame);
    // Move sprite on screen
    void handleInput(float deltaTime);
    void applyDrag(float deltaTime);
    void wrapAroundScreen();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    Bullet* shoot(); // Returns Bullet it fires
    void checkCollision(std::vector<Asteroid*>& liveAsteroids); 
    void boost();
};
#endif //SHIP_H
