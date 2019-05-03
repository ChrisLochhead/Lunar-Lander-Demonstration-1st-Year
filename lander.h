#ifndef LANDER_H
#define LANDER_H

#include "ground.h"

const float GRAVITY = 0.003; // set the gravity once here

class Lander
{
	public:
		Lander(float ix, float iy, int iradius); // created with initial position and size

		//render functons using freeglut
		void show();	
		void draw();
		
		//physics and collision
		void gravity();
		void windowcollisions();
		void stop();
		void incrementVel(float ddx, float ddy);

		//restart game
		void reset();

		//fuel management
		int getfuel(){return fuel;}
		void setfuel(int newfuel){fuel = newfuel;}

		//get positons
		float gety(){return y;}
		float getx(){return x;}

		float getDx(){return dx;}
		float getDy(){return dy;}

		//check height
		float heightLeftAboveGround(Ground *g);
		float heightRightAboveGround(Ground *g);
	private:
		float x, y, radius, dy, dx;
		int fuel;
};
#endif