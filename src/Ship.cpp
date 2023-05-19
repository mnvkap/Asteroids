#include "Ship.h"
#ifndef PI
#define PI 3.14159265358979323846
#endif

Ship::Ship(int centerX, int centerY, Game& curGame) 
  : health(99), boostTimer(5), xPos(centerX), yPos(centerY), game(curGame), shipSprite() {
  if (!shipTexture.loadFromFile("textures/ship.png")) { }
  shipSprite.setTexture(shipTexture);
  shipSprite.setOrigin(shipTexture.getSize().x / 2.0f, shipTexture.getSize().y / 2.0f);
  shipSprite.setScale(Game::RESWIDTH * 0.07f / shipTexture.getSize().x, Game::RESHEIGHT * 0.07f / shipTexture.getSize().y);
  shipSprite.setPosition(Game::RESWIDTH / 2, Game::RESHEIGHT / 2);

  // Load sound 
  if (!fireBuffer.loadFromFile("sounds/fire.ogg")) { }
  fireSound = sf::Sound(fireBuffer);
}

void Ship::handleInput(float deltaTime) {
  if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) ) {
    sf::Vector2f direction(std::sinf(rotation * PI / 180.0f), -std::cosf(rotation * PI / 180.0f));
    velocity += direction * ACCELERATION * deltaTime;
    if (getMagnitude(velocity) > MAX_SPEED) { velocity = normalize(velocity) * MAX_SPEED; }
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { rotation -= ROTATION_SPEED * deltaTime; }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)|| sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { rotation += ROTATION_SPEED * deltaTime; }
}

void Ship::applyDrag(float deltaTime) { velocity *= std::powf(DRAG, deltaTime); }

void Ship::wrapAroundScreen() {
  if (shipSprite.getPosition().x < 0) { shipSprite.setPosition(Game::RESWIDTH, shipSprite.getPosition().y); }
  else if (shipSprite.getPosition().x > Game::RESWIDTH) { shipSprite.setPosition(0, shipSprite.getPosition().y); }

  if (shipSprite.getPosition().y < 0) { shipSprite.setPosition(shipSprite.getPosition().x, Game::RESHEIGHT); }
  else if (shipSprite.getPosition().y > Game::RESHEIGHT) { shipSprite.setPosition(shipSprite.getPosition().x, 0); }
}

float Ship::getMagnitude(sf::Vector2f vector) { return std::sqrt(vector.x * vector.x + vector.y * vector.y); }

sf::Vector2f Ship::normalize(sf::Vector2f vector) {
  float magnitude = getMagnitude(vector);
  if (magnitude > 0) { return vector / magnitude; }
  return vector;
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

  // Play sound effect
  fireSound.play();

  return bullet;
}

void Ship::takeDamage() {
  health -= 33; 
}
