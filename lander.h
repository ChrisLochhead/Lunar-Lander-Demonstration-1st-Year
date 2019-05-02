#ifndef LANDER_H
#define LANDER_H

#include "ground.h"

const float GRAVITY = 0.003; // set the gravity once here

class Lander
{
	public:
		Lander(float ix, float iy, int iradius); // created with initial position and size

		void show();	
		void draw();
		void gravity();
		void windowcollisions();
		void stop();
		void incrementVel(float ddx, float ddy);
		void reset();

		int getfuel(){return fuel;}
		void setfuel(int newfuel){fuel = newfuel;}

		float gety(){return y;}
		float getx(){return x;}

		float getDx(){return dx;}
		float getDy(){return dy;}

		float heightLeftAboveGround(Ground *g);
		float heightRightAboveGround(Ground *g);
	private:
		float x, y, radius, dy, dx;
		int fuel;
};
#endif