#include <Asteroid.h>
int RESWIDTH = static_cast<int>(Game::RESWIDTH);
int RESHEIGHT = static_cast<int>(Game::RESHEIGHT);

Asteroid::Asteroid() {
  setPositionAndVelocity();

  if (!asteroidTexture.loadFromFile("textures/BigAsteroid.png")) { }
  asteroidSprite.setTexture(asteroidTexture);
  asteroidSprite.setScale(Game::RESWIDTH * 0.2f / asteroidTexture.getSize().x, Game::RESHEIGHT * 0.2f / asteroidTexture.getSize().y);
  asteroidSprite.setPosition(xPos, yPos);
  sf::FloatRect bounds = asteroidSprite.getGlobalBounds();
}

void Asteroid::setPositionAndVelocity() {
  std::random_device rd; // Create a random number engine
  std::mt19937 gen(rd()); // Mersenne Twister engine
  std::uniform_int_distribution<int> edgeGen(0, 3); // Create a distribution
  std::uniform_real_distribution<float> randOne(-0.02, 0.01); // Random float between -0.2 - 0.2
  std::uniform_real_distribution<float> randTwo(0.02, 0.03); // Random float between 0.2 - 0.8
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
  // Check X boundaries
  if (xPos < -bounds.width) { xPos = Game::RESWIDTH + bounds.width; }
  else if (xPos > bounds.width + Game::RESWIDTH) { xPos = -bounds.width; }

  // Check Y boundaries
  if (yPos < -bounds.height) { yPos = Game::RESHEIGHT + bounds.height; } 
  else if (yPos > bounds.height + Game::RESHEIGHT) { yPos = -bounds.height; }

  asteroidSprite.setPosition(xPos, yPos);
}
