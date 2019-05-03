#ifndef GROUND_H
#define GROUND_H 

class Ground // generates the ground
{
	public:
		Ground();
		void show();
		float heightAt(float x);
	private:
		// screen width and height are not changeable so the screen isnt resizeable
		static const int SCREEN_WIDTH = 1000; 
		static const int NUM_HEIGHTS = 100;
		float x, y, size;
		float heights[NUM_HEIGHTS];
};

#endif