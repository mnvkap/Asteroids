#ifndef SHIP_H
#define SHIP_H

class Ship {
  
  public:
    // Coordinates of ship
    int x;
    int y;
    int health;
    int boostTimer;

    // Constructor
    Ship();
    void move(int deltaX, int deltaY);
    void shoot();
    void takeDamage();
    void getInfo();
    void boost();
}
