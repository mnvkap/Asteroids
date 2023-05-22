#include "Ship.h"
#ifndef PI
#define PI 3.14159265358979323846
#endif

Ship::Ship(int centerX, int centerY, Game& curGame) 
  : health(99), boostTimer(5), xPos(centerX), yPos(centerY), game(curGame), shipSprite(), showThruster(false) {
  if (!shipTexture.loadFromFile("textures/ship.png")) { }
  if (!thrusterTexture.loadFromFile("textures/thruster.png")) { }
  shipSprite.setTexture(shipTexture);
  shipSprite.setOrigin(shipTexture.getSize().x / 2.0f, shipTexture.getSize().y / 2.0f);
  shipSprite.setScale(Game::RESWIDTH * 0.07f / shipTexture.getSize().x, Game::RESHEIGHT * 0.07f / shipTexture.getSize().y);
  shipSprite.setPosition(Game::RESWIDTH / 2, Game::RESHEIGHT / 2);

  thrusterSprite.setTexture(thrusterTexture);
  thrusterSprite.setOrigin(thrusterTexture.getSize().x / 2.0f, thrusterTexture.getSize().y / 2.0f);
  thrusterSprite.setScale(Game::RESWIDTH * 0.02f / thrusterTexture.getSize().x, Game::RESHEIGHT * 0.06f / thrusterTexture.getSize().y);

  // Set thruster sprite position relative to the ship sprite position
  sf::Vector2f shipPosition = shipSprite.getPosition();
  float shipHeight = shipSprite.getGlobalBounds().height;
  thrusterSprite.setPosition(shipPosition.x, shipPosition.y + shipHeight / 2.0f);

  // Load sound 
  if (!fireBuffer.loadFromFile("sounds/fire.ogg")) { }
  if (!shipEngineBuffer.loadFromFile("sounds/engine.wav")) { }
  shipEngineSound = sf::Sound(shipEngineBuffer);
  fireSound = sf::Sound(fireBuffer);
}

void Ship::update(float deltaTime) {
  handleInput(deltaTime);
  applyDrag(deltaTime);
  wrapAroundScreen();
  shipSprite.move(velocity * deltaTime);
  shipSprite.setRotation(rotation);

  // Calculate new position of the thruster
  sf::Vector2f shipPosition = shipSprite.getPosition();
  float shipRotation = shipSprite.getRotation(); // Get the ship's rotation

  // Convert the ship's rotation to radians
  float shipRotationInRadians = shipRotation * PI / 180.0f;

  // Calculate the offset position of the thruster based on the ship's rotation
  float offsetX = std::sin(shipRotationInRadians) * shipSprite.getGlobalBounds().height / 2.0f;
  float offsetY = std::cos(shipRotationInRadians) * shipSprite.getGlobalBounds().height / 2.0f;

  // Set thruster sprite position relative to the ship sprite position and rotation
  thrusterSprite.setPosition(shipPosition.x - offsetX, shipPosition.y + offsetY);
  thrusterSprite.setRotation(rotation);
}

void Ship::handleInput(float deltaTime) {
  if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) ) {
    sf::Vector2f direction(std::sinf(rotation * PI / 180.0f), -std::cosf(rotation * PI / 180.0f));
    velocity += direction * ACCELERATION * deltaTime;
    showThruster = true;

    // Only start sound if it is not already playing.
    if (shipEngineSound.getStatus() != sf::Sound::Playing) { shipEngineSound.play(); }
    if (getMagnitude(velocity) > MAX_SPEED) { velocity = normalize(velocity) * MAX_SPEED; }
  }
  else { showThruster = false; shipEngineSound.stop(); }
  
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { rotation -= ROTATION_SPEED * deltaTime; }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)|| sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { rotation += ROTATION_SPEED * deltaTime; }
}

void Ship::applyDrag(float deltaTime) { velocity *= std::powf(DRAG, deltaTime); }

void Ship::wrapAroundScreen() {
  // get the width and height of the sprite
  float spriteWidth = shipSprite.getGlobalBounds().width;
  float spriteHeight = shipSprite.getGlobalBounds().height;

  if (shipSprite.getPosition().x < -spriteWidth) { shipSprite.setPosition(Game::RESWIDTH, shipSprite.getPosition().y); }
  else if (shipSprite.getPosition().x > Game::RESWIDTH) { shipSprite.setPosition(-spriteWidth, shipSprite.getPosition().y); }

  if (shipSprite.getPosition().y < -spriteHeight) { shipSprite.setPosition(shipSprite.getPosition().x, Game::RESHEIGHT); }
  else if (shipSprite.getPosition().y > Game::RESHEIGHT) { shipSprite.setPosition(shipSprite.getPosition().x, -spriteHeight); }
}

float Ship::getMagnitude(sf::Vector2f vector) { return std::sqrt(vector.x * vector.x + vector.y * vector.y); }

sf::Vector2f Ship::normalize(sf::Vector2f vector) {
  float magnitude = getMagnitude(vector);
  if (magnitude > 0) { return vector / magnitude; }
  return vector;
}

void Ship::draw(sf::RenderWindow& window) { 
  window.draw(shipSprite); 
  if (showThruster) { window.draw(thrusterSprite); }
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
