//Author: Drew Cody
//Class: CMPS 335
//Assignment: HW3

#include <cmath>
#include "structures.h"
extern "C" {
#include "fonts.h"
}
#include "drewC.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
using namespace std;

void resizeAsteroid(Asteroid *a)
{
    if (a->radius < 50 && a->radius >= 21) {
	a->nverts = 4;
	a->radius = rnd()*80.0 + 40.0;
	Flt r2 = a->radius / 2.0;
	Flt angle = 0.0f;
	Flt inc = (PI * 2.0) / (Flt)a->nverts;
	for (int i=0; i<a->nverts; i++) {
	    a->vert[i][0] = sin(angle) * (r2 + rnd() * a->radius);
	    a->vert[i][1] = cos(angle) * (r2 + rnd() * a->radius);
	    angle += inc;
	}
	a->color[0] = 1.0;
	a->color[1] = 1.0;
	a->color[2] = 1.0;
	a->color[3] = 1.0;
    } 
}

float bulletAccuracy(Game *g)
{
    float accuracy;
    accuracy = (g->bulletsHit/g->bulletsFired) * 100;
    return accuracy;
}

void asteroidCollision(Asteroid *a, Game *g)
{
    while (a) {
	float d0, d1, dist, shipVelocity, asteroidVelocity;
	d0 = g->ship.pos[0] - a->pos[0];
	d1 = g->ship.pos[1] - a->pos[1];
	dist = (d0*d0 + d1*d1);
	if (dist < (a->radius * a->radius) * 0.5) {
	    //Calculate damage taken from impact with asteroid
	    shipVelocity = abs(g->ship.vel[0] + g->ship.vel[1]);
	    asteroidVelocity = abs(a->vel[0] + a->vel[1]);

	    if ( g->ship.superMode >= super ) {
		g->ship.damageTaken += 0;
	    }
	    else if (shipVelocity >= 2.5 || asteroidVelocity >= 2.5) {
		g->ship.damageTaken += 5;
	    }
	    else if (shipVelocity >= 1.5 || asteroidVelocity >= 1.5) {
		g->ship.damageTaken += 2;
	    } else {
		g->ship.damageTaken++;
	    }
	    //Alter ships position and velocity	
	    g->ship.pos[0] = a->pos[0] + d0 * 1.5;
	    g->ship.pos[1] = a->pos[1] + d1 * 1.5;
	    g->ship.vel[0] *= -0.25f;
	    g->ship.vel[1] *= -0.25f;
	    //Alter asteroid velocity
	    a->vel[0] += g->ship.vel[0] * -0.25;
	    a->vel[1] += g->ship.vel[1] * -0.25;
	}
	a = a->next;
    }
}

bool endGame(Game *g)
{
    if (g->ship.damageTaken >= 100) {
	return true;
    } else {
	return false;
    }
}

void endMenu(Game *g)
{
    int yellow = 0x00ffff00;
    int red = 0x00ff0000;
    Rect r;
    r.bot = yres - 300;
    r.left = 600;
    ggprint16(&r, 50, red, "GAME OVER");
    if (g->ship.damageTaken >= 100) {
	ggprint16(&r, 50, red, "YOUR SHIP WAS DESTROYED");
    } else {
	ggprint16(&r, 50, red, "YOU WIN!");
    }
    ggprint16(&r, 50, yellow, "Your Score: %i", g->score);
    ggprint16(&r, 50, yellow, "Your Time: %i seconds",g->gameTimer);
    ggprint16(&r, 50, yellow, "Your Accuracy: %4.2f%",g->accuracy);
    r.bot = yres - 600;
    ggprint16(&r, 50, yellow, "Press ESC to Exit");
}

void readOut(Game *g) {
    int yellow = 0x00ffff00;

    Rect r;
    r.bot = yres - 40;
    r.left = 10;
    r.center = 0;
    ggprint16(&r, 20, 0x00ff0000, "CS335 - Advanced Asteroids");
    ggprint16(&r, 20, yellow, "Score: %i", g->score);
    ggprint16(&r, 20, yellow, "Damage: %i", g->ship.damageTaken);

    if (g->bulletsFired == 0) {
	g->accuracy = 0.0;
    } else {
	g->accuracy = bulletAccuracy(g);
    }
}

void slowDown(Game *g) {
    
    Flt rad = ((g->ship.angle+90.0) / 360.0f) * PI * 2.0;
    Flt xdir = cos(rad);
    Flt ydir = sin(rad);
    if (g->ship.superMode >= super) {
	g->ship.vel[0] = 0.0f;
	g->ship.vel[1] = 0.0f;
    } else {
	g->ship.vel[0] += xdir * -0.025f;
	g->ship.vel[1] += ydir * -0.025f;
	Flt speed = sqrt(g->ship.vel[0]*g->ship.vel[0]+
		g->ship.vel[1]*g->ship.vel[1]);
	if (speed > 5.0f) {
	    speed = 5.0f;
	    normalize(g->ship.vel);
	    g->ship.vel[0] *= speed;
	    g->ship.vel[1] *= speed;
	}
    }
}
