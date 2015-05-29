#ifndef _drewC_H_
#define _drewC_H_
void resizeAsteroid(Asteroid *a);
void asteroidCollision(Asteroid *a, Game *g);
void endMenu(Game *g);
bool endGame(Game *g);
float bulletAccuracy(Game *g);
extern const int super;
#endif

