#include <Asteroid.h>
int RESWIDTH = static_cast<int>(Game::RESWIDTH);
int RESHEIGHT = static_cast<int>(Game::RESHEIGHT);

Asteroid::Asteroid(int size) 
  : live(true), size(size) {
  setPositionAndVelocity();
  
  switch(size) {
    case 4:
      if (!asteroidTexture.loadFromFile("textures/Asteroid4.png")) { }
      asteroidSprite.setTexture(asteroidTexture);
      asteroidSprite.setScale(Game::RESWIDTH * 0.2f / asteroidTexture.getSize().x, Game::RESHEIGHT * 0.2f / asteroidTexture.getSize().y);
      break;
    case 3:
      if (!asteroidTexture.loadFromFile("textures/Asteroid3.png")) { }
      asteroidSprite.setTexture(asteroidTexture);
      asteroidSprite.setScale(Game::RESWIDTH * 0.15f / asteroidTexture.getSize().x, Game::RESHEIGHT * 0.15f / asteroidTexture.getSize().y);
      break;
    case 2:
      if (!asteroidTexture.loadFromFile("textures/Asteroid2.png")) { }
      asteroidSprite.setTexture(asteroidTexture);
      asteroidSprite.setScale(Game::RESWIDTH * 0.1f / asteroidTexture.getSize().x, Game::RESHEIGHT * 0.1f / asteroidTexture.getSize().y);
      break;
    case 1:
      if (!asteroidTexture.loadFromFile("textures/Asteroid1.png")) { }
      asteroidSprite.setTexture(asteroidTexture);
      asteroidSprite.setScale(Game::RESWIDTH * 0.05f / asteroidTexture.getSize().x, Game::RESHEIGHT * 0.05f / asteroidTexture.getSize().y);
      break;
  }

  asteroidSprite.setPosition(xPos, yPos);
}

void Asteroid::setPositionAndVelocity() {
  std::random_device rd; // Create a random number engine
  std::mt19937 gen(rd()); // Mersenne Twister engine
  std::uniform_int_distribution<int> edgeGen(0, 3); // Create a distribution
  std::uniform_real_distribution<float> randOne(-0.01, 0.01); // Random float between -0.2 - 0.2
  std::uniform_real_distribution<float> randTwo(0.01, 0.02); // Random float between 0.2 - 0.8
  int edge = edgeGen(gen); // randomly select one of the four edges 
  switch(edge) {
    case 0: // top
      xPos = rand() % RESWIDTH;
      yPos = 0;
      dx = randOne(gen);
      dy = randTwo(gen);
      break;
    case 1: // right
      xPos = RESWIDTH;
      yPos = rand() % RESHEIGHT;
      dx = -randTwo(gen);
      dy = randOne(gen);
      break;
    case 2: // bottom
      xPos = rand() % RESWIDTH;
      yPos = RESHEIGHT;
      dx = randOne(gen);
      dy = -randTwo(gen);
      break;
    case 3: // left
      xPos = 0;
      yPos = rand() % RESHEIGHT;
      dx = randTwo(gen);
      dy = randOne(gen);
      break;
  }
}

void Asteroid::update() {
  xPos += dx;
  yPos += dy;
  
  // get the width and height of the sprite
  float spriteWidth = asteroidSprite.getGlobalBounds().width;
  float spriteHeight = asteroidSprite.getGlobalBounds().height;

  // Check X boundaries
  if (xPos < -spriteWidth) { xPos = Game::RESWIDTH; }
  else if (xPos > Game::RESWIDTH) { xPos = -spriteWidth; }

  // Check Y boundaries
  if (yPos < -spriteHeight) { yPos = Game::RESHEIGHT; } 
  else if (yPos > Game::RESHEIGHT) { yPos = -spriteHeight; }

  asteroidSprite.setPosition(xPos, yPos);
}

std::vector<Asteroid*> Asteroid::breakApart(Asteroid* asteroid) {
  std::vector<Asteroid*> newAsteroids;
  if (asteroid->size == 1) { asteroid->live = false; return newAsteroids; } 

  float spriteWidth = asteroid->asteroidSprite.getGlobalBounds().width;
  float spriteHeight = asteroid->asteroidSprite.getGlobalBounds().height;

  Asteroid* newAsteroidOne = new Asteroid(asteroid->size - 1);
  newAsteroidOne->xPos = asteroid->xPos + (spriteWidth / 2);  
  newAsteroidOne->yPos = asteroid->yPos + (spriteHeight / 2); 
  newAsteroidOne->dx = asteroid->dx * 2.5;
  newAsteroidOne->dy = asteroid->dy * 1.5; 

  Asteroid* newAsteroidTwo = new Asteroid(asteroid->size - 1);
  newAsteroidTwo->xPos = asteroid->xPos - (spriteWidth / 2); 
  newAsteroidTwo->yPos = asteroid->yPos - (spriteHeight / 2); 
  newAsteroidTwo->dx = asteroid->dx * 1.5;
  newAsteroidTwo->dy = asteroid->dy * 2.5; 

  asteroid->live = false; // Kill parent asteroid
  newAsteroids.push_back(newAsteroidOne);
  newAsteroids.push_back(newAsteroidTwo);
  return newAsteroids; 
}
