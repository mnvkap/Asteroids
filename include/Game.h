#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#ifndef GAME_H
#define GAME_H

class Game {
  public:
    int const RESHEIGHT;
    int const RESWIDTH;

    // Window for game to be played in 
    sf::RenderWindow window;

    Game();
    // Method to start Game
    void run();
    void stop(); 
}
