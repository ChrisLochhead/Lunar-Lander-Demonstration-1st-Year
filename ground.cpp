#include"ground.h"
#include "GL\freeglut.h"
#include"random.h"

Ground::Ground()
{
	for(int i=0; i<100; i++){	
		heights[i] = rnd(50, 100);  // create 100 random peaks and add them to the heights array
	}

	int f1 = rnd(10, 50); 
	int f2 = rnd(50, 80); // predefined landing area ranges

	float h = heights[f1];

	for(int i=f1; i<f1+10; i++){	
		heights[i] = h; // make ten points from here random for first landing zone
	}

	h = heights[f2];

	for(int i=f2; i<f2+10; i++){	
		heights[i] = h; // and then again for the second landing zone
	}
}

float Ground::heightAt(float x) {
	int height_index = x * NUM_HEIGHTS / SCREEN_WIDTH;
	return heights[height_index];
}

void Ground::show()
{
	glBegin(GL_LINE_STRIP); // draw a single line with multiple points
		glColor3f(0.5, 0.5, 0.5);
		glLineWidth(5.0);

		glVertex2f(-02, -1); // creat start off screen
		for(int i=0; i<100; i++){
			glVertex2f(i*10, heights[i]); // draw each point from heights array at intervals of 10 on the x axis
		}
		glVertex2f(1015, -1); // and finish off screen
	glEnd();
}

