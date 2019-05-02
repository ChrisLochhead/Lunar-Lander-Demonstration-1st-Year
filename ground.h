#ifndef GROUND_H
#define GROUND_H // used to prevent multiple declarations and include loops

class Ground // generates the ground
{
	public:
		Ground();
		void show();
		float heightAt(float x){
			int height_index = x * NUM_HEIGHTS/SCREEN_WIDTH;
			return heights[height_index];
		}
	private:

		static const int SCREEN_WIDTH = 1000; 
		static const int NUM_HEIGHTS = 100; // screen width and height are not changeable so the screen isnt resizeable
		float x, y, size;
		float heights[NUM_HEIGHTS];
};

#endif