/* JoAnn Tuazon       *
 * CMPS 335           *
 * Advanced-Asteroids *
 * Spring 2015        */

#include "joannT.h"

void init_sounds(void)
{
    if(fmod_init()) {
	printf("ERROR");
	return;
    }
    if(fmod_createsound((char *)"./sounds/Asteroids.mp3", 0)) {
	printf("ERROR");
	return;
    }
    if(fmod_createsound((char *)"./sounds/starpower.mp3", 1)) {
	printf("ERROR");
	return;
    }
    fmod_setmode(0,FMOD_LOOP_NORMAL);
    fmod_setmode(1,FMOD_LOOP_NORMAL);
}

void play_music(int a) {
    fmod_playsound(a);
}

//void pause_music(int a) {
//    fmod_setpaused(a);
//}


GLuint load_background(void)
{
    GLuint bgTexture;
    Ppmimage *bgImage = ppm6GetImage((char*)"./images/AA_background.ppm");
    glGenTextures(1, &bgTexture);
    glBindTexture(GL_TEXTURE_2D, bgTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    bgImage->width, bgImage->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, bgImage->data);
    return bgTexture;
}

void draw_background(GLuint bgTexture)
{
    glBindTexture(GL_TEXTURE_2D, bgTexture);
    glBegin(GL_QUADS);
    glColor3f(1.0f,0.0f,0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(0, yres);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, yres);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, 0);
    glEnd();
}

void set_mouse_position(int x, int y) {
    XWarpPointer(dpy, None, win, 0, 0, 0, 0, x, y);
}

void show_mouse_cursor(const int onoff)
{
    if (onoff) {
	XUndefineCursor(dpy, win);
	return;
    }
    Pixmap blank;
    XColor dummy;
    char data[1] = {0};
    Cursor cursor;
    blank = XCreateBitmapFromData (dpy, win, data, 1, 1);
    if (blank == None)
	std::cout << "error: out of memory." << std::endl;
    cursor = XCreatePixmapCursor(dpy, blank, blank, &dummy, &dummy, 0, 0);
    XFreePixmap(dpy, blank);
    XDefineCursor(dpy, win, cursor);
}
