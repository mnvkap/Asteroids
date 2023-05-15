#ifndef ASTEROID_H
#define ASTEROID_H

class Asteroid {
  private:
    int x;
    int y;
    
  public:
    Asteroid(int wave);
    void startMove();
    void kill();
    
}
#endif //ASTEROID_H
