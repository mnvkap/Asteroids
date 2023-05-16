#include "Ship.h"
#include "Bulelt.h"

Ship::Ship(int centerX, int centerY) 
  : health(99), boostTimer(5), xPos(centerX), yPos(centerY) {
}

void Ship::move(int deltaX, int deltaY) {
  xPos = deltaX;
  yPos = deltaY;
}

void Ship::shoot() {
  Bullet bullet = new Bullet(xPos, yPos);
  bullet.startFire();
}

void Ship::takeDamage() {
  health -= 33; 
  // Do something on the screen
}

  

