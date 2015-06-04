/*Michael Wines
 * header file for michaelW.cpp
*/
#ifndef mwines
#define mwines
#include <GL/glx.h>
#include "ppm.h"
#include "structures.h"

extern Game g;
//extern GLuint shipTexture;
//extern Ppmimage *shipImage = NULL;
void getShipTexture(void);
void setShipTexture(Game *g);
void changeShipTexture(void);

#endif

