#include <Game.h>
#include <random>
#include <optional>

#ifndef ASTEROID_H
#define ASTEROID_H

class Asteroid {
  private:
    float xPos, yPos;
    float dx, dy;
    sf::Texture asteroidTexture;

  public:
    int size;
    bool live; 
    sf::Sprite asteroidSprite; 

    Asteroid(int size);
    void setPositionAndVelocity();
    void update(std::vector<Asteroid*>& liveAsteroids);
    void checkCollision(std::vector<Asteroid*>& liveAsteroids); 
    static std::vector<Asteroid*> breakApart(Asteroid* asteroid); 
};
#endif //ASTEROID_H
