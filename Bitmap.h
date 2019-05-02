

#ifndef BITMAP_H
#define BITMAP_H

#include <string>
typedef unsigned char BYTE;
#define BMPError char
#include "GL\freeglut.h"

enum Orientation{
	NORMAL,
	MIRROR_X,
	MIRROR_Y,
	ROT_90,
	ROT_180,
	ROT_270
};

class Bitmap
{
public:
	Bitmap(const char fname[], bool transparency=false);
	Bitmap(std::string fname, bool transparency=false);
	int getWidth(){ return width;}
	int getHeight(){ return height;}
	void draw();	// Draw at
	void draw(int x, int y, int w, int h);
	void drawAt(int pos_x, int pos_y);
	void drawAt(int pos_x, int pos_y, int seg_x, int seg_y, int seg_w, int seg_h);
	void setCurrentImage(const char fname[], bool transparency=false);
	void setCurrentImage(std::string fname, bool transparency = false);
	void setOrientation(Orientation o){ orient = o;}
	Orientation getOrientation(){ return orient;}
	GLubyte* getBytes(){ return bytes;}
	~Bitmap();
private:
	BMPError BMPLoad(const char fname[]);
	BMPError BMPLoadGL(const char fname[]);
	BMPError BMPSetTransparency();
	void drawTexture(float tex_x1, float tex_y1, float text_x2, float tex_y2,
		         int scr_x1, int scr_y1, int scr_x2, int scr_y2);
	GLubyte& pixel(int x,int y,int c);
	void allocateMem();
	int width,height;
	GLubyte* bytes;			
	GLuint texture;
	bool withAlpha;
	bool loaded;
	Orientation orient;
};

#define BMPNOTABITMAP 'b'	/// error flags
#define BMPNOOPEN 'o'
#define BMPFILEERROR 'f'
#define BMPBADINT 'i'
#define BMPNOERROR '\0'
#define BMPUNKNOWNFORMAT 'u'


std::string TranslateBMPError(BMPError err);	

#endif
