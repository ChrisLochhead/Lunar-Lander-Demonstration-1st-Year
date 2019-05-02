#include"collisionbox.h"
#include"gl/glut.h"
#include"lander.h"
#include<iostream>
using namespace std;

CollisionBox::CollisionBox(int ix, int iy, int iwidth, int iheight)
{
	x = ix; y = iy; 
	width = iwidth; height = iheight;
}

void CollisionBox::show()
{
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
		glVertex2i(x, y);
		glVertex2i(x+width, y);
		glVertex2i(x+width, y+height);
		glVertex2i(x, y+height);
	glEnd();
}

void CollisionBox::move(float dx, float dy)
{
	x += dx;
	y -= dy;
}

void CollisionBox::windowcollisions()
{
	if((x+width) < 0)			
		x = x+1000;
	else if((x-width) > 1000)	
		x = x-1000;
}

