/* JoAnn Tuazon */

#ifndef JOANNT_H
#define JOANNT_H

#include "structures.h"
#include <FMOD/wincompat.h>
#include "fmod.h"
#include <X11/Xlib.h>
#include <X11/keysym.h>


extern Display *dpy;
extern Window win;
extern XEvent *e;

void init_sounds(void);
void play_music(int a);
GLuint load_texture(char* pathname, Ppmimage *&image);
unsigned char *buildAlphaData(Ppmimage *img);
void setUpImage(GLuint texture, Ppmimage *picture);
void convertToRGBA(Ppmimage *picture);
void draw_ship(Game *g, GLuint imageTexture);
void draw_background(GLuint bgTexture);
void set_mouse_position(int x, int y);
void show_mouse_cursor(const int onoff);

#endif
