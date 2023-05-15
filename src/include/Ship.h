#ifndef SHIP_H
#define SHIP_H

class Ship {
  private:
    int x;
    int y;
    int health;
    int boostTimer;
  
  public:
    Ship();
    void move(int deltaX, int deltaY);
    void shoot();
    void takeDamage();
    void getInfo();
    void boost();
}
