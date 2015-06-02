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
GLuint load_background(void);
void draw_background(GLuint bgTexture);

#endif
