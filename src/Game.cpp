#include "Game.h"
#include "Ship.h"
#include "Bullet.h"
#include "Asteroid.h"


Game::Game() 
  : window(sf::VideoMode(RESWIDTH, RESHEIGHT), "Asteroids"), clock(), background() { 
  setUp();
}

// This method contains the game loop
void Game::start() {

  liveAsteroids.push_back(new Asteroid()); 
  liveAsteroids.push_back(new Asteroid()); 
  liveAsteroids.push_back(new Asteroid()); 
  liveAsteroids.push_back(new Asteroid()); 

  window.clear(); 
  window.draw(background);
  window.display();

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed) { return; }
      if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
        Bullet* newBullet = ship->shoot(); 
        liveBullets.push_back(newBullet); 
      }
    }
    float deltaTime = clock.restart().asSeconds(); // Restart and get elapsed time
    for (Bullet* bullet : liveBullets) { bullet->fire(deltaTime); }

    ship->update(deltaTime);
    window.clear();
    window.draw(background);
    ship->draw(window);
    for (Asteroid* asteroid : liveAsteroids) { // Update and draw each asteroid
        asteroid->update();
        window.draw(asteroid->asteroidSprite); // Draws the asteroid using the sprite
    }

    for (Bullet* bullet : liveBullets) { window.draw(bullet->bulletSprite); }
    window.display();

    // Clean up liveBullets
    cleanLiveBullets();
  }
}

// This method keeps our live bullets vector clean of unalive bullets
void Game::cleanLiveBullets() {
  for (auto it = liveBullets.begin(); it != liveBullets.end(); /* no increment here */) {
      if (!(*it)->live) {
          delete *it; // delete the Bullet object
          it = liveBullets.erase(it); // erase returns the new iterator
      } else { ++it; /* only increment if we didn't erase */ }
  }
}

// This method will be called to initiate the game
void Game::run() {
  bool startGame = false; 
  bool visible = true; // Used to blink press any key
  float blinkInterval = 0.5f; 

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) { return; }
      else if (event.type == sf::Event::KeyPressed) { startGame = true; }
    }

    if (clock.getElapsedTime().asSeconds() >= blinkInterval) { // Check if we should blink text
      visible = !visible; 
      if (visible) { text.back()->setFillColor(sf::Color(255, 255, 255, 0)); } 
      else { text.back()->setFillColor(sf::Color(255, 255, 255, 255)); }

      // Update screen
      window.clear(); 
      window.draw(background);
      ship->draw(window);
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
  if (!pressKeyFont.loadFromFile("fonts/astronboy.otf")) { }
  if (backgroundTexture.loadFromFile("textures/background.png")) { backgroundTexture.setRepeated(true); }

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

  // Store fonts in vector 
  text.push_back(asteroidText);
  text.push_back(pressAnyKeyText);

  // Create our background
  background = sf::Sprite(backgroundTexture);
  background.setTextureRect(sf::IntRect(0, 0, RESWIDTH, RESHEIGHT));

  // Create Ship 
  ship = new Ship(RESWIDTH/2, RESHEIGHT/2, *this);
}
