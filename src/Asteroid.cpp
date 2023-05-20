#include <Asteroid.h>
int RESWIDTH = static_cast<int>(Game::RESWIDTH);
int RESHEIGHT = static_cast<int>(Game::RESHEIGHT);
Asteroid::Asteroid() 
  : xPos(rand() % RESWIDTH), yPos(rand() % RESHEIGHT), dx(((rand() % 5) - 2) / 30.0f), dy(((rand() % 5) - 2) / 30.0f) {
    if (!asteroidTexture.loadFromFile("textures/BigAsteroid.png")) { }
    asteroidSprite.setTexture(asteroidTexture);
    asteroidSprite.setScale(Game::RESWIDTH * 0.1f / asteroidTexture.getSize().x, Game::RESHEIGHT * 0.1f / asteroidTexture.getSize().y);
    asteroidSprite.setPosition(xPos, yPos);
}

void Asteroid::update() {
    xPos += dx;
    yPos += dy;
    asteroidSprite.setPosition(xPos, yPos);
    if (asteroidSprite.getPosition().x < 0 || asteroidSprite.getPosition().x > Game::RESWIDTH) { dx = -dx; }
    if (asteroidSprite.getPosition().y < 0 || asteroidSprite.getPosition().y > Game::RESHEIGHT) { dy = -dy; }
}
