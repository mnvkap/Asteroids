#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <"Ship.h">

#ifndef GAME_H
#define GAME_H

class Game {
  private:
    // Window for game to be played in 
    sf::RenderWindow window;
    
    // Game object
    Ship* ship;

    // Sounds
    sf::Sound fire;
    sf::Sound boost;
    sf::Sound kill;
    sf::Sound damage;
    sf::Sound lose;

    int score;
    int wave;

    // Constructor helper method
    void setUpPopUp();
  public:
    static const float RESHEIGHT;
    static const float RESWIDTH;


    Game();
    
    // Method to start Game
    void run();
    void stop(); 
}
