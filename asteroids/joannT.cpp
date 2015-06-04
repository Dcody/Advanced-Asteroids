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

GLuint load_texture(char* pathname, Ppmimage *&image)
{
    GLuint texture;
    //Ppmimage *bgImage = ppm6GetImage(pathname);
    image = ppm6GetImage(pathname);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
	    image->width, image->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
    return texture;
}

void draw_ship(Game *g, GLuint imageTexture)
{
    glEnable(GL_TEXTURE_2D);
    glColor4ub(255, 255, 255, 255);
    glPushMatrix();
    glTranslatef(g->ship.pos[0],g->ship.pos[1],g->ship.pos[2]);
    glBindTexture(GL_TEXTURE_2D, imageTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0); glVertex2i(100,100);
    glTexCoord2f(0.0,1.0); glVertex2i(-100,100);
    glTexCoord2f(1.0,1.0); glVertex2i(100,100);
    glTexCoord2f(1.0,0.0); glVertex2i(100,-100);
    glBindTexture(GL_TEXTURE_2D,0);
    glPopMatrix();
    glEnd();
}

void draw_background(GLuint bgTexture)
{
    glBindTexture(GL_TEXTURE_2D, bgTexture);
    glBegin(GL_QUADS);
    glColor3f(1.0f,1.0f,1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(0, yres);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, yres);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, 0);
    glEnd();
}

unsigned char *buildAlphaData(Ppmimage *img)
{
    int a, b, c;
    unsigned char *newdata, *ptr;
    unsigned char *data = (unsigned char *)img->data;
    newdata = new unsigned char[img->width * img->height * 4];
    ptr = newdata;
    for (int i = 0; i < img->width * img->height * 3; i+=3) {
	a = *(data + 0);
	b = *(data + 1);
	c = *(data + 2);
	*(ptr+0) = a;
	*(ptr+1) = b;
	*(ptr+2) = c;
	
	*(ptr + 3) = (a|b|c);
	ptr += 4;
	data += 3;
    }
    return newdata;
}

void setUpImage(GLuint texture, Ppmimage *picture)
{
    int w = picture->width;
    int y = picture->height;

    glBindTexture(GL_TEXTURE_2D,texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, y, 0, GL_RGB, GL_UNSIGNED_BYTE,
	    picture->data);
}

void convertToRGBA(Ppmimage *picture)
{
    int w = picture->width;
    int y = picture->height;

    unsigned char *silhouetteData = buildAlphaData(picture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, y, 0, GL_RGBA, GL_UNSIGNED_BYTE,
	    silhouetteData);
    delete [] silhouetteData;
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
