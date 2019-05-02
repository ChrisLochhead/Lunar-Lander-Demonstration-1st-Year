
#include "Bitmap.h"
#include "GL\freeglut.h"

Bitmap::Bitmap(const char fname[], bool transparency){
	bytes=0;					 
								
	withAlpha = transparency;
	loaded = false;
	BMPLoadGL(fname); // find bitmap file in debug folder
}

Bitmap::Bitmap(std::string fname, bool transparency){
	bytes=0;
	withAlpha = transparency;
	loaded = false;
	BMPLoadGL(fname.c_str());
}

void Bitmap::setCurrentImage(const char fname[], bool transparency){
	bytes = 0;
	withAlpha = transparency;
	loaded = false;
	BMPLoadGL(fname);
}

void Bitmap::setCurrentImage(std::string fname, bool transparency){
	withAlpha = transparency;
	loaded = false;
	BMPLoadGL(fname.c_str());
}

Bitmap::~Bitmap(){ // destructor function
	glDeleteTextures(1, &texture);
}

GLubyte& Bitmap::pixel(int x,int y,int c){
	if (withAlpha && loaded)
		return bytes[(y*width+x)*4+c];
	else
		return bytes[(y*width+x)*3+c];
}

void Bitmap::allocateMem(){
	
	bytes=new GLubyte[width*height*3];
}

std::string TranslateBMPError(BMPError err) // error checking from errors defined in Bitmap.h
{
	switch(err)
	{
	case(BMPNOTABITMAP):
		return "This file is not a bitmap, specifically it doesn't start 'BM'";
	case(BMPNOOPEN):
		return "Failed to open the file, suspect it doesn't exist";
	case(BMPFILEERROR):
		return "ferror said we had an error. This error seems to not always mean anything, try ignoring it";
	case(BMPBADINT):
		return "sizeof(int)!=4 quite a lot of rewriting probably needs to be done on the code";
	case(BMPNOERROR):
		return "No errors detected";
	case(BMPUNKNOWNFORMAT):
		return "Unknown bmp format, ie not 24bit, 256,16 or 2 colour";
	default:
		return "Not a valid error code";
	}
}

BMPError Bitmap::BMPSetTransparency(){
	
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	GLubyte *transTex = new GLubyte[height*width*4];
	GLubyte r, g, b;
	GLubyte *src = bytes;
	
	r = *src++;
	g = *src++;
	b = *src;
	
	src = bytes;
	GLubyte *dest = transTex;
	
	for (int y=0;y<height;y++)
	{
		for (int x=0;x<width;x++)
		{
			*dest++ = *src++;
			*dest++ = *src++;
			*dest++ = *src++;
			if ( *(dest-3)==r && *(dest-2) == g && *(dest-1) == b)
				*dest++ = 0;
			else
				*dest++ = 255;
		}
	}
	
	delete[] bytes;
	
	bytes = transTex;
	return BMPNOERROR;
}

BMPError Bitmap::BMPLoad(const char* fname)
{
	if(sizeof(int)!=4) return BMPBADINT;
		
	FILE* f=NULL;
	errno_t err = fopen_s(&f, fname,"rb");		
	if(err != 0) {
		return BMPNOOPEN;
	}
	char header[54];
	fread(header,54,1,f);			

	if(header[0]!='B' || header[1]!='M') {
		fclose(f);
		return BMPNOTABITMAP;		
	}

	
	int offset=*(unsigned int*)(header+10);
	
	width=*(int*)(header+18);
	height=*(int*)(header+22);
	
	allocateMem();
	int bits=int(header[28]);		

	int x,y,c;
	BYTE cols[256*4];				
	switch(bits)
	{
	case(24):
		fseek(f,offset,SEEK_SET);
		fread(bytes,width*height*3,1,f);		
		for(x=0;x<width*height*3;x+=3)			
		{
			GLubyte temp=bytes[x];
			bytes[x]=bytes[x+2];
			bytes[x+2]=temp;
		}
		break;

	case(8):
		fread(cols,256*4,1,f);						
		fseek(f,offset,SEEK_SET);
		for(y=0;y<height;++y)						
			for(x=0;x<width;++x)
			{
				GLubyte byte;
				fread(&byte,1,1,f);									
				for(int c=0;c<3;++c) {
					int cc = byte*4+2-c;
					pixel(x,y,c)=cols[cc];	
				}
			}
		break;

	case(4):
		fread(cols,16*4,1,f);
		fseek(f,offset,SEEK_SET);
		for(y=0;y<256;++y)
			for(x=0;x<256;x+=2)
			{
				GLubyte byte;
				fread(&byte,1,1,f);						
				for(c=0;c<3;++c)						
					pixel(x,y,c)=cols[byte/16*4+2-c];
				for(c=0;c<3;++c)
					pixel(x+1,y,c)=cols[byte%16*4+2-c];
			}
		break;

	case(1):
		fread(cols,8,1,f);
		fseek(f,offset,SEEK_SET);
		for(y=0;y<height;++y)
			for(x=0;x<width;x+=8)
			{
				BYTE byte;
				fread(&byte,1,1,f);
				
				
				
				for(int x2=0;x2<8;++x2)
					for(int c=0;c<3;++c)
						pixel(x+x2,y,c)=cols[((byte>>(7-x2))&1)*4+2-c];
			}
		break;

	default:
		fclose(f);
		return BMPUNKNOWNFORMAT;
	}

	if(ferror(f))
	{
		fclose(f);
		return BMPFILEERROR;
	}
	loaded = true;
	fclose(f);
	return BMPNOERROR;
}

void Bitmap::drawTexture(float tex_x1, float tex_y1, float tex_x2, float tex_y2,
		         int scr_x1, int scr_y1, int scr_x2, int scr_y2){
	
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	switch(orient){
	case NORMAL:
		glTexCoord2d(tex_x1,tex_y1);	glVertex2d(scr_x1,scr_y1);
		glTexCoord2d(tex_x2,tex_y1);	glVertex2d(scr_x2,scr_y1);
		glTexCoord2d(tex_x2,tex_y2);	glVertex2d(scr_x2,scr_y2);
		glTexCoord2d(tex_x1,tex_y2);	glVertex2d(scr_x1,scr_y2);
		break;
	case MIRROR_X:
		glTexCoord2d(tex_x2,tex_y1);	glVertex2d(scr_x1,scr_y1);
		glTexCoord2d(tex_x1,tex_y1);	glVertex2d(scr_x2,scr_y1);
		glTexCoord2d(tex_x1,tex_y2);	glVertex2d(scr_x2,scr_y2);
		glTexCoord2d(tex_x2,tex_y2);	glVertex2d(scr_x1,scr_y2);
		break;
	case MIRROR_Y:
		glTexCoord2d(tex_x1,tex_y2);	glVertex2d(scr_x1,scr_y1);
		glTexCoord2d(tex_x2,tex_y2);	glVertex2d(scr_x2,scr_y1);
		glTexCoord2d(tex_x2,tex_y1);	glVertex2d(scr_x2,scr_y2);
		glTexCoord2d(tex_x1,tex_y1);	glVertex2d(scr_x1,scr_y2);
		break;
	case ROT_90:
		glTexCoord2d(tex_x1,tex_y2);	glVertex2d(scr_x1,scr_y1);
		glTexCoord2d(tex_x1,tex_y1);	glVertex2d(scr_x2,scr_y1);
		glTexCoord2d(tex_x2,tex_y1);	glVertex2d(scr_x2,scr_y2);
		glTexCoord2d(tex_x2,tex_y2);	glVertex2d(scr_x1,scr_y2);
		break;
	case ROT_180:
		glTexCoord2d(tex_x2,tex_y2);	glVertex2d(scr_x1,scr_y1);
		glTexCoord2d(tex_x1,tex_y2);	glVertex2d(scr_x2,scr_y1);
		glTexCoord2d(tex_x1,tex_y1);	glVertex2d(scr_x2,scr_y2);
		glTexCoord2d(tex_x2,tex_y1);	glVertex2d(scr_x1,scr_y2);
		break;
	case ROT_270:
		glTexCoord2d(tex_x2,tex_y1);	glVertex2d(scr_x1,scr_y1);
		glTexCoord2d(tex_x2,tex_y2);	glVertex2d(scr_x2,scr_y1);
		glTexCoord2d(tex_x1,tex_y2);	glVertex2d(scr_x2,scr_y2);
		glTexCoord2d(tex_x1,tex_y1);	glVertex2d(scr_x1,scr_y2);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}


void Bitmap::draw() {
	drawTexture(0, 0, 1, 1, 0, 0, width, height);
}

void Bitmap::draw(int x, int y, int w, int h){
	drawTexture(0, 0, 1, 1, x, y, w, h);
}


void Bitmap::drawAt(int pos_x, int pos_y){
	drawTexture(0, 0, 1, 1, pos_x, pos_y, pos_x+width, pos_y+height);
}


void Bitmap::drawAt(int pos_x,int pos_y, int seg_x, int seg_y, int seg_w, int seg_h){
	float rx1, ry1, rx2, ry2;
	rx1 = (float)seg_x/width;
	ry1 = (float)seg_y/height;
	rx2 = (float)(seg_x+seg_w)/width;
	ry2 = (float)(seg_y+seg_h)/height;
	drawTexture(rx1, ry1, rx2, ry2, pos_x, pos_y, pos_x+seg_w, pos_y+seg_h);
}

BMPError Bitmap::BMPLoadGL(const char fname[])
{
	BMPError e=BMPLoad(fname);
	if(e!=BMPNOERROR) return e;
	orient = NORMAL;
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	if(withAlpha) {
		BMPSetTransparency();
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,bytes);
	} else {
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,bytes);
	}
	delete [] bytes;
	return BMPNOERROR;
}
