#include <Game.h>
#include <random>

#ifndef ASTEROID_H
#define ASTEROID_H

class Asteroid {
  private:
    float xPos, yPos;
    float dx, dy;
    sf::Texture asteroidTexture;

  public:
    int size;
    bool live; // Tracks state of asteroid
    sf::Sprite asteroidSprite; 

    Asteroid();
    void setPositionAndVelocity();
    void update();
};
#endif //ASTEROID_H
