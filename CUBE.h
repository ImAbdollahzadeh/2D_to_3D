#ifndef CUBE__H__
#define CUBE__H__

#include "VERTEX.h"
#include "LINE.h"
#include "CAMERA.h"
#include "GENERAL_COLORS.h"
#include <windows.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma warning(disable:4244)

#define PI 3.14159265359
#define DEG_TO_RADIAN(deg) (((PI)/180.00f)*deg)
#define sgn(x) ((x<0)?-1:((x>0)?1:0))
#define WINDOW_ALIGN(X) ((X+31)&~31)

#define RED(CL)   ((CL)>>16)
#define GREEN(CL) ((CL&0x0000FF00)>>8)
#define BLUE(CL)  ((CL&0x000000FF))

#define SET_PIXEL(FB,X,Y,CL)\
do { \
FB[(Y*3) * 500 + (3*X)]   = RED(CL);\
FB[(Y*3) * 500 + (3*X+1)] = GREEN(CL);\
FB[(Y*3) * 500 + (3*X+2)] = BLUE(CL);\
} while(0);

#define SET_BIG_PIXEL(FB,X,Y,CL)\
do { \
FB[(Y*3) * 500 + (3*X)]   = RED(CL);\
FB[(Y*3) * 500 + (3*X+1)] = GREEN(CL);\
FB[(Y*3) * 500 + (3*X+2)] = BLUE(CL);\
\
FB[(Y*3) * 500 + (3*X+3)]   = RED(CL);\
FB[(Y*3) * 500 + (3*X+4)] = GREEN(CL);\
FB[(Y*3) * 500 + (3*X+5)] = BLUE(CL);\
\
FB[(Y*3) * 500 + (3*X-3)]   = RED(CL);\
FB[(Y*3) * 500 + (3*X-2)] = GREEN(CL);\
FB[(Y*3) * 500 + (3*X-1)] = BLUE(CL);\
\
FB[((Y+1)*3) * 500 + (3*X)]   = RED(CL);\
FB[((Y+1)*3) * 500 + (3*X+1)] = GREEN(CL);\
FB[((Y+1)*3) * 500 + (3*X+2)] = BLUE(CL);\
\
FB[((Y-1)*3) * 500 + (3*X)]   = RED(CL);\
FB[((Y-1)*3) * 500 + (3*X+1)] = GREEN(CL);\
FB[((Y-1)*3) * 500 + (3*X+2)] = BLUE(CL);\
} while(0);

#define white 0x00ffffff
#define yellow 0x0000ffff

typedef struct _CUBE {
	VERTEX vertices[8];
	LINE   lines   [12];
	GENERAL_COLORS color;
} CUBE;


void line_impl(unsigned char* fb,
	           VERTEX* v1,
	           VERTEX* v2);
void draw_lines(unsigned char* fb, 
	            CUBE* cu,
	            CAMERA* cam);

void bullet_impl(unsigned char* fb,
	             CAMERA* cam,
	             VERTEX* v);

void draw_vertices(unsigned char* fb,
	               CUBE* cu, 
	               CAMERA* cam);

void init_scene(unsigned char* fb,
	            unsigned int fb_bytes,
	            CUBE* cu,
	            VERTEX* cube_vertices, 
	            CAMERA* cam, 
	            VERTEX* cam_position,
	            GENERAL_COLORS cube_color);

void update_lines_from_vertices(CUBE* cu);

void draw_ritcol(unsigned char* fb, 
	             CAMERA* cam);

#endif // !_3D_OBJECT__H__

