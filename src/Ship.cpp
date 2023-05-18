#include "Ship.h"

Ship::Ship(int centerX, int centerY, Game& curGame) 
  : health(99), boostTimer(5), xPos(centerX), yPos(centerY), game(curGame), shipSprite() {
  if (!shipTexture.loadFromFile("textures/ship.png")) { }
  shipSprite.setTexture(shipTexture);
  shipSprite.setScale(Game::RESWIDTH * 0.07f / shipTexture.getSize().x, Game::RESHEIGHT * 0.07f / shipTexture.getSize().y);
}

void Ship::move(int deltaX, int deltaY) {
  xPos = deltaX;
  yPos = deltaY;
}

Bullet* Ship::shoot() {
  sf::Vector2f shipPos = shipSprite.getPosition(); // Get the ship's position
  float shipRotation = shipSprite.getRotation(); // Get the ship's rotation

  // Calculate the bullet's initial position based on the ship's position, rotation, and size
  float shipSpriteWidth = shipSprite.getLocalBounds().width;
  float shipSpriteHeight = shipSprite.getLocalBounds().height;
  float offsetX = shipSpriteWidth / 2.0f * cos((shipRotation - 90) * M_PI / 180);
  float offsetY = shipSpriteHeight / 2.0f * sin((shipRotation - 90) * M_PI / 180);
  Bullet* bullet = new Bullet(shipPos.x, shipPos.y, shipRotation, game);
  return bullet;
}

void Ship::takeDamage() {
  health -= 33; 
}

  

