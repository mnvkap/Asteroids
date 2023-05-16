#ifndef BULLET_H
#define BULLET_H

class Bullet {
  public:
    // Coordinates of Bullet 
    int xPos;
    int yPos;

    Bullet(int deltaX, int deltaY);
    // Start the movement of the bullet
    void startFire();
    // End the movement, called when bullet hit's Boundary or Asteroid
    void stopFire();
};
#endif //BULLET_H
