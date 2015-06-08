/*Amador Joao Silva
  CMPS 335
  Advanced Asteroids
  Spring 2015
  */
#include "structures.h"
#include "ppm.h"
#include<stdlib.h>
#include<stdio.h>
#include<ctime>
#include<cmath>
#include<GL/gl.h>
#include "ajS.h"
using namespace std;


GLuint getPpm()
{
    //load images into a ppm structure
    //Ppm tmp;
    Ppmimage *asteroidTex=NULL;
    asteroidTex = ppm6GetImage((char*)"./images/generic.ppm");
    int w = asteroidTex->width;
    int h = asteroidTex->height;
    unsigned char tmpArr[w*h*3];
    unsigned char *t = asteroidTex->data;
    unsigned char dataWithAlpha[w*h*4];

    for(int i=0; i<(w*h*3); i++){
	tmpArr[i] = *(t+i);
    }
    // apply the alpha channel
    for(int i=0; i<(w*h); i++){
	// copy color to new array
	dataWithAlpha[i*4] = tmpArr[3 * i];
	dataWithAlpha[i*4 + 1] = tmpArr[ 3 * i + 1];
	dataWithAlpha[i*4 + 2] = tmpArr[ 3 * i + 2];
	// set alpha
	if((int)tmpArr[i*3] ==0 && (int)tmpArr[i*3+1]==0 && (int)tmpArr[i*3+2]==0 )
	    dataWithAlpha[i*4+3]=0;
	else
	    dataWithAlpha[i*4+3]=250;
    }


    GLuint returningTex;
    //
    glGenTextures(1, &returningTex);
    glBindTexture(GL_TEXTURE_2D, returningTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataWithAlpha);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return returningTex;
}

void buildBoss(Boss *&boss) {
    boss = new Boss;
    boss->nverts = 4;
    boss->radius = 200;

    Flt angle = 0.0f;
    Flt inc = (3.14159265 * 2.0)/ (Flt)boss->nverts;
    for (int i=0; i < 4; i++) {
	boss->vert[i][0] = sin(angle) * (boss->radius);
	boss->vert[i][1] = cos(angle) * (boss->radius);
	angle += inc;
    }
    boss->pos[0]= xres/1.5;
    boss->pos[1]= yres;
    boss->pos[2]= 0;
    boss->vel[0]= rand() % 6 + (-3);
    boss->vel[1]= rand() % 6 + (-3);

    boss->lifePoint = 100;


}

GLuint getBossPpm()
{
    //load images into a ppm structure
    //Ppm tmp;
    Ppmimage *asteroidTex=NULL;
    asteroidTex = ppm6GetImage((char*)"./images/EvilMoon.ppm");
    int w = asteroidTex->width;
    int h = asteroidTex->height;
    unsigned char tmpArr[w*h*3];
    unsigned char *t = asteroidTex->data;
    unsigned char dataWithAlpha[w*h*4];

    for(int i=0; i<(w*h*3); i++){
	tmpArr[i] = *(t+i);
    }
    // apply the alpha channel
    for(int i=0; i<(w*h); i++){
	// copy color to new array
	dataWithAlpha[i*4] = tmpArr[3 * i];
	dataWithAlpha[i*4 + 1] = tmpArr[ 3 * i + 1];
	dataWithAlpha[i*4 + 2] = tmpArr[ 3 * i + 2];
	// set alpha
	if((int)tmpArr[i*3] ==0 && (int)tmpArr[i*3+1]==0 && (int)tmpArr[i*3+2]==0 )
	    dataWithAlpha[i*4+3]=0;
	else
	    dataWithAlpha[i*4+3]=250;
    }


    GLuint returningTex;
    //
    glGenTextures(1, &returningTex);
    glBindTexture(GL_TEXTURE_2D, returningTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataWithAlpha);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return returningTex;
}

void deleteBulletBoss(Game *&g, Bullet *&node)
{
    if(node->prev == NULL) {
	if (node->prev == NULL) {
	    g->bhead = NULL;
	} else {
	    node->next->prev = NULL;
	    g->bhead = node->next;
	}
    } else {
	if (node->next ==NULL) {
	    node->prev->next = NULL;
	} else { 
	    node->prev->next = node->next;
	    node->next->prev = node->prev;
	}
    }
    delete node;
    node = NULL;
    g->nbullets--;
}

void BossMvmtBulletCol(Game *&g, Boss *&boss, bool &hadBoss) {
    float d0, d1, dist;


    if (boss != NULL) {
	boss->pos[0] += boss->vel[0];
	boss->pos[1] += boss->vel[1];
	//check for collision with window edges
	if (boss->pos[0] < -100.0) {
	    boss->pos[0] += (float)xres+200;
	}
	else if (boss->pos[0] > (float)xres+100) {
	    boss->pos[0] -= (float)xres+200;
	}
	else if (boss->pos[1] < -100.0) {
	    boss->pos[1] += (float)yres+200;
	}
	else if (boss->pos[1] > (float)yres+100) {
	    boss->pos[1] -= (float)yres+200;
	}


	Bullet *b = g->bhead;
	while(b)
	{
	    d0 = b->pos[0] - boss->pos[0];
	    d1 = b->pos[1] - boss->pos[1];
	    dist = sqrt(d0*d0 + d1*d1);
	    if (dist < (boss->radius-100)) {
		//cout << "hit" << endl;
		boss->color[0] = 1;
		boss->color[1] = 0;
		boss->color[2] = 0;
		boss->lifePoint--;

		if (boss->lifePoint % 5 == 0) {
		    int temp1 = rand() % 6 + (-3);
		    if( temp1 < 0 ) {
			boss->vel[0] = (rand() % 3 + 5) * -1;
		    } else {
			boss->vel[0] = rand() % 3 + 5;
		    }
		    temp1 = rand() % 6 + (-3);
		    if (temp1 < 0 ) {
			boss->vel[1] = (rand() % 3 + 5) * -1;
		    } else {
		    	boss->vel[1] = rand() % 3 + 5;
		    }
		}


		//delete the bullet..
		Bullet *saveb = b->next;
		deleteBulletBoss(g,b);
		b = saveb;
		break;

	    }
	    if(boss->lifePoint <= 0){
		delete boss;
		boss=NULL;
		hadBoss=true;
		//cout << "testing for seg fault" << endl;
		break;
	    }
	    b = b->next;

	}
	if(boss != NULL) {
	    d0 = g->ship.pos[0] - boss->pos[0];
	    d1 = g->ship.pos[1] - boss->pos[1];
	    dist = sqrt(d0*d0 + d1*d1);
	    if(dist < boss->radius * 0.85) {
		boss->killShip = true;
	    } else {
		boss->killShip = false;
	    }
	}

    }
}


