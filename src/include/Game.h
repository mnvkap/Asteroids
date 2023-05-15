#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#ifndef GAME_H
#define GAME_H

class Game {
  private: 
    sf::RenderWindow window;
  public:
    Game();
    void run();
    void stop(); 
}
