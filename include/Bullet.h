#include <Game.h>

#ifndef BULLET_H
#define BULLET_H

class Bullet {
  private:
    sf::Texture bulletTexture;
    sf::Vector2f velocity;
  public:
    // Coordinates of Bullet 
    int xPos;
    int yPos;
    float rotation;
    bool live; // Tracks state of bullet
    Game& game;
    sf::Sprite bulletSprite; 

    Bullet(int deltaX, int deltaY, float shipRotation, Game& curGame);
    // Start the movement of the bullet
    void fire(float deltaTime);
};
#endif //BULLET_H
