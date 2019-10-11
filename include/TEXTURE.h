#pragma once
#include "VERTEX.h"
#include "CUBE.h"
#include "CAMERA.h"

typedef struct _BMP {
	unsigned int   width;
	unsigned int   height;
	unsigned char* data;
} BMP;

typedef struct _TX_TRIANGLE {
	VERTEX v1;
	VERTEX v2;
	VERTEX v3;
} TX_TRIANGLE;

typedef struct _TEXTURE {
	VERTEX v1;
	VERTEX v2;
	VERTEX v3;
	VERTEX v4;
	TX_TRIANGLE    triangles[2];
	unsigned char* data;
	unsigned int   bytes;
} TEXTURE;

void bitmap_creation (const char* bmp_image_address, BMP* bitmap);
void release_bitmap  (BMP* bitmap);
void cube_texture_cube(unsigned char* fb, CUBE* cu, BMP* bitmap);
