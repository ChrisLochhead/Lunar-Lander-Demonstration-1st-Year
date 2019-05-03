#include"lander.h"
#include "GL\freeglut.h"
#include"random.h"
#include<cmath>
#include"ground.h"

const float PI = 3.14159268; // set pi for drawing of the lander

Lander::Lander(float ix, float iy, int iradius)
{
	x = ix; y = iy; radius = iradius;
	dx = rand() % 2 - 4;
	dy = 1;
	fuel = 300;
}

void Lander::show(){
	glPushMatrix();
	glTranslatef(x, y, 0);
	glRotatef(22, 0, 0, 1);
	glTranslatef(-x, -y, 0);
	draw();
	glPopMatrix();
}

void Lander::draw()
{
	glBegin(GL_POLYGON);		// lander
	const int NPOINTS=10;
	const float TWOPI=2*3.1415927;
	const float STEP=TWOPI/NPOINTS;
	glColor3f(0, 1, 0);
	for(float angle=0; angle<TWOPI; angle+=STEP)	
		glVertex2f(x+radius*cos(angle), y+radius*sin(angle)); // draw an 8 point circle
	glEnd();

	glBegin(GL_LINE_LOOP);	//draw left leg
	glColor3f(0, 1, 1);
	glVertex2f(x-6, y-6);
	glColor3f(0, 1, 1);
	glVertex2f(x-12, y-12);
	glEnd();

	glBegin(GL_LINE_LOOP);	// draw right leg
	glColor3f(0, 1, 1);
	glVertex2f(x, y-8);
	glColor3f(0, 1, 1);
	glVertex2f(x, y-17);
	glEnd();
}


void Lander::gravity()
{
	x += dx;			
		
	y += -dy;			
	dy += GRAVITY;		 // apply transformations to variables and apply gravity to the y value
}



void Lander::reset() 
{
	x = rand() % 900 + 100;
	y = rand() % 450 + 350; // reset the landers position and fuel withing dx and dy boundaries
	dx = rand() % 2 - 4;
	dy= 1;
	fuel = 300;
}

void Lander::incrementVel(float ddx, float ddy) // add values to x and y depending on amount of fuel
{
	if (fuel > 0)
	{
		fuel -= 1;
		if (fuel < 1)
			fuel -= 0;
	}

	dx += ddx;
	dy -= ddy; 
}

void Lander::stop() // freeze the landers position
{
	dy = dx = 0; 
}

void Lander::windowcollisions() // make lander appear on other side of the screen like pacman
{
	if((x+radius)<0)			
		x = x+1000;
	else if((x-radius) > 1000)	
		x = x-1000;
}

float Lander::heightLeftAboveGround(Ground *g)
{
	return g->Ground::heightAt(x-12);
}

float Lander::heightRightAboveGround(Ground *g) 
{
	return g->heightAt(x);
}






