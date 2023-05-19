#ifndef ASTEROID_H
#define ASTEROID_H

class Asteroid {
  private:
    sf::Texture asteroidTexture;
    sf::Vector2f velocity;
  public:
    // Coordinates of Asteroid
    int xPos;
    int yPos;
    int size;
    float rotation;
    bool live; // Tracks state of asteroid

    sf::Sprite asteroidSprite; 

    Asteroid(int x, int y);
    void startMove(float deltaTime);
}
#endif //ASTEROID_H
