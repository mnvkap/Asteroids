#include "Game.h"
#include "Ship.h"
#include "Bullet.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const float Game::RESHEIGHT = 1080;
const float Game::RESWIDTH  = 1920;
const float FRICTION = 0.1f;    // Friction coefficent
const float MAX_VELOCITY = 1.5f; // Maximum velocity for the Sprite
const float ACCELERATION = 0.01f;
const float ROTATION_SPEED = 0.1f;
Ship* ship;

Game::Game() 
  : window(sf::VideoMode(RESWIDTH, RESHEIGHT), "Asteroids"), clock() { 
  setUp();
}

// This method contains the game loop
void Game::start() {
  window.clear(); 

  // Instantiate Ship Object 
  ship = new Ship(RESWIDTH/2, RESHEIGHT/2, *this);
  Bullet* newBullet = nullptr; // Created for shoot func
  // Create our background
  sf::Sprite background(starPattern);
  background.setTextureRect(sf::IntRect(0, 0, RESWIDTH, RESHEIGHT));
  sf::Vector2f velocity(0.0f, 0.0f); 

  // Create Ship Sprite
  sf::Sprite* shipSprite = &ship->shipSprite;
  float shipSpriteWidth = shipSprite->getLocalBounds().width;
  float shipSpriteHeight = shipSprite->getLocalBounds().height;
  shipSprite->setOrigin(shipSpriteWidth / 2, shipSpriteHeight / 2);
  shipSprite->setPosition(RESWIDTH / 2, RESHEIGHT / 2);

  window.draw(background);
  window.draw(*shipSprite);
  window.display();

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed) { return; }
      if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
        newBullet = ship->shoot(); 
        liveBullets.push_back(newBullet); 
      }
    }

    velocity.x *= (1.0f - FRICTION); // Apply friction
    velocity.y *= (1.0f - FRICTION);

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ) {
      velocity.x += ACCELERATION * cos((shipSprite->getRotation() - 90) * M_PI / 180);
      velocity.y += ACCELERATION * sin((shipSprite->getRotation() - 90) * M_PI / 180);
    }
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ) {
      velocity.x -= ACCELERATION * cos((shipSprite->getRotation() - 90) * M_PI / 180);
      velocity.y -= ACCELERATION * sin((shipSprite->getRotation() - 90) * M_PI / 180);
    }
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ) {
      shipSprite->rotate(-ROTATION_SPEED);
    }
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ) {
      shipSprite->rotate(ROTATION_SPEED);
    }

    if (velocity.x > MAX_VELOCITY) { velocity.x = MAX_VELOCITY; }
    else if (velocity.x < -MAX_VELOCITY) { velocity.x = -MAX_VELOCITY; }
    if (velocity.y > MAX_VELOCITY) { velocity.y = MAX_VELOCITY; }
    else if (velocity.y < -MAX_VELOCITY) { velocity.y = -MAX_VELOCITY; }

    shipSprite->move(velocity); // Update ship location 
    for (Bullet* bullet : liveBullets) { bullet->fire(clock); }
    clock.restart(); // Reset clock 

    // Wrap around screen edges
    if (shipSprite->getPosition().x < 0) { shipSprite->setPosition(RESWIDTH, shipSprite->getPosition().y); }
    else if (shipSprite->getPosition().x > RESWIDTH) { shipSprite->setPosition(0, shipSprite->getPosition().y); }
    if (shipSprite->getPosition().y < 0) { shipSprite->setPosition(shipSprite->getPosition().x, RESHEIGHT); }
    else if (shipSprite->getPosition().y > RESHEIGHT) { shipSprite->setPosition(shipSprite->getPosition().x, 0); }

    window.clear();
    window.draw(background);
    window.draw(*shipSprite);

    for (Bullet* bullet : liveBullets) { window.draw(bullet->bulletSprite); }

    window.display();

    // Clean up liveBullets
    for (auto it = liveBullets.begin(); it != liveBullets.end(); /* no increment here */) {
        if (!(*it)->live) {
            delete *it; // delete the Bullet object
            it = liveBullets.erase(it); // erase returns the new iterator
        } else {
            ++it; // only increment if we didn't erase
        }
    }
  }
}
// This method will be called to initiate the game
void Game::run() {
  // Create our background
  sf::Sprite background(starPattern);
  background.setTextureRect(sf::IntRect(0, 0, RESWIDTH, RESHEIGHT));
  for(auto textObj: text) { window.draw(*textObj); } // We draw our text objects on the screen

  bool visible = true; // Used to blink press any key
  sf::Clock clock; 
  float blinkInterval = 0.5f; 

  bool startGame = false; 
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) { return; }
      else if (event.type == sf::Event::KeyPressed) { startGame = true; }
    }

    if (clock.getElapsedTime().asSeconds() >= blinkInterval) {
      visible = !visible;
      if (visible) { text.back()->setFillColor(sf::Color(255, 255, 255, 0)); }
      else { text.back()->setFillColor(sf::Color(255, 255, 255, 255)); }

      // Update screen
      window.clear(); 
      window.draw(background);
      for(auto textObj: text) { window.draw(*textObj); } // We draw our text objects on the screen
      window.display();
      clock.restart(); // Restart the clock

      if (startGame) { break; }
    }
  }

  start();
}

// This method is used to set up the title screen, and set textures/fonts for gameplay
void Game::setUp() {
  if (!asteroidFont.loadFromFile("fonts/nasalization-rg.otf")) { }
  if (!regularTextFont.loadFromFile("fonts/nocontinue.ttf")) { }
  if (!pressKeyFont.loadFromFile("fonts/astronboy.otf")) { }
  if (starPattern.loadFromFile("textures/repeatStars.png")) { starPattern.setRepeated(true); }

  // Create text objects
  sf::Text* asteroidText = new sf::Text;
  sf::Text* pressAnyKeyText = new sf::Text;

  // Set Asteroids text
  asteroidText->setString("ASTEROIDS");
  asteroidText->setFont(asteroidFont);
  asteroidText->setCharacterSize((int)(.085 *(RESHEIGHT + RESWIDTH)));
  asteroidText->setFillColor(sf::Color::White);
  sf::FloatRect asteroidBounds = asteroidText->getLocalBounds(); // Used to calculate placement of text
  asteroidText->setOrigin(asteroidBounds.left + asteroidBounds.width / 2.0f, asteroidBounds.top + asteroidBounds.height / 2.0f); // Set the origin to the center of the text
  asteroidText->setPosition(RESWIDTH / 2.0f, 150);

  // Set pressAnyKeyText
  pressAnyKeyText->setString("PRESS ANY KEY TO PLAY");
  pressAnyKeyText->setFont(pressKeyFont);
  pressAnyKeyText->setCharacterSize((int)(.05 *(RESHEIGHT + RESWIDTH)));
  pressAnyKeyText->setFillColor(sf::Color::White);
  sf::FloatRect pressAnyKeyTextBounds = pressAnyKeyText->getLocalBounds(); // Used to calculate placement of text
  pressAnyKeyText->setOrigin(pressAnyKeyTextBounds.left + pressAnyKeyTextBounds.width / 2.0f, pressAnyKeyTextBounds.top + pressAnyKeyTextBounds.height / 2.0f); // Set the origin to the center of the text
  pressAnyKeyText->setPosition(RESWIDTH / 2.0f, RESHEIGHT - 100);

  text.push_back(asteroidText);
  text.push_back(pressAnyKeyText);
}
