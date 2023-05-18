#include <Bullet.h>

Bullet::Bullet(int deltaX, int deltaY, float shipRotation, Game& curGame)
  : live(true), xPos(deltaX), yPos(deltaY), rotation(shipRotation), game(curGame), bulletTexture(), bulletSprite() {
  if (!bulletTexture.loadFromFile("textures/bullet.png")) { }
  bulletSprite.setTexture(bulletTexture);
  bulletSprite.setOrigin(bulletTexture.getSize().x / 2.0f, bulletTexture.getSize().y / 2.0f);
  bulletSprite.setPosition(xPos, yPos);
}

void Bullet::fire(sf::Clock& clock) {
  sf::Vector2f velocity(cos((bulletSprite.getRotation() - 90) * M_PI / 180) * 500.0f, sin((bulletSprite.getRotation() - 90) * M_PI / 180) * 500.0f); // Set bullet speed and direciton
  float deltaTime = clock.restart().asSeconds(); // Get time since last frame
  bulletSprite.move(velocity * deltaTime); // Move sprite 

  // Check for wall collison 
  sf::Vector2f bulletPos = bulletSprite.getPosition(); 
  sf::FloatRect bulletSpriteBounds = bulletSprite.getLocalBounds();
  if (bulletPos.x < 0 || bulletPos.x + bulletSpriteBounds.width > game.RESWIDTH) { live = false; }
  if (bulletPos.y < 0 || bulletPos.y + bulletSpriteBounds.height > game.RESHEIGHT) { live = false; }
}

