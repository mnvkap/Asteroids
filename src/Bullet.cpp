#include "Bullet.h"
#include "Asteroid.h"
Bullet::Bullet(int deltaX, int deltaY, float shipRotation, Game& curGame)
  : live(true), xPos(deltaX), yPos(deltaY), rotation(shipRotation), game(curGame), bulletTexture(), bulletSprite(), velocity() {
  if (!bulletTexture.loadFromFile("textures/bullet.png")) { }
  bulletSprite.setTexture(bulletTexture);
  bulletSprite.setOrigin(bulletTexture.getSize().x / 2.0f, bulletTexture.getSize().y / 2.0f);
  bulletSprite.setRotation(rotation);
  bulletSprite.setScale(Game::RESWIDTH * 0.01f / bulletTexture.getSize().x, Game::RESHEIGHT * 0.065f / bulletTexture.getSize().y);
  bulletSprite.setPosition(xPos, yPos);
  velocity = sf::Vector2f(cos((rotation - 90) * M_PI / 180) * 750.0f, sin((rotation - 90) * M_PI / 180) * 750.0f);
}

void Bullet::fire(float deltaTime) {
  bulletSprite.move(velocity * deltaTime); // Move sprite 

  // Check for wall collison 
  sf::Vector2f bulletPos = bulletSprite.getPosition(); 
  sf::FloatRect bulletSpriteBounds = bulletSprite.getLocalBounds();
  if (bulletPos.x < 0 || bulletPos.x + bulletSpriteBounds.width > game.RESWIDTH) { live = false; }
  if (bulletPos.y < 0 || bulletPos.y + bulletSpriteBounds.height > game.RESHEIGHT) { live = false; }
}

void Bullet::checkCollision(std::vector<Asteroid*>& liveAsteroids) {
  sf::FloatRect bulletBounds = bulletSprite.getGlobalBounds();
  std::vector<Asteroid*> newAsteroids;
  for (Asteroid* asteroid : liveAsteroids) {
    sf::FloatRect asteroidBounds = asteroid->asteroidSprite.getGlobalBounds();
    if (bulletBounds.intersects(asteroidBounds)) {
      live = false; // Kill the bullet
      std::vector<Asteroid*> brokenAsteroids = Asteroid::breakApart(asteroid);
      if (!brokenAsteroids.empty()) { newAsteroids.push_back(brokenAsteroids.at(0)); newAsteroids.push_back(brokenAsteroids.at(1)); }
    }
  }
  liveAsteroids.insert(liveAsteroids.end(), newAsteroids.begin(), newAsteroids.end());
}
