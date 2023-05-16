#include "Game.h"

const float Game::RESHEIGHT = 1080;
const float Game::RESWIDTH  = 1920;

Game::Game() 
  : window(sf::VideoMode(RESWIDTH, RESHEIGHT), "Asteroids") { 
  setUp();
}

void Game::start() {
  window.clear(); 

  // Create our background
  sf::Sprite background;
  background.setTexture(starPattern);
  background.setTextureRect(sf::IntRect(0, 0, RESWIDTH, RESHEIGHT));
  
  window.draw(background);
  window.display();
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed) { return; }
    }
  }
}
void Game::run() {
  // Create our background
  sf::Sprite background;
  background.setTexture(starPattern);
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

void Game::setUp() {
  if (!asteroidFont.loadFromFile("font/nasalization-rg.otf")) { }
  if (!regularTextFont.loadFromFile("font/nocontinue.ttf")) { }
  if (!pressKeyFont.loadFromFile("font/astronboy.otf")) { }
  if (starPattern.loadFromFile("textures/repeatStars.png")) { starPattern.setRepeated(true); }

  // Create text objects
  sf::Text* asteroidText = new sf::Text;
  sf::Text* moveUpText = new sf::Text;
  sf::Text* moveDownText = new sf::Text;
  sf::Text* moveLeftText = new sf::Text;
  sf::Text* moveRightText = new sf::Text;
  sf::Text* pressAnyKeyText = new sf::Text;

  // Set Asteroids text
  asteroidText->setString("ASTEROIDS");
  asteroidText->setFont(asteroidFont);
  asteroidText->setCharacterSize((int)(.085 *(RESHEIGHT + RESWIDTH)));
  asteroidText->setFillColor(sf::Color(252, 61, 33, 252));
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

  // Set Direcions 
  moveUpText->setString("'W' or 'UP ARROW' MOVE THE SHIP UPWARDS");
  moveDownText->setString("'S' or 'DOWN ARROW' MOVE THE SHIP DOWNWARDS");
  moveLeftText->setString("'A' or 'LEFT ARROW' MOVE THE SHIP LEFT");
  moveRightText->setString("'D' or 'RIGHT ARROW' MOVE THE SHIP RIGHT");

  // Create vector for managing text objects 
  text = {moveUpText, moveDownText, moveLeftText, moveRightText};

  // Set regular text
  int spacing = 0; // Used to keep track of space between lines
  for (auto text: text) {
    // Set up text formating
    text->setFont(regularTextFont);
    text->setCharacterSize((int)(.02 *(RESHEIGHT + RESWIDTH)));
    text->setFillColor(sf::Color(255, 175, 0, 200));
    
    // Set up text position
    sf::FloatRect textBounds = text->getLocalBounds();
    text->setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f); // Set the origin to the center of the text
    text->setPosition(RESWIDTH / 2.0f, (RESHEIGHT / 2) - 200 + spacing );
    spacing += textBounds.height + 10; // Set space for next line, based on the height of the text, plus some margin
  }
  text.push_back(asteroidText);
  text.push_back(pressAnyKeyText);
}
