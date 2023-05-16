#ifndef BULLET_H
#define BULLET_H

public Bullet {
  public:
    // Coordinates of Bullet 
    int x;
    int y;

    Bullet();
    // Start the movement of the bullet
    void startFire();
    // End the movement, called when bullet hit's Boundary or Asteroid
    void stopFire();
}
#endif //BULLET_H
