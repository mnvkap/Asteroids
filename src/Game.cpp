#include "Game.h"

const float Game::RESHEIGHT = 1080;
const float Game::RESWIDTH  = 1920;

Game::Game() 
: window(sf::VideoMode(RESWIDTH, RESHEIGHT), "Asteroids") { 
  setUpText();
}

void Game::run() {
  // Create rectangle to lay our text on 
  sf::RectangleShape background(sf::Vector2f(RESWIDTH, RESHEIGHT));
  background.setFillColor(sf::Color(64, 64, 64, 255));
  window.draw(background);
  for(auto textObj: text) { window.draw(*textObj); }

  window.display();
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) { return; }
      else if (event.type == sf::Event::KeyPressed) { return; }
    }
  }
}

void Game::setUpText() {
  if (!asteroidFont.loadFromFile("font/nasalization-rg.otf")) { }
  if (!regularTextFont.loadFromFile("font/atarianSystemBold.ttf")) { }

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
  asteroidText->setCharacterSize((int)(.075 *(RESHEIGHT + RESWIDTH)));
  asteroidText->setFillColor(sf::Color::Red);
  sf::FloatRect asteroidBounds = asteroidText->getLocalBounds(); // Used to calculate placement of text
  asteroidText->setOrigin(asteroidBounds.left + asteroidBounds.width / 2.0f, asteroidBounds.top + asteroidBounds.height / 2.0f); // Set the origin to the center of the text
  asteroidText->setPosition(RESWIDTH / 2.0f, 150);

  // Set Direcions and pressAnyKeyText
  moveUpText->setString("'W' or 'UP ARROW' WILL MOVE THE SHIP UPWARDS");
  moveDownText->setString("'S' or 'DOWN ARROW' WILL MOVE THE SHIP DOWNWARDS");
  moveLeftText->setString("'A' or 'LEFT ARROW' WILL MOVE THE SHIP LEFT");
  moveRightText->setString("'D' or 'RIGHT ARROW' WILL MOVE THE SHIP RIGHT");
  pressAnyKeyText->setString("PRESS ANY KEY TO PLAY");

  // Create vector for managing text objects 
  text = {moveUpText, moveDownText, moveLeftText, moveRightText, pressAnyKeyText};

  // Set regular text
  int spacing = 0; // Used to keep track of space between lines
  for (auto text: text) {
    // Set up text formating
    text->setFont(regularTextFont);
    text->setCharacterSize((int)(.025 *(RESHEIGHT + RESWIDTH)));
    text->setFillColor(sf::Color::White);
    
    // Set up text position
    sf::FloatRect textBounds = text->getLocalBounds();
    text->setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f); // Set the origin to the center of the text
    text->setPosition(RESWIDTH / 2.0f, (RESHEIGHT / 2) + spacing );
    spacing += textBounds.height + 10; // Set space for next line, based on the height of the text, plus some margin
  }
  text.push_back(asteroidText);
}
