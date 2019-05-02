#ifndef COLLISIONBOX_H
#define COLLISION_H


class CollisionBox
{
	public:
		CollisionBox(int ix, int iy, int iwidth, int iheight);
		void show();
		void move(float dx, float dy);
		void windowcollisions();
		void reset(float nx, float ny){x = nx; y = ny;}
	private:
		float x, y, width, height;
		float dx, dy;
};
#endif