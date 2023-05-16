#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#ifndef GAME_H
#define GAME_H

class Game {
  public:
    sf::RenderWindow window;

    Game();
    void run();
    void stop(); 
}
