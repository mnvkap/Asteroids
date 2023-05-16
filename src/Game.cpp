#Include "Game.h"

float Game::RESHEIGHT = 1280;
float Game::RESWIDTH  =  720;

// The constructor will do 2 Things :
// 1.) Generate a pop-up window, Advising the user on the game itself
// 2.) Start the game if the user wishes to proceed
// or Close the application
Game::Game() {
  setUpPopUp();
}

void Game::setUpPopUp() {
  // Create rectangle to lay our text on 
  sf::RectangleShape background(sf::Vector2f(RESWIDTH, RESHEIGHT));
  background.setFillColor(sf::Color(0, 0, 0, 150));

  // Create text objects
  sf::Font asteroidFont; 
  sf::Font regularTextFont;
  if (!asteroidFont.loadFromFile("font/nasalization-rg.otf")) { }
  if (!regularTextFont.loadFromFile()) { }

  sf::Text asteroidText;
  sf::Text moveText;
  sf::Text pressAnyKeyText;

  asteroidText.setFont(asteroidFont);
  moveText.setFont(regularTextFont);
  pressAnyKeyText.setFont(regularTextFont); 

  asteroidText.setString("ASTEROIDS!!!");
  asteroidText.setCharacterSize(48);
  asteroidText.setFillColor(sf::Color::Red);

  // Calculate pos of asteroidText
  sf::FloatRect asteroidBounds = asteroidText.getLocalBounds();
  asteroidText.setOrigin(asteroidBounds.left + asteroidBounds.width / 2.0f, asteroidBounds.top + asteroidBounds.height / 2.0f); // Set the origin to the center of the text
  asteroidText.setPosition(RESWIDTH / 2.0f, 100);

  window.draw(background);
  window.draw(asteroidText);
}

void Game::run() {
  window.display();
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) { return false; }
      else if (event.type == sf::Event::KeyPressed) { return true; }
    }
  }
}

