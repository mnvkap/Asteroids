#ifndef SHIP_H
#define SHIP_H

class Ship {
  
  public:
    // Coordinates of ship
    int xPos;
    int yPos;
    int health;
    int boostTimer;

    // Constructor
    Ship(int centerX, int centerY);
    void move(int deltaX, int deltaY);
    void shoot();
    void takeDamage();
    void boost();
};
#endif //SHIP_H
