#ifndef ASTEROID_H
#define ASTEROID_H

class Asteroid {
    
  public:
    // Coordinates of Asteroid
    int x;
    int y;

    Asteroid(int wave);
    void startMove();
    void kill();
    
}
#endif //ASTEROID_H
