/* Author : Michael Wines
 * Assignment:  HW3
 * Purpose:  Modularlize a program.
*/

#include "michaelW.h"
#include <GL/glx.h>
#include "ppm.h"
#include "structures.h"

Ppmimage *shipImage = NULL;
GLuint shipTexture;



void getShipTexture(void) {
    shipImage = ppm6GetImage((char*)"./images/ship.ppm");
    glGenTextures(1, &shipTexture);
    glBindTexture(GL_TEXTURE_2D, shipTexture);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, shipImage->width, shipImage->height, GL_RGB, GL_UNSIGNED_BYTE, shipImage->data);
}
void setShipTexture(Game *g){
    glPushMatrix();
    glTranslatef(g->ship.pos[0], g->ship.pos[1], g->ship.pos[2]);
    glBindTexture(GL_TEXTURE_2D, shipTexture);
    glRotatef(g->ship.angle, 0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);

    glVertex2f(  -20.0f,-10.0f); glTexCoord2f(0.0f, 0.2f);
    glVertex2f(0.0f,  20.0f); glTexCoord2f(0.5f, 1.0f);
    glVertex2f(0.0f,  -6.0f);  glTexCoord2f(0.5f, 0.2f);
    glVertex2f(20.0f,  -10.0f); glTexCoord2f(1.0f, 0.2f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnd();
}



