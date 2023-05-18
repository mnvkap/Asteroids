#include "Bullet.h"
#include "Game.h"

#ifndef SHIP_H
#define SHIP_H

class Ship {
  private:
    sf::Texture shipTexture;

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
    void move(int deltaX, int deltaY);
    Bullet* shoot(); // Returns Bullet it fires
    void takeDamage();
    void boost();
};
#endif //SHIP_H
